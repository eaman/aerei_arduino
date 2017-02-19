/* Zeta prototipo

Test dei vari LED
*/

#include <common.h>


// Due LED con lampeggio alternato:
Lampeggiatore right = 3;
Lampeggiatore left = 5;
const byte rtail = 6;
const byte ltail = 9;

void setup() {
  left.Invert() ; // Parte da stato invertito rispetto al default
  pinMode(rtail,OUTPUT);
  pinMode(ltail,OUTPUT);
    
}

void loop() {
  // Due LED con lampeggio alternato:
  right.Blink();
  left.Blink();
  digitalWrite(rtail,HIGH);
  digitalWrite(ltail,HIGH);
}
