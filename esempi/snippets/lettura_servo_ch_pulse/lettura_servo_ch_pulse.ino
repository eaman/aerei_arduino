
/* Lettura di un canale servo della RX

   Lettura tramite la finzione pulsein
   Utilizzabile su qualunque PIN

*/

#include <common.h>

unsigned long currentMillis; // timestamp reference per millis per tutto il loop

// Variabili
const byte chPin = A4; // PIN su cui e' collegato il canale
long unsigned chStamp = 0; // Timestamp per
unsigned int chIn = 1500; // Valore catturato
unsigned int chValue = 1500; // Valore computato
unsigned int freq = 200 ; // Ogni quanti millisecondi leggere il valore
// Attenzione che pulsein e' blocking

void setup() {
    // Funzione relativa a calibrazione:
//    mid_point =  calibraTrim(chPin) ; // + LED di servizio per monitor calibrazione
} ;

void loop() {
    currentMillis = millis(); // Timestamp per tutto il loop

// Lettura ailerons channel ogni 200ms
    if (currentMillis - chStamp >= freq) {
        chStamp = currentMillis ;

        chIn = pulseIn(chPin, HIGH, 25000);
        if (chIn != 0 && chIn > 1000 && chIn <2000)  {
            // get only resonable values
            chValue = chIn;
        } ;
// Lettura Aileron channel: FAKE con un potenziometro 10K
// chIn = analogRead(chPin);
// chValue = 1000 + chIn
    };


// do something with    chValue
}
