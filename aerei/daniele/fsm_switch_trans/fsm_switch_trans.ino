/* Aereo di Daniele

FSM: il throttle e' a posto
Prototipo: F8 Bearcat

Output:
   2 LED PWM ai lati con lampeggio alternato
   2 LED PWM alle estremita ali

Input:
    2 interrupts per th e alettone
    PIN 2:  alettone
    PIN 3:  throttle


    TODO
* Vedere la calibrazione automatica
* Min e max a 1000 - 2000 per alettone

TODO: 
Aggiungere FSM per alettone: lampeggi alternati
in base a chValue2
*/

#include <common.h>
# define DEBUG

// Instanziamo un LED fuori dal loop
Lampeggiatore left = 6;
Lampeggiatore right = 9;
Lampeggiatore codasx = 5;
Lampeggiatore codadx = 10;

Pwm pleft = 6;
Pwm pright = 9;
Pwm pcodasx = 5;
Pwm pcodadx = 10;

// Variabili per interrupt 0 si PIN 2
volatile unsigned int chValue2 = 1500; // Valore computato
volatile unsigned int chStart2 = 1500; // Inizio rilevamento

// Variabili per interrupt 1 su PIN 3
volatile unsigned int chValue3 = 1500; // Valore computato
volatile unsigned int chStart3 = 1500; // Inizio rilevamento

// Variabili per autocalibrazione 0
const byte chPin2 = 2; // PIN per la calibrazione alettone
int mid_point2 = 1500;

// Variabili per autocalibrazione 1
const byte chPin3 = 3; // PIN per la calibrazione
int mid_point3 = 1000;

// Variabili
int caso ;
int thrBit;
unsigned long pausa = 2000;  // Pausa per la transizione durante gli stati 2, 4 della FSM

// Variabili
const byte chPin = A1; // PIN su cui e' collegato il canale
unsigned int chIn = 1500; // Valore catturato
long unsigned chStamp = 0; // Timestamp per
unsigned int freq = 400 ; // Ogni quanti millisecondi leggere il valore 
unsigned long currentMillis; // timestamp reference per millis per tutto il loop
const int soglia = 1500; // soglia per scatto toggle a 2 posizioni
unsigned long FSM_lastMillis = 0 ; // Timestamp per la FSM degli alettoni


// FSM gestione interruttore luci
enum  { // Stati della FMS
    On,     // Acceso
    toOff,  // Trans On -> Off
    Off,    // Spento
    toOn    // Trans OFF -> On
} toggle  = Off;

void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.
right.Invert();
codadx.Invert();

  // HI -> LOW --> LOW -> HI
  // per avere 2 LED che lampeggiano alternativamente
    // Funzione relativa a calibrazione con pulsein:
    mid_point2 =  calibraTrim(chPin2) ; // Calibrazione del TRIM attivo sul canale
    //mid_point3 =  calibraTrim(chPin3) ; // Calibrazione del TRIM attivo sul canale
    attachInterrupt(0, chRise2, RISING); // PIN 2 su 328p / 168
    attachInterrupt(1, chRise3, RISING); // PIN 3 su 328p / 168
#ifdef dEBUG
Serial.begin(9600); 
#endif
}

void loop() {
currentMillis = millis(); // Timestamp per tutto il loop

//codasx.Blink();
//codadx.Blink();
// Lettura ailerons channel ogni 200ms
    if (currentMillis - chStamp >= freq) {

        chIn = pulseIn(chPin, HIGH, 25000);
        if (chIn != 0 && chIn > 1000 && chIn <2000)  {
            // get only resonable values
            chStamp = currentMillis ;
        } ;
    };

switch (toggle) {
    case Off:
    // Spento
    pcodasx.Set(255) ;
    pcodadx.Set(255) ;
    pleft.Set(255) ;
    pright.Set(255) ;
        if (chIn > soglia) {
            FSM_lastMillis = currentMillis;
            toggle = toOn ; 
        }
        break;

// Interruttore on / off

    case On:
    // Acceso
// Gestione throttle
    if (chValue3 < 1050) {
        // IDLE
//pleft.Up(1000);
//pright.Up(1000);
pcodasx.UD(2000);
pcodadx.UD(2000);
pleft.lUp(1000);
pright.lDown(1000);


    }
    else if (chValue3 > 1900) {
        // Throttle al massimo: LED laterali lampeggiano a caso,
        // Sotto luminosita' a caso
        caso = random(30, 250) ;
pleft.Set(caso); 
pright.Set(caso); 
pcodasx.Set(caso);
pcodadx.Set(caso);
        delay(caso);
    }
    else {
        // Throttle medio
        thrBit = map(chValue3,1050, 1900, 0, 255);
        codasx.Blink(1220 - 4 * thrBit );
        codadx.Blink(1220 - 4 * thrBit );
left.Blink(map(chValue2,1000,2000,200,800 ));
right.Blink(map(chValue2,1000,2000,800,200 ));
    }
break;


    case toOn:
    // Trans off -> on
pleft.lUp(pausa); 
pright.lUp(pausa); 
pcodasx.lUp(pausa);
pcodadx.lUp(pausa);

        if (chIn > soglia && currentMillis - pausa > FSM_lastMillis ) { 
            toggle = On ; 
        } else if  (chIn <= soglia) {
            toggle = Off ; 
        }
        break;

    case toOff:
    // Trans on -> off
pleft.lDown(pausa); 
pright.lDown(pausa); 
pcodasx.lDown(pausa);
pcodadx.lDown(pausa);

        if (chIn <= soglia && currentMillis - pausa > FSM_lastMillis ) { 
            toggle = Off ; 
        } else if  (chIn > soglia) {
            toggle = On ; 
        }
        break;
#ifdef DEBUG
    Serial.print("PIN2: ");
    Serial.print(chValue2);
    Serial.print(" -base: ");
    Serial.print(mid_point2);

    Serial.print(" |-| PIN3:");
    Serial.print(chValue3);
    Serial.print(" -base: ");
    Serial.print(mid_point3);
    Serial.print(" switch: ");
    Serial.println(chIn);
#endif
}
}





// Functions
void chRise2() {
    attachInterrupt(0, chFall2, FALLING);
    chStart2 = micros();
}

void chFall2() {
    attachInterrupt(0, chRise2, RISING);
    chValue2 = micros() - chStart2;
}
// Seconod iterrupt
void chRise3() {
    attachInterrupt(1, chFall3, FALLING);
    chStart3 = micros();
}

void chFall3() {
    attachInterrupt(1, chRise3, RISING);
    chValue3 = micros() - chStart3;
}
