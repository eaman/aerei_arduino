/* Esempio

   Esempio base:
   2 LED / Strisce laterali che lampeggiano alternativamente
   1 LED / Striscia sotto in FADE

   Lettura del canale Throttle (3) con la funzione Pulsein
*/

#include <common.h>

// LED disponibili
Lampeggiatore left = 12;
Lampeggiatore right = 11;
Pwm sotto = 9;

// Variabili
const byte thrPin = 3; // PIN collegato al CH3
byte thr ; // Throttle
int thrIn ;

void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.

  right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da
  // HI -> LOW --> LOW -> HI
  // per avere 2 LED che lampeggiano alternativamente
}

void loop() {
// Lettura CH3
  thrIn = pulseIn(thrPin, HIGH, 25000);
  thr = constrain(map(thrIn, 983, 2000, 0, 255), 0, 255) ;



// Attivazione LEDs
  left.Blink(1120 - 4 * thr);   
  right.Blink(1120 - 4 * thr);
  sotto.lSet(thr);   // Luminosita' proporzionale al throttle
  delay(10); // Opzionale 
}
