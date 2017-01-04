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
byte thr ;
int thrIn ;

long previousMillisA ;
long previousMillisB;

void setup() {
  left.Invert() ; // Parte da stato invertito rispetto al default
  pinMode(rtail, OUTPUT);
  pinMode(ltail, OUTPUT);
  pinMode(thrPin, INPUT);
  Serial.begin(9600);

  randomSeed(analogRead(0));
}

void loop() {

  thrIn = pulseIn(thrPin, HIGH, 25000);
  thr = constrain(map(thrIn, 983, 2000, 0, 255), 0, 255) ;
  // Due LED con lampeggio alternato:
  right.Blink(1630 - 6 * thr );
  left.Blink(1630 - 6 * thr );
  if (thr < 240) {
  analogWrite(rtail, thr);
  analogWrite(ltail, thr);
  } else {
    lampA ;
    lampB;
  }
  Serial.println(thrIn);
  Serial.print("\t thr:");
  Serial.println(thr);

}


// Functions 

static byte intervalA ;
static byte intervalB ;

void lampA () {
  // Illumina la coda r a un tempo random
  if (millis() - previousMillisA > intervalA) {   
    previousMillisA = millis(); 
  digitalWrite(rtail, !digitalRead(rtail));
  // Leggiamo direttamente il registro di ledB e scriviamo il suo opposto,
  // questo ci permette di non dover avere una variabile per tracciare lo stato.
  intervalA = random(50,255);
  }
}

void lampB () {
  // Illumina la coda l a un tempo random

  if (millis() - previousMillisB > intervalB) {   
    previousMillisB = millis(); 
  digitalWrite(ltail, !digitalRead(ltail));
  // Leggiamo direttamente il registro di ledB e scriviamo il suo opposto,
  // questo ci permette di non dover avere una variabile per tracciare lo stato.
  intervalB = random(50,255);
  }
}
