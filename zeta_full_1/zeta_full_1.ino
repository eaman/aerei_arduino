/* Esempi Vari

Vari esempi di utilizzo della libreria.
*/

#include <common.h>


// Due LED con lampeggio alternato:
Lampeggiatore right = 3;
Lampeggiatore left = 5;
const byte rtail = 6;
const byte ltail = 9;
const byte thrPin = A3;
int thr ;
int thrIn ;

void setup() {
  left.Invert() ; // Parte da stato invertito rispetto al default
  pinMode(rtail, OUTPUT);
  pinMode(ltail, OUTPUT);
  pinMode(thrPin, INPUT);
  Serial.begin(9600);

}

void loop() {

  thrIn = pulseIn(thrPin, HIGH, 25000);
  thr = constrain(map(thrIn, 983, 2000, 0, 255), 0, 255) ;
  // Due LED con lampeggio alternato:
  right.Blink(1630 - 6 * thr );
  left.Blink(1630 - 6 * thr );
  analogWrite(rtail, thr);
  analogWrite(ltail, thr);
  Serial.println(thrIn);
  Serial.print("\t thr:");
  Serial.println(thr);

}
