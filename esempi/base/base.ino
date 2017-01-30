/* Esempio

   Esempio base:
   2 LED / Strisce laterali che lampeggiano alternativamente
   1 LED / Striscia sotto in FADE
*/

#include <common.h>

// Instanziamo un LED fuori dal loop
Lampeggiatore left = 12;
Lampeggiatore right = 11;
Pwm sotto = 9;

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
  sotto.UD(2000);   // Fade completo in 2 secondi
}
