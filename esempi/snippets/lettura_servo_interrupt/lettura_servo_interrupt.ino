
/* Lettura di un canale servo della RX

   Lettura tramite uno dei due external interrupt ala Arduino
   Utilizzabile solo sui PIN 2-3

*/

#include <common.h>
#define DEBUG

// Variabili per interrupt 0
volatile unsigned int chValue = 1500; // Valore computato
volatile unsigned int chStart = 1500; // Inizio rilevamento

// Variabili per autocalibrazione
const byte chPin = 2; // PIN per la calibrazione
int mid_point = 1500;

void setup() {
    // Funzione relativa a calibrazione con pulsein:
//    mid_point =  calibraTrim(chPin) ; // Calibrazione del TRIM attivo sul canale
    attachInterrupt(0, chRise, RISING); // PIN 2 su 328p / 168
#ifdef DEBUG
Serial.begin(9600); // Warning: interrupts e serial potrebbero dare problemi
} ;
#endif

void loop() {
#ifdef DEBUG
    Serial.print(chValue);
    Serial.print(" - base: ");
    Serial.println(mid_point);
    delay(200);
#endif
}

// ISR:
void chRise() {
    attachInterrupt(0, chFall, FALLING);
    chStart = micros();
}

void chFall() {
    attachInterrupt(0, chRise, RISING);
    chValue = micros() - chStart;
}
