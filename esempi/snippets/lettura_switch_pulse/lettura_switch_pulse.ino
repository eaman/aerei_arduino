/* Toggle con transizioni tra On | OFF con pulseIn


Sketch di esempio per accensione spegnimento di tutto l'impianto luci
tramite un interruttore a due posizioni della radio utilizzando pulseIn.

Output esempio: 
   1 Lampeggiatore in coda in PWM

Input:
   1 interruttore su interrupt 0 per accensione / spegnimento luci


   Il codice e' blocking fin tanto che il segnale passa da RISE a FALL
   quindi blocca per 1-2ms a ogni esecuzione. Con la variabile freq
   si imposta ogni quanto fare una lettura.


*/

#define DEBUG
#include <common.h>

unsigned long currentMillis; // timestamp reference per millis per tutto il loop

// Variabili Toggle
const byte chToggle = A0; // PIN su cui e' collegato il canale
long unsigned toggleTime = 0; // Timestamp per switch
int toggleValue = 1500; // Valore catturato
int toggleIn = 1500; // Valore filtrato
const int soglia = 1400; // soglia per scatto toggle a 2 posizioni
const unsigned int freq = 200 ; // Ogni quanti millisecondi leggere il valore
// Attenzione che pulsein e' blocking

void setup() {

#ifdef DEBUG
Serial.begin(9600); 
#endif
} ;

void loop() {
    currentMillis = millis(); // Timestamp per tutto il loop

// Lettura ailerons channel ogni 200ms
    if (currentMillis - toggleTime > freq) {

        toggleIn = pulseIn(chToggle, HIGH, 25000);
        if (toggleIn != 0 && toggleIn > 1000 && toggleIn <2000)  {
            // get only resonable values
            toggleValue = toggleIn;
            toggleTime = currentMillis ;
        } ;
    };

if (toggleValue > soglia) {
    // Luci accese
#ifdef DEBUG
    Serial.print("Luci On ");
#endif

} else {
    // luci spente
#ifdef DEBUG
    Serial.print("Luci Off ");
#endif
} ;

#ifdef DEBUG
    Serial.print(toggleIn);
    Serial.print(" - Filtrato: ");
    Serial.println(toggleValue);
    //delay(200);
#endif

}
