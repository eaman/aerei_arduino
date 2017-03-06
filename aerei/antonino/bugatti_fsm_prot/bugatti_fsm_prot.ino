/* Bugatti di Antonino

Outputs:
   2 LED / Strisce laterali che lampeggiano alternativamente
   1 LED in PWM per il motore 
   1 Striscia RGB sotto per tutta la lunghezza delle ali

Inputs:
   Lettura del canale Throttle (3) con la funzione Pulsein
   Lettura alettoni con interrupt 0 (PIN2)

*/

#include <common.h>
#define DEBUG

// LED disponibili
Lampeggiatore left = 7;
Lampeggiatore right = 8;
Pwm motore = 3;

// RGB
RGBLed ailerons(11,10,9,255); // Common Cat 
    // Transizione: lampeggiatori sui PIN RGB
    Lampeggiatore sxLamp(10); // Lampeggiatore
    Lampeggiatore dxLamp(9); // Lampeggiatore
//Pwm rsotto = 6;
//Pwm gsotto = 5;
//Pwm bsotto = 3;


// Var thr
//////////////// !!!! cambiare thrIn
const byte thrPin = A5; // PIN collegato al CH3
byte thr ;  // Throttle a 8bit
int thrIn ; // Valore del th in ingresso dal servo

// Variabili per interrupt 0 su PIN 2
volatile unsigned int ail = 1500; // Valore computato
volatile unsigned int chStart2 = 1500; // Inizio rilevamento

// Variabili per autocalibrazione 0
const byte chPin2 = 2; // PIN per la calibrazione
int mid_point2 = 1500;

// Vars Alettoni
int mid_point = 1560 ; // centro del segnale, trimmato nel setup
const int deviation = 50 ; // deviazione dal punto medio
        //per entrare nello stato successivo dal centro


// FSM gestione alettoni
enum  { // Stati della FMS
    middle,   // centrale
    sxin,     // transizione a sx
    sx,       // sx
    dxin,     // transizione a dx
    dx        // dx
} ailstate  = middle;

// Vars FSM
unsigned long FSM_lastMillis = 0 ; // Timestamp per la FSM degli alettoni
unsigned long pausa = 600;  // Pausa per la transizione durante gli stati 2, 4 della FSM

// Variabili comuni:
unsigned long currentMillis; // timestamp reference per millis per tutto il loop
byte caso ; // Valore random 


void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.
  pinMode(thrPin,INPUT);
  right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da

  attachInterrupt(0, chRise2, RISING); // PIN 2 su 328p / 168

  randomSeed(analogRead(0));

  // Test iniziale dei LED per verifica contatti:
  left.High();
  right.High();
  ailerons.White();
  motore.Set(255);
  delay(4000);


#ifdef DEBUG
   Serial.begin(9600);
#endif
}

void loop() {
currentMillis = millis(); // Timestamp per tutto il loop
    
// Lettura CH3
  thrIn = pulseIn(thrPin, HIGH, 25000);
  // Hint: thrIn andrebbe calibrato son un Serial.write
  if (thrIn != 0) {
thr = map(thrIn, 960, 2000, 0, 255);
};
    
// Gestione throttle
  if (thr >= 0 && thr < 15) {
    // IDLE

    right.Blink();
    left.Blink();
    motore.UD(2000);
  } else if (thr < 245) {
    // Throttle medio
      
    right.Blink(1120 - 4 * thr );
    left.Blink(1120 - 4 * thr );
    motore.lSet(thr);   // Luminosita' proporzionale al throttle
  } else {
    // Throttle al massimo: LED laterali lampeggiano a caso,
    // Sotto luminosita' a caso

    caso = random(20, 240) ;
    right.Swap();
    left.Swap();
    motore.lSet(caso);
    delay(caso);
  }



  //// Ailerons:
 switch (ailstate) {
    case middle:
        ailerons.White();
        // Alettoni piatti
        if (ail > mid_point + deviation + deviation /3) {
            // extra margine per avere un po' di gioco
            ailstate = sxin;
            ailerons.Off(); 
            FSM_lastMillis = currentMillis;
        }
        else if (ail < mid_point - deviation - deviation / 3) {
            ailstate = dxin;
            ailerons.Off(); 
            FSM_lastMillis = currentMillis ;
        } ;
        break;

    case sxin:
        // Transizione a sx
        sxLamp.Blink(150);
        if (currentMillis - pausa > FSM_lastMillis ) {
            ailstate = sx;
        }
        break;

    case sx:
        ailerons.Green();
        if (ail < mid_point + deviation) {
            ailstate = middle;
        }
        else if (ail < mid_point - deviation) {
            FSM_lastMillis = currentMillis;
            ailstate = dxin;
        } ;
        break;

    case dxin:
        // Transizione a dx
        dxLamp.Blink(150);
        if (currentMillis - pausa > FSM_lastMillis ) {
            ailstate = dx;
        }
        break;

    case dx:
        ailerons.Blue();
        if (ail > mid_point - deviation) {
            ailstate = middle;
        }
        else if (ail > mid_point + deviation) {
            FSM_lastMillis = currentMillis;
            ailstate = dxin;
        } ;
        break;
    }

#ifdef DEBUG
Serial.print(thrIn);
    Serial.print("\tthr: ");
Serial.print(thr);
    Serial.print("\tail: ");
    Serial.print(ail);
    Serial.print("\t ailstate:");
    Serial.println(ailstate);
#endif
}
// ISRs
void chRise2() {
    attachInterrupt(0, chFall2, FALLING);
    chStart2 = micros();
}

void chFall2() {
    attachInterrupt(0, chRise2, RISING);
    ail = micros() - chStart2;
}