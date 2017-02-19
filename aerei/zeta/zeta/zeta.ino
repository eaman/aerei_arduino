/* Zeta

Versione con solo il throttle come input via pulseIn.

Aggiunta striscia RGB sotto.


*/

#include <common.h>
enum states_available { // Stati della FMS
  idle,    // Throttle a zero
  normal,  // Th normale
  full,    // Th massimo
};
states_available state  ;

// Due LED con lampeggio alternato:
Lampeggiatore right = 3; // Lampeggiatori superiori a lato fusoliera
Lampeggiatore left = 5;
const byte rtail = 6; // Luci del motore posteriore
const byte ltail = 9;
const byte thrPin = A3; 
byte pausa ;
byte thr ;
int thrIn ;

Pwm rwhite = 3; // PWM sui lampeggiatori
Pwm lwhite = 5; 
Pwm rtp = 6 ;   // PWM sulla coda
Pwm ltp = 9 ;

RGBLed rgb(7,8,4,255);

void setup() {
  left.Invert() ; // Parte da stato invertito rispetto al default
  pinMode(rtail, OUTPUT);
  pinMode(ltail, OUTPUT);
  pinMode(thrPin, INPUT);
  // Warning: serial breaks PWM
  // Serial.begin(9600);

  randomSeed(analogRead(0));
    // Test iniziale dei LED per verifica contatti:
  left.High();
  right.High();
  rgb.White();
  rtp.Set(255);
  ltp.Set(255);
  delay(4000);
}

void loop() {


  thrIn = pulseIn(thrPin, HIGH, 25000);
  thr = constrain(map(thrIn, 983, 2000, 0, 255), 0, 255) ;
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
    rgb.Green();
    
      rwhite.UD(2000);  // Utilizza il coseno
      lwhite.UD(2000);  // Bisognerebbe evitare di calcolarli 4 volte uguale
      ltp.shift = 500;
      ltp.lUp(1000);
      rtp.lUp(1000);
      break;

    case normal:
    rgb.Blue();
      // Due LED con lampeggio alternato:
      right.Blink(1120 - 4 * thr );
      left.Blink(1120 - 4 * thr );
      analogWrite(rtail, lum(thr));
      analogWrite(ltail, lum(thr));
      break;

    case full:
    rgb.Red();
      pausa = random(30, 125);
      // Due LED con lampeggio alternato:
      right.Blink(1120 - 4 * thr );
      digitalWrite(ltail, !digitalRead(ltail));
      digitalWrite(3, !digitalRead(3));
  

      left.Blink(1120 - 4 * thr );
      digitalWrite(rtail, !digitalRead(rtail));
      digitalWrite(5, !digitalRead(5));
      delay(pausa);
      break;
  }


  //  Serial.println(thrIn);
  //  Serial.print("\t thr:");
  //  Serial.print(thr);
  //  Serial.print("\t state:");
  //  Serial.println(state);

}
