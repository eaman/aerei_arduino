/* Bugatti di Antonino

   2 LED / Strisce laterali che lampeggiano alternativamente
   1 LED in PWM per il motore 
   1 Striscia RGB sotto per tutta la lunghezza delle ali

   Lettura del canale Throttle (3) con la funzione Pulsein
*/

#include <common.h>

// LED disponibili
Lampeggiatore left = 7;
Lampeggiatore right = 8;
RGBLed sotto(6,5,9);
Pwm motore = 3;

// RGB
Pwm rsotto = 6;
Pwm gsotto = 5;
Pwm bsotto = 3;


// Variabili
const byte thrPin = A3; // PIN collegato al CH3
byte thr ;  // Throttle a 8bit
int thrIn ; // Valore del th in ingresso dal servo
byte caso ; // Valore random 

void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.
  pinMode(A3,INPUT);
  right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da
  // HI -> LOW --> LOW -> HI
  // per avere 2 LED che lampeggiano alternativamente

  randomSeed(analogRead(0));

  // Test iniziale dei LED per verifica contatti:
  left.High();
  right.High();
  sotto.White();
  motore.Set(255);
  delay(4000);
}

void loop() {
  // Lettura CH3
  thrIn = pulseIn(thrPin, HIGH, 25000);
  // Hint: thrIn andrebbe calibrato son un Serial.write
  thr = map(thrIn, 983, 2000, 0, 255);
    
// Gestione throttle
  if (thr >= 0 && thr < 15) {
    // IDLE

    right.Blink();
    left.Blink();
    gsotto.UD(2000);
    motore.UD(2000);
  } else if (thr < 245) {
    // Throttle medio
      
    right.Blink(1120 - 4 * thr );
    left.Blink(1120 - 4 * thr );
    bsotto.UD(500 + thr * 4);
    motore.lSet(thr);   // Luminosita' proporzionale al throttle
  } else {
    // Throttle al massimo: LED laterali lampeggiano a caso,
    // Sotto luminosita' a caso

    caso = random(20, 240) ;
    right.Swap();
    left.Swap();
    motore.lSet(caso);
    sotto.SetColor(caso,caso,caso);    
    delay(caso);
  }
}
