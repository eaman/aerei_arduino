
/* Lettura di un canale servo della RX

   Lettura tramite la funzione pulsein
   Utilizzabile su qualunque PIN

   Il codice e' blocking fin tanto che il segnale passa da RISE a FALL
   quindi blocca per 1-2ms a ogni esecuzione. Con la variabile freq
   si imposta ogni quanto fare una lettura.


*/

#define DEBUG
#include <common.h>

unsigned long currentMillis; // timestamp reference per millis per tutto il loop

// Variabili
const byte chPin = 2; // PIN su cui e' collegato il canale
long unsigned chStamp = 0; // Timestamp per
unsigned int chIn = 1500; // Valore catturato
unsigned int chValue = 1500; // Valore computato
unsigned int freq = 200 ; // Ogni quanti millisecondi leggere il valore
int mid_point = 1500; // Punto medio per calibrazione
// Attenzione che pulsein e' blocking

void setup() {
// Funzione relativa a calibrazione: per il throttle si puo' evitare
    mid_point =  calibraTrim(chPin)  ; 

#ifdef DEBUG
Serial.begin(9600); // Warning: interrupts e serial potrebbero dare problemi
#endif
} ;

void loop() {
    currentMillis = millis(); // Timestamp per tutto il loop

// Lettura ailerons channel ogni 200ms
    if (currentMillis - chStamp >= freq) {

        chIn = pulseIn(chPin, HIGH, 25000);
        if (chIn != 0 && chIn > 1000 && chIn <2000)  {
            // get only resonable values
            chValue = chIn;
            chStamp = currentMillis ;
        } ;
    };

// do something with    chValue
#ifdef DEBUG
    Serial.print(chValue);
    Serial.print(" - base: ");
    Serial.println(mid_point);
    delay(200);
#endif

}
