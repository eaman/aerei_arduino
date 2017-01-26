/* Funzione Invert

   Due LED con lampeggio alternato
*/

#include <common.h>

Lampeggiatore right = 3;
Lampeggiatore left = 5;

void setup() {
  left.Invert(); // Parte da stato invertito rispetto al default
}

void loop() {
  // Due LED con lampeggio alternato:
  right.Blink();
  left.Blink();
  // Si possono usare i soliti metodi dell'oggetto blink
}
