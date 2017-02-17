/* Yak 980 di A.

   Prototipo base:
OUTPUT:
   1 PWM motore: 10
   2 LED ai lati con lampeggio alternato
   1 LED in coda lampeggio a freq doppia
*/

#include <common.h>

// Instanziamo un LED fuori dal loop
Pwm pLeft = 11;
Lampeggiatore right = 4;
Lampeggiatore coda = 6;
Pwm motore = 10;
byte pins[] = {  // PIN dei LED che compongono la sequenza
 	7,8,9 
}; 

Sequenza seq = Sequenza(pins,3);

void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.

 // right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da
  // HI -> LOW --> LOW -> HI
  // per avere 2 LED che lampeggiano alternativamente
}

void loop() {
//  left.Blink();   // Lampeggia con un default di 1sec (0.5 HI 0.5 LOW)
  right.Blink();
  pLeft.UD(2000);
  coda.Blink();
  motore.UD(2000);
  seq.Update(200);
}
