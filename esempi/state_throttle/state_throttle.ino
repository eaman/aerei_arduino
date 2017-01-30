/* Throttle state machine

Idle, throttle e averburner effect basati sono sul canale throttle.   

FSM con dispatcher esterno.


*/

#include <common.h>

enum  { // Stati della FMS
  idle,    // Throttle a zero
  normal,  // Th normale
  full,    // Th massimo
} state  ;

// Due LED con lampeggio alternato:
Lampeggiatore right = 3;
Lampeggiatore left = 5;
Pwm motor = 7;

const byte thrPin = A3;
byte thr ; // Valore a 8bit per il throttle
int thrIn ; // Valore rilevato del 3 Ch della RX 



void setup() {
  left.Invert() ; // Parte da stato invertito rispetto al default
  randomSeed(analogRead(0));
}

void loop() {

 // Lettura Throttle channel: FAKE con un potenziometro
 //thrIn = analogRead(3);
 //thr = constrain(thrIn / 4 , 0, 255) ;

 // Lettura Throttle channel
 thrIn = pulseIn(thrPin, HIGH, 25000);
 thr = constrain(map(thrIn, 983, 2000, 0, 255), 0, 255) ; // 983 potrebbe campbiare con 
           // con un altra ricevente, fare una calibrazione nel caso.

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
       // Lampeggia i lati fissi e fa un PWD Up/Down col motore
     right.Blink();
     left.Blink();
     motore.UD(1000);
     break;

   case normal:
     // right e left lampeggiano alternativamente in base al th,
     // il motore e' acceso con correzione di luminosita' in proporzione al th
     right.Blink(1120 - 4 * thr ); // lampeggio piu' rapido in base al Th
     left.Blink(1120 - 4 * thr );
     motore.lSet(thr);
     break;

   case full:
     // lampeggi e PWM a caso
     right.Swap();
     left.Swap();
     motore.lSet(random(0,255);
     delay(random(20, 100));
     break;
  }

