/* Aereo Palla

Pilotare un LED RGB in base al canale degli alettoni:
per versione con interrupts vedere esempio successivo.

= 3 stati + 2 transizioni:
- piatto
- roll a sx
- roll a dx

TODO:
* clean up magic numbers

*/

#include <common.h>
#define dEBUG // Cambiare in DEBUG per il debug

// Variabili:
unsigned long currentMillis; // timestamp reference per millis per tutto il loop

// Un LED RGB
RGBLed ailerons(9,10,7,255); // Common Cat

// Transizione: Pwm
Lampeggiatore sxLamp(10); // Lampeggiatore
Lampeggiatore dxLamp(9); // Lampeggiatore


// Variabili per lettura canale servo
int ail ; // Valore per ailerons
int ailIn ; // Valore rilevato del 4 Ch della RX
unsigned long ailTimer ; // millis per ail


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
unsigned long pausa = 1000;  // Pausa per la transizione durante gli stati 2, 4 della FSM

// Variabili per interrupt 0 si PIN 2: Throttle
volatile unsigned int chValue2 = 1500; // Valore computato
volatile unsigned int chStart2 = 1500; // Inizio rilevamento

// Variabili per interrupt 1 su PIN 3: Ailerons
volatile unsigned int ail = 1500; // Valore computato
volatile unsigned int mid_point = 1560; // Inizio rilevamento


// Variabili per autocalibrazione 1
const byte chPin3 = 3; // PIN per la calibrazione
int mid_point3 = 1000;

// Vars Alettoni
int mid_point = 1560 ; // centro del segnale, trimmato nel setup
const int deviation = 50 ; // deviazione dal punto medio
        //per entrare nello stato successivo dal centro

///////////////////////////////////////////////////////////
void setup() {

//   #define DEBUG

#ifdef DEBUG
   Serial.begin(9600);
#endif

// Funzione relativa a calibrazione:
mid_point =  calibraTrim(ailPin) ; // + LED di servizio per monitor calibrazione
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
        // dx
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
        // sx
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
    Serial.print("ailIn: ");
    Serial.print(ailIn);
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
    chValue2 = micros() - chStart2;
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
