/* Zeta test
 *  le funzioni finali sono da controllare


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
   Serial.begin(9600);

  randomSeed(analogRead(0));
}

void loop() {

  thrIn = pulseIn(thrPin, HIGH, 25000);
  thr = constrain(map(thrIn, 983, 2000, 0, 255), 0, 255) ;

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
rwhite.Up(200);
lwhite.Up(200);
ltp.Up(200);
rtp.Up(200);
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

  
  Serial.println(thrIn);
  Serial.print("\t thr:");
  Serial.print(thr);
  Serial.print("\t state:");
  Serial.println(state);

}
