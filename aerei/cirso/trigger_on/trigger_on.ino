/* Aereo di Cirso

Output:
   2 LED ai lati con lampeggio alternato
   1 LED in coda lampeggio a freq doppia

Input:
   1 interruttore su interrupt 0 per accensione / spegnimento luci

Note:
   Realizzato con un semplice ciclo IF per ON / OFF,
   lo sketch successsivo ha un macchina a stati per gestire
   la transizione ON <-> OFF con una dissolvenza.
*/

#include <common.h>

// Variabili per interrupt 0
volatile unsigned int chValue = 1500; // Valore computato
volatile unsigned int chStart = 1500; // Inizio rilevamento

// Instanziamo un LED fuori dal loop
Lampeggiatore left = 5;
Lampeggiatore right = 6;
Lampeggiatore coda = 9;

void setup() {
    // I PINs vengono impostati dal constructor al momento
    // della dichiarazione dell'ogetto.

    attachInterrupt(0, chRise, RISING); // PIN 2 su 328p / 168
    right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da
    // HI -> LOW --> LOW -> HI
    // per avere 2 LED che lampeggiano alternativamente
}

void loop() {

    if (chValue > 1500) {
        left.Blink();   // Lampeggia con un default di 1sec (0.5 HI 0.5 LOW)
        right.Blink();
        coda.Blink(1000); // Lampeggio in 1000ms = 1 secondo
    } else {
// sarebbe carino mettere una transizione da on -> off con un fade down...
        left.Low();
        right.Low();
        coda.Low();
    } ;
}

// Functions
void chRise() {
    attachInterrupt(0, chFall, FALLING);
    chStart = micros();
};

void chFall() {
    attachInterrupt(0, chRise, RISING);
    chValue = micros() - chStart;
};
