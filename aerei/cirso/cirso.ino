/* Aereo di Cirso

   Esempio base:
   2 LED ai lati con lampeggio alternato
   1 LED in coda lampeggio a freq doppia
*/

#include <common.h>

// Instanziamo un LED fuori dal loop
Lampeggiatore left = 5;
Lampeggiatore right = 6;
Lampeggiatore coda = 9;

void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.

  right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da
  // HI -> LOW --> LOW -> HI
  // per avere 2 LED che lampeggiano alternativamente
}

void loop() {
  left.Blink();   // Lampeggia con un default di 1sec (0.5 HI 0.5 LOW)
  right.Blink();
  coda.Blink(1000); // Lampeggio in 1000ms = 1 secondo
}
