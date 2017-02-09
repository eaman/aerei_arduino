
/* Lettura di un canale servo della RX

   Lettura tramite la funzione pulsein
   Utilizzabile su qualunque PIN

   Il codice e' blocking fin tanto che il segnale passa da RISE a FALL
   quindi blocca per 1-2ms a ogni esecuzione. Con la variabile freq
   si imposta ogni quanto fare una lettura.


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
//    mid_point =  calibraTrim(chPin) +10 ; // Con pulse in c'e' una traslazione ~10
//Serial.begin(9600); // Warning: interrupts e serial potrebbero dare problemi
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
    };

// do something with    chValue
//    Serial.print(chValue);
//    Serial.print(" - base: ");
//    Serial.println(mid_point);
//    delay(200);

}
