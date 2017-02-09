/* Ailerons state machine

Pilotare un LED RGB in base al canale degli alettoni:

= 3 stati + 2 transizioni:
- piatto
- roll a sx
- roll a dx

NOTE: uso di goto all'interno dell FSM.

TODO:

* clean up magic numbers

*/

#include <common.h>

// Variabili:
unsigned long currentMillis; // timestamp reference per millis per tutto il loop

// Un LED RGB
RGBLed ailerons(11,10,9,255);

// Variabili per lettura canale servo
const byte ailPin = A4;
int ail ; // Valore a 8bit per ailerons
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

unsigned long FSM_lastMillis = 0 ; // Timestamp per la FSM degli alettoni
unsigned long pausa = 1000;  // Pausa per la transizione durante gli stati 2, 4 della FSM
int mid_point = 1560 ; // centro del segnale, trimmato nel setup
const int deviation = 50 ; // deviazione dal punto medio
        //per entrare nello stato successivo dal centro

///////////////////////////////////////////////////////////
void setup() {

//   Serial.begin(9600);
//   #define DEBUG

    // Funzione relativa a calibrazione:
    mid_point =  calibraTrim(ailPin) ; // + LED di servizio per monitor calibrazione
}

void loop() {
    currentMillis = millis(); // Timestamp per tutto il loop

// Lettura ailerons channel ogni 200ms
    if (currentMillis - ailTimer>= 200) { 
        ailTimer = currentMillis ;

        ailIn = pulseIn(ailPin, HIGH, 25000);
        if (ailIn != 0 && ailIn > 1000 && ailIn <2000)  {
            // get only resonable values
            ail = ailIn;
        } ;
// Lettura Aileron channel: FAKE con un potenziometro 10K
// ailIn = analogRead(3);
// ail = 1000 + ailIn 
    }



    switch (ailstate) {
    case middle:
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
        ailerons.Red();
        break;

    case sxin:
        // Transizione a sx
        ailerons.Off();
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
        ailerons.Off();
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
