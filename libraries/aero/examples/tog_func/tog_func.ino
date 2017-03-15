/* Toggle con transizioni tra On | OFF con pulseIn
   Funzione


Sketch di esempio per accensione spegnimento di tutto l'impianto luci
tramite un interruttore a due posizioni della radio utilizzando 
la funzione toggleRead(pin) basata su pulseIn.


Input:
   1 pulseIn su A0 per accensione / spegnimento luci


   Il codice e' blocking fin tanto che il segnale passa da RISE a FALL
   quindi blocca per 1-2ms a ogni esecuzione. Con la variabile freq
   si imposta ogni quanto fare una lettura (default = 500ms).


*/

#define dEBUG
#include <common.h>
#include <aero.h>

void setup() {
   Serial.begin(9600);
} ;

void loop() {


if (toggleRead(A0)) { // Numero del PIN a cui e' collegato il canale dell'interruttore
//if (toggleRead(A0,100)) { // Numero del PIN, frequenza di aggiornamento in milli sec
    // Luci accese
    Serial.println("Luci On ");
} else {
    // luci spente
    Serial.println("Luci Off ");
} ;


}
