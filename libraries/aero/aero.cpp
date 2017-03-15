/*
  Aero 

Autore: Andrea Manni

Link: http://aero.piffa.net
Licenza:    GPLv3

*/

#include "Arduino.h"
#include "aero.h"

#define dEBUG

//////////////////
// Funzioni

boolean toggleRead (byte togglePin, const unsigned int freq ) {
// Variabili Toggle
long static unsigned toggleTime ; // Timestamp per switch
static int toggleValue = 0 ; // Valore catturato
static int toggleIn = 0 ; // Valore filtrato
const int soglia = 1400; // soglia per scatto toggle a 2 posizioni
// const unsigned int freq = 500 ; // Ogni quanti millisecondi leggere il valore

    if (millis() - toggleTime > freq) {

        toggleIn = pulseIn(togglePin, HIGH, 25000);
        if (toggleIn != 0 && toggleIn > 1000 && toggleIn <2000)  {
            // get only resonable values
            toggleValue = toggleIn;
            toggleTime = millis() ;
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
