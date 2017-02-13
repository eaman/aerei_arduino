/* Esempio

   Esempio base:
   2 LED / Strisce laterali che lampeggiano alternativamente
   1 LED / Striscia sotto in FADE

   Lettura del canale Throttle (3) con la funzione Pulsein
*/

#include <common.h>

// LED disponibili
Lampeggiatore left = 10;
Lampeggiatore right = 11;
Pwm sotto = 9;

// Quando il Throttle e' in IDE facciamo un PWM anche sui laterali
Pwm lpwm = 10 ;
Pwm rpwm = 11;

// Variabili
const byte thrPin = 3; // PIN collegato al CH3
byte thr ; // Valore a 8bit per il throttle
int thrIn ; // Valore rilevato del 3 Ch della RX 
const int thMin = 983; // In genere il valore minimo del TH resta costante,
// per calcolarlo si puo' usare la funzione di calibrazione nel setup

byte caso;

void setup() {
    // I PINs vengono impostati dal constructor al momento
    // della dichiarazione dell'ogetto.

    right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da
    // HI -> LOW --> LOW -> HI
    // per avere 2 LED che lampeggiano alternativamente

    randomSeed(analogRead(0));
}

void loop() {
    // Lettura CH3 con pulsein, per usare interrupts vedi ../snippets.
    thrIn = pulseIn(thrPin, HIGH, 25000);
    if (thrIn >= thMin && thrIn < 2000)  { // clean up
        thr = thrIn ;
    };

// Gestione throttle
    if (thr < 1050) {
        // IDLE

        rpwm.UD(2000);
        lpwm.UD(2000);
        sotto.lDown(1500);
    }
    else if (thr < 1900) {
        // Throttle medio
        right.Blink(1120 - 4 * thr );
        left.Blink(1120 - 4 * thr );
        sotto.lSet(map(thrIn, thMin, 2000, 0, 255));   // Luminosita' proporzionale al throttle
    }
    else {
        // Throttle al massimo: LED laterali lampeggiano a caso,
        // Sotto luminosita' a caso
        caso = random(20, 240) ;
        right.Swap();
        left.Swap();
        sotto.lSet(caso);
    }
}
