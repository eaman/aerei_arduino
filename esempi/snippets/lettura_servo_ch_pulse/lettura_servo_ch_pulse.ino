
/* Lettura di un canale servo della RX

   Lettura tramite la funzione pulsein
   Utilizzabile su qualunque PIN

   Il codice e' blocking fin tanto che il segnale passa da RISE a FALL
   quindi blocca per 1-2ms a ogni esecuzione.
   
   Il segnale dalla rx dovrebbe essere ~50hz,
   vedere questo sketch $_millis con lettura a intervalli programmabili.

*/

#include <common.h>


// Variabili
const byte chPin = A4; // PIN su cui e' collegato il canale
unsigned int chIn = 1500; // Valore catturato
unsigned int chValue = 1500; // Valore computato
// Attenzione che pulsein e' blocking

// Variabili per autocalibrazione
int mid_point = 1500;

void setup() {
    // Funzione relativa a calibrazione:
    mid_point =  calibraTrim(chPin) - 10; // Con pulse in si toglie 10
Serial.begin(9600); // Warning: interrupts e serial potrebbero dare problemi

} ;

void loop() {

// Lettura ailerons channel ogni 200ms
        chIn = pulseIn(chPin, HIGH, 25000);
        if (chIn != 0 && chIn > 1000 && chIn <2000)  {
            // get only resonable values
            chValue = chIn;
    };


// do something with    chValue
    Serial.print(chValue);
    Serial.print(" - base: ");
    Serial.println(mid_point);
    delay(200);
}
