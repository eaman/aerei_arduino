/* Zeta test
 
Nota: rovedere i PWM per come calcolano le pause:
non possono schendere sotto a 1ms
*/

#include <common.h>
enum states_available { // Stati della FMS
  idle,    // Throttle a zero
  normal,  // Th normale
  full,    // Th massimo
};
states_available state  ;

// Due LED con lampeggio alternato:
Lampeggiatore right = 3;
Lampeggiatore left = 5;
const byte rtail = 6;
const byte ltail = 9;
const byte thrPin = A3;
byte thr ;
int thrIn ;

Pwm rwhite = 3;
Pwm lwhite = 5;
Pwm rtp = 6 ;
Pwm ltp = 9 ;


void setup() {
  left.Invert() ; // Parte da stato invertito rispetto al default
  pinMode(rtail, OUTPUT);
  pinMode(ltail, OUTPUT);
  pinMode(thrPin, INPUT);
  // Warning: serial breaks PWM
  // Serial.begin(9600);

  randomSeed(analogRead(0));
}

void loop() {

thrIn = pulseIn(thrPin, HIGH, 25000);
thr = constrain(map(thrIn, 983, 2000, 0, 255), 0, 255) ;
// Inserire necro delay
delay(10); // Se si abilita il serial debug
            // togliere il delay

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
      rwhite.UD(2);
      lwhite.UD(2);
      ltp.UD(2);
      rtp.UD(2);
      break;

    case normal:
      // Due LED con lampeggio alternato:
      right.Blink(1120 - 4 * thr );
      left.Blink(1120 - 4 * thr );
      analogWrite(rtail, thr);
      analogWrite(ltail, thr);
      break;

    case full:
      // Due LED con lampeggio alternato:
      right.Blink(1120 - 4 * thr );
      left.Blink(1120 - 4 * thr );
      digitalWrite(rtail, !digitalRead(rtail));
      digitalWrite(ltail, !digitalRead(ltail));
      delay(random(20, 100));
      break;
  }


  //  Serial.println(thrIn);
  //  Serial.print("\t thr:");
  //  Serial.print(thr);
  //  Serial.print("\t state:");
  //  Serial.println(state);

}
