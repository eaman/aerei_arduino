/* Esempio

   Esempio base:
   2 LED / Strisce laterali che lampeggiano alternativamente
   1 LED / Striscia sotto in FADE

   Lettura del canale Throttle (3) con la funzione Pulsein
*/

#include <common.h>

// LED disponibili
Lampeggiatore left = 10;
Lampeggiatore right = 11;
Pwm sotto = 9;

// Quando il Throttle e' in IDE facciamo un PWM anche sui laterali
Pwm lpwm = 10 ;
Pwm rpwm = 11;

// Variabili
const byte thrPin = 3; // PIN collegato al CH3
byte thr ; // Throttle
int thrIn ;
byte caso;

void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.

  right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da
  // HI -> LOW --> LOW -> HI
  // per avere 2 LED che lampeggiano alternativamente

  randomSeed(analogRead(0));
}

void loop() {
  // Lettura CH3
  thrIn = pulseIn(thrPin, HIGH, 25000);
  thr = constrain(map(thrIn, 983, 2000, 0, 255), 0, 255) ;

// Gestione throttle
  if (thr > 0 && thr < 15) {
    // IDLE

    rpwm.UD(2000);
    lpwm.UD(2000);
    sotto.lDown(1500);
  } else if (thr < 245) {
    // Throttle medio

    right.Blink(1120 - 4 * thr );
    left.Blink(1120 - 4 * thr );
    sotto.lSet(thr);   // Luminosita' proporzionale al throttle
  } else {
    // Throttle al massimo: LED laterali lampeggiano a caso,
    // Sotto luminosita' a caso

    caso = random(20, 240) ;
    right.Swap();
    left.Swap();
    sotto.lSet(caso);
    delay(caso);
  }
}
