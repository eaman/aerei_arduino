/* Ailerons state machine
            Serial.print(mid_point);

Pilotare un LED RGB in base al canale degli alettoni:
Questo sketch usa 2 interrupts per thr e alettoni.

INPUT:
PIN 2   : throttle
PIN 3   : alettoni

OUTPUT:
ailerons	RGB Alettoni 
motore		Motore PWM
left, right 2 Lampeggiatori PWM laterali + PWM

FSM per alettoni
= 3 stati + 2 transizioni:
- piatto
- roll a sx
- roll a dx
- piatto -> sx
- piatto -> dx


Ciclo if per gestione di 3 stati del motore:
- idle
- middle 
- max


TODO:
* Da testare! Mai provato.

*/

#include <common.h>
#define DEBUG

// Variabili per interrupt 0 si PIN 2
volatile unsigned int thr = 1500; // Valore computato
volatile unsigned int chStart2 = 1500; // Inizio rilevamento

// Variabili per interrupt 1 su PIN 3
volatile unsigned int ail = 1500; // Valore computato
volatile unsigned int chStart3 = 1500; // Inizio rilevamento

// Variabili per autocalibrazione 0
const byte chPin2 = 3; // PIN per la calibrazione
int mid_point2 = 1500;

// LEDs:
Pwm motore = 11;

// LED RGB alettoni
RGBLed ailerons(5,6,9,255); // Common Cat
// Transizione: Pwm
Lampeggiatore sxLamp(6); // Lampeggiatore
Lampeggiatore dxLamp(9); // Lampeggiatore


// Variabili per lettura canale servo
byte ailPin = 3; // Calibrazione

// Vars Alettoni
int mid_point = 1560 ; // centro del segnale, trimmato nel setup
const int deviation = 50 ; // deviazione dal punto medio
        //per entrare nello stato successivo dal centro

// Led motore e altri:
Lampeggiatore left = 10;
Lampeggiatore right = 12;
Pwm sotto = 9;

// Quando il Throttle e' in IDE facciamo un PWM anche sui laterali
Pwm lpwm = 10 ;
Pwm rpwm = 12;

// Variabili:
unsigned long currentMillis; // timestamp reference per millis per tutto il loop
byte caso; // Random var
byte thrBit ; // Valore a 8bit per il throttle




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
unsigned long pausa = 500;  // Pausa per la transizione durante gli stati 2, 4 della FSM

///////////////////////////////////////////////////////////
void setup() {


#ifdef DEBUG
   Serial.begin(9600);
#endif

    attachInterrupt(0, chRise2, RISING); // PIN 2 su 328p / 168
    attachInterrupt(1, chRise3, RISING); // PIN 3 su 328p / 168


// Funzione relativa a calibrazione:
mid_point =  calibraTrim(ailPin) + 10 ; // + LED di servizio per monitor calibrazione
//Serial.print(mid_point);
//while(1) {
//}
}

void loop() {
    currentMillis = millis(); // Timestamp per tutto il loop

    switch (ailstate) {
    case middle:
        ailerons.White();
        // Alettoni piatti
        if (ail > mid_point + deviation + deviation /3) {
            // extra margine per avere un po' di gioco
            ailstate = sxin;
            FSM_lastMillis = currentMillis;
        }
        else if (ail < mid_point - deviation - deviation / 3) {
            ailstate = dxin;
            FSM_lastMillis = currentMillis ;
        } ;
        break;

    case sxin:
        // Transizione a sx
        sxLamp.Blink(200);
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
        dxLamp.Blink(200);
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

// Gestione throttle
    if (thr < 1050) {
        // IDLE
        rpwm.UD(2000);
        lpwm.UD(2000);
        motore.lDown(1500);
    }
    else if (thr > 1900) {
        // Throttle al massimo: LED laterali lampeggiano a caso,
        // Sotto luminosita' a caso
        caso = random(30, 250) ;
        right.Swap();
        left.Swap();
        motore.lSet(caso);
        delay(caso); // Blocking!
    }
    else {
        // Throttle medio
        thrBit = map(thr,1050, 1900, 0, 255);
        right.Blink(1220 - 4 * thrBit );
        left.Blink(1220 - 4 * thrBit );
        motore.lSet(thrBit);   // Luminosita' proporzionale al throttle
    }

        
#ifdef DEBUG
Serial.print((thr - 980) / 4);
    Serial.print("\tail: ");
    Serial.print(ail);
    Serial.print("\t ailstate:");
    Serial.println(ailstate);
#endif
}


// Functions
void chRise2() {
    attachInterrupt(0, chFall2, FALLING);
    chStart2 = micros();
}

void chFall2() {
    attachInterrupt(0, chRise2, RISING);
    thr = micros() - chStart2;
}
// Seconod iterrupt
void chRise3() {
    attachInterrupt(1, chFall3, FALLING);
    chStart3 = micros();
}

void chFall3() {
    attachInterrupt(1, chRise3, RISING);
    ail = micros() - chStart3;
}
