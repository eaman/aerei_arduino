/* Toggle con transizioni tra On | OFF con pulseIn
   Funzione


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

#define dEBUG
#include <common.h>

unsigned long currentMillis; // timestamp reference per millis per tutto il loop


void setup() {
   Serial.begin(9600);
#ifdef DEBUG
Serial.begin(9600); 
#endif
} ;

void loop() {
currentMillis = millis(); // Timestamp per tutto il loop


if (toggleRead(A0)) {
    // Luci accese
    Serial.println("Luci On ");
} else {
    // luci spente
    Serial.println("Luci Off ");
} ;


}

boolean toggleRead(byte togglePin) {
// Variabili Toggle
long static unsigned toggleTime ; // Timestamp per switch
static int toggleValue = 0 ; // Valore catturato
static int toggleIn = 0 ; // Valore filtrato
const int soglia = 1400; // soglia per scatto toggle a 2 posizioni
const unsigned int freq = 400 ; // Ogni quanti millisecondi leggere il valore

    if (currentMillis - toggleTime > freq) {

        toggleIn = pulseIn(togglePin, HIGH, 25000);
        if (toggleIn != 0 && toggleIn > 1000 && toggleIn <2000)  {
            // get only resonable values
            toggleValue = toggleIn;
            toggleTime = currentMillis ;
        } ;
    };
#ifdef DEBUG
    Serial.print(toggleIn);
    Serial.print(" - Filtrato: ");
    Serial.println(toggleValue);
#endif

if (toggleValue > soglia) {
    return 1;
} else {
    return 0;
} ;

}
