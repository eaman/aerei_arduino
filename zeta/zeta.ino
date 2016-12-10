/* Esempio

Setup per la Zeta
*/

#include <common.h>
Lampeggiatore status = 13;

// Attorno al canopy:
Lampeggiatore rtop = 3;
Lampeggiatore ltop = 5;

void setup() {
  // I PINs vengono impostati dalla dichiarazione dell'ogetto.
  ltop.Invert();
}

void loop() {


  rtop.Blink(300);
  ltop.Blink(300);
  status.Blink(500);
}
