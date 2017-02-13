/* Aereo di Daniele

Prototipo:

Output:
   2 LED ai lati con lampeggio alternato
   1 LED PWM per motore

Input:
    2 interrupts per th e alettone
    PIN 2:  alettone
    PIN 3:  throttle


    TODO
* Vedere la calibrazione automatica
* Min e max a 1000 - 2000 per alettone

*/

#include <common.h>
# define DEBUG

// Instanziamo un LED fuori dal loop
Lampeggiatore left = 5;
Lampeggiatore right = 6;
Lampeggiatore coda = 9;

// Variabili per interrupt 0 si PIN 2
volatile unsigned int chValue2 = 1500; // Valore computato
volatile unsigned int chStart2 = 1500; // Inizio rilevamento

// Variabili per interrupt 1 su PIN 3
volatile unsigned int chValue3 = 1500; // Valore computato
volatile unsigned int chStart3 = 1500; // Inizio rilevamento

// Variabili per autocalibrazione 0
const byte chPin2 = 2; // PIN per la calibrazione alettone
int mid_point2 = 1500;

// Variabili per autocalibrazione 1
const byte chPin3 = 3; // PIN per la calibrazione
int mid_point3 = 1000;


void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.

  // HI -> LOW --> LOW -> HI
  // per avere 2 LED che lampeggiano alternativamente
    // Funzione relativa a calibrazione con pulsein:
    //mid_point2 =  calibraTrim(chPin2) ; // Calibrazione del TRIM attivo sul canale
    //mid_point3 =  calibraTrim(chPin3) ; // Calibrazione del TRIM attivo sul canale
    attachInterrupt(0, chRise2, RISING); // PIN 2 su 328p / 168
    attachInterrupt(1, chRise3, RISING); // PIN 3 su 328p / 168
#ifdef DEBUG
Serial.begin(9600); 
#endif
}

void loop() {

#ifdef DEBUG
    Serial.print("PIN2: ");
    Serial.print(chValue2);
    Serial.print(" -base: ");
    Serial.print(mid_point2);

    Serial.print(" |-| PIN3:");
    Serial.print(chValue3);
    Serial.print(" -base: ");
    Serial.println(mid_point3);
    delay(200);
#endif
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
