/* Yak 980 di A.

   Prototipo:

OUTPUT:
   1 PWM motore: 10
   2 LED ai lati con lampeggio alternato
   1 LED in coda lampeggio a freq doppia
   3 Sequenza di LED da 3 unita' ripetuta 3 volte

INPUT:

   * Thtottle: PIN 2
   * Ailerons: PIN 3

Notes: abbondante usi di map().
NO FSM.

*/

#include <common.h>
#define dEBUG

// Variabili per interrupt 0 si PIN 2
volatile unsigned int chValue2 = 1500; // Valore computato
volatile unsigned int chStart2 = 1500; // Inizio rilevamento

// Variabili per interrupt 1 su PIN 3
volatile unsigned int chValue3 = 1500; // Valore computato
volatile unsigned int chStart3 = 1500; // Inizio rilevamento

// Variabili per autocalibrazione 0
const byte chPin2 = 2; // PIN per la calibrazione
int mid_point2 = 980;

// Variabili per autocalibrazione 1
const byte chPin3 = 3; // PIN per la calibrazione
int mid_point3 = 1500;

// Instanziamo un LED fuori dal loop
Lampeggiatore left = 4;
Lampeggiatore right = 11;
Lampeggiatore coda = 6;
Pwm motore = 10;
Lampeggiatore stato = 13;
byte pins[] = {  // PIN dei LED che compongono la sequenza
 	7,8,9 
}; 
Sequenza seq = Sequenza(pins,3);

void setup() {
left.Invert();
    // Funzione relativa a calibrazione con pulsein:
    mid_point3 =  calibraTrim(chPin3) + 8; // La calibrazione in genere non serve
    // su throttle, il valore minimo e' costante e non c'e' TRIM

    attachInterrupt(0, chRise2, RISING); // PIN 2 su 328p / 168
    attachInterrupt(1, chRise3, RISING); // PIN 3 su 328p / 168

} ;


void loop() {
stato.Blink(); // Onboard LED per vedere se la scheda e' accesa

  right.Blink(map(chValue3,980,2020,800,200));
  left.Blink(map(chValue3,980,2020,200,800));
  coda.Blink(chValue2 /4);
  motore.lSet((chValue2 -980) / 4);
  seq.Update(map(chValue2,980,2000,300,40));

}

// Functions
void chRise2() {
    attachInterrupt(0, chFall2, FALLING);
    chStart2 = micros();
}

void chFall2() {
    attachInterrupt(0, chRise2, RISING);
    chValue2 = micros() - chStart2;
}
// Seconod iterrupt
void chRise3() {
    attachInterrupt(1, chFall3, FALLING);
    chStart3 = micros();
}

void chFall3() {
    attachInterrupt(1, chRise3, RISING);
    chValue3 = micros() - chStart3;
}
