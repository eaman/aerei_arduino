/* Zeta test
 *  le funzioni finali sono da controllare


*/

#include <common.h>


// Due LED con lampeggio alternato:
Lampeggiatore right = 3;
Lampeggiatore left = 5;
const byte rtail = 6;
const byte ltail = 9;
const byte thrPin = A3;
byte thr ;
int thrIn ;

long previousMillisA = 0;
long previousMillisB = 0;

unsigned long intervalA = 200;
unsigned long intervalB = 200;

void setup() {
  left.Invert() ; // Parte da stato invertito rispetto al default
  pinMode(rtail, OUTPUT);
  pinMode(ltail, OUTPUT);
  pinMode(thrPin, INPUT);
  // Serial.begin(9600);

  randomSeed(analogRead(0));
}

void loop() {
  thrIn = pulseIn(thrPin, HIGH, 25000);
  thr = constrain(map(thrIn, 983, 2000, 0, 255), 0, 255) ;

  if (thr >0 && thr < 15) {
    digitalWrite(rtail, 1);
digitalWrite(ltail, 1);
    digitalWrite(3, 1);
digitalWrite(5, 1);

  } else if (thr < 245) {
        // Due LED con lampeggio alternato:
    right.Blink(1120 - 4 * thr );
    left.Blink(1120 - 4 * thr );
    analogWrite(rtail, thr);
    analogWrite(ltail, thr);
  } else {
    digitalWrite(rtail, !digitalRead(rtail));
    digitalWrite(ltail, !digitalRead(ltail));
    delay(random(20, 100));

    //lampA;
    //lampB;

  }
  Serial.println(thrIn);
  Serial.print("\t thr:");
  Serial.println(thr);

}


// Functions
// TODO: non funzionano :(


void lampA () {
  // Illumina la coda r a un tempo random
  if (millis() - previousMillisA > intervalA) {
    previousMillisA = millis();
    intervalA = random(50, 255);
    digitalWrite(rtail, !digitalRead(rtail));
    // Leggiamo direttamente il registro di ledB e scriviamo il suo opposto,
    // questo ci permette di non dover avere una variabile per tracciare lo stato.

  }
}

void lampB () {
  // Illumina la coda l a un tempo random

  if (millis() - previousMillisB > intervalB) {
    previousMillisB = millis();
    intervalB = random(50, 255);
    digitalWrite(ltail, !digitalRead(ltail));
    // Leggiamo direttamente il registro di ledB e scriviamo il suo opposto,
    // questo ci permette di non dover avere una variabile per tracciare lo stato.

  }
}
