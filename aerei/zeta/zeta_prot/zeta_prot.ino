/* Zeta prototipo

   Sketch da breadboard, il throttle e' simulato con un potenziometro.

*/

#include <common.h>
enum  { // Stati della FMS
  idle,    // Throttle a zero
  normal,  // Th normale
  full,    // Th massimo
} state  ;

// Due LED con lampeggio alternato:
Lampeggiatore right = 13;
Pwm rpwm = 3;

// Variabili
const byte thrPin = A3;
byte thr ;
int thrIn ;



void setup() {
  Serial.begin(9600);
  pinMode(A3, INPUT);
  randomSeed(analogRead(0));
}

void loop() {

  // Utilizzando un potenziometro
  //  thrIn = analogRead(3);
  //  thr = constrain(thrIn / 4 , 0, 255) ;

  // Utilizzando una RX
  thrIn = pulseIn(thrPin, HIGH, 25000);
  // Hint: thrIn andrebbe calibrato son un Serial.write
  thr = constrain(map(thrIn, 960, 2000, 0, 255), 0, 255);

  // FMS dispatcher
  if ( thr < 10 ) {
    state = idle ;
  } else if ( thr > 245 ) {
    state = full ;
  } else {
    state = normal ;
  }

  switch (state) {
    case idle:
      rpwm.UD(2000);
      right.Blink();
      break;

    case normal:
      // Due LED con lampeggio alternato:
      right.Blink(1120 - 4 * thr );
      rpwm.lSet(thr);
      break;

    case full:
      digitalWrite(3, HIGH);
      rpwm.Set(0);
      right.Swap();
      delay(50);
      rpwm.Set(255);
      right.Swap();
      delay(50);
      break;
  }


  Serial.print(thrIn);
  Serial.print("\t thr:");
  Serial.print(thr);
  Serial.print("\t state:");
  Serial.println(state);
  //  delay(200);
}
