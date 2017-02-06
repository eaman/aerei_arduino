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

enum  { // Stati della FMS
    middle,   // centrale
    sxin,     // transizione a sx
    sx,       // sx
    dxin,     // transizione a dx
    dx        // dx
} ailstate  = middle;

// Un LED RGB
RGBLed ailerons(11,10,9);

const byte ailPin = A4;
int ail ; // Valore a 8bit per ailerons
int ailIn ; // Valore rilevato del 4 Ch della RX


unsigned long now; // timestamp reference for millis
unsigned long pausa = 1000;

int mid_point = 1500 ; // centro del segnale, trimmato nel setup
const int deviation = 50 ; // deviazione per entrare nello stato succiessivo

void setup() {
    /* Bisognerebbe introdurre una calibrazione per compensare i TRIM
       ed eventualmente i dual rates.

    - attivarla se allo start un ale e' al massimo
    - fargli leggere i valori massimi
    - salvarli in eprom
    - per i dual rates: si potrebbe intercettare valori oltre al max
      e in base a questi traslare le soglie automaticamente

    Hint: leggere la soglia di rollio significativo in volo
          e inserirla nei riferimenti.
    */

    Serial.begin(9600);

/* START Calibrazione TRIM canale:
   Lettura di 10 smaple
   calcolo del valore medio esclusi gli 0 
 */
    byte a = 0;
    Serial.println(">> Calibrazione: ");
    while (a < 10) {
        ailIn = pulseIn(ailPin, HIGH, 25000);
        if (ailIn != 0 ) {
            ail = ail + ailIn ;
            a++ ;
            Serial.print(a);
            Serial.print(": ");
            Serial.println(ail);
            digitalWrite(13, !digitalRead(13));
            delay(10);
        }
    }
    mid_point = ail / 10 ;
    Serial.print(">> Fine Calibrazione: ");
    Serial.print(mid_point);
    Serial.println("--");
// END calibrazione

    // Funzione relativa a calibrazione:
//mid_point =  calibraTrim(ailPin) ; // Pin a cui e' collegato il canale
//mid_point =  calibraTrim(aliPin,11) ; // + LED di servizio per monitor calibrazione
}

void loop() {

// Lettura Aileron channel: FAKE con un potenziometro 10K
//ailIn = analogRead(3);
//ail = constrain(aliIn * 2 , 0, 2000) ;

// Lettura ailerons channel
    ailIn = pulseIn(ailPin, HIGH, 25000);
    if (ailIn != 0) {
        ail = constrain(ailIn, 1000, 2000);
    } ;
    // con un altra ricevente, fare una calibrazione nel caso.
    // Middle = 1512


    switch (ailstate) {
    case middle:
        // Alettoni piatti
        if (ail > mid_point + deviation + deviation /3) {
            ailstate = sxin;
            now = millis() ;
            goto sxin ;
        }
        else if (ail < mid_point - deviation - deviation / 3) {
            ailstate = dxin;
            now = millis() ;
            goto dxin ;
        } ;
        ailerons.White();

        break;

    case sxin:
sxin:
        // Transizione a sx
        ailerons.Off();
        if (millis() - pausa > now ) {
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
            now = millis() ;
            ailstate = dxin;
        } ;
        break;

    case dxin:
        // Transizione a dx
dxin:
        ailerons.Off();
        if (millis() - pausa > now ) {
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
            now = millis() ;
            ailstate = dxin;
        } ;
        break;
    }

    Serial.print("ailIn: ");
    Serial.print(ailIn);
    Serial.print("\tail: ");
    Serial.print(ail);
    Serial.print("\t ailstate:");
    Serial.println(ailstate);
    //  delay(200);
}
