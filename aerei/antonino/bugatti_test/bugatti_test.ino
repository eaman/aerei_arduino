/* Bugatti di Antonino

   Esempio base:
   2 LED / Strisce laterali che lampeggiano alternativamente
   1 LED in PWM per il motore PWM
   1 Striscia RGB sotto per tutta la lunghezza delle ali

   Lettura del canale Throttle (3) con la funzione Pulsein
*/

#include <common.h>

// LED disponibili
Lampeggiatore left = 7;
Lampeggiatore right = 8;
Pwm motore = 3;

// RGB
Pwm rsotto = 6;
Pwm gsotto = 5;
Pwm bsotto = 3;

void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.

  right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da
  // HI -> LOW --> LOW -> HI
  // per avere 2 LED che lampeggiano alternativamente

  randomSeed(analogRead(0));
}

void loop() {
    right.Blink();
    left.Blink();
    gsotto.UD(2000);
    motore.UD(2000);
}
