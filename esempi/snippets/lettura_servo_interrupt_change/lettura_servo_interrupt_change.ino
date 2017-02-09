
/* Lettura di un canale servo della RX

   Lettura tramite i pin change interrupts
   Utilizzabile su tutti i PINS

- http://playground.arduino.cc/Main/PinChangeInterrupt

*/

#include <common.h>


// Variabili per interrupt 0
unsigned int chValue = 1500; // Valore computato
unsigned int chStart = 1500; // Inizio rilevamento

// Variabili per autocalibrazione
const byte chPin = 2; // PIN per la calibrazione
int mid_point = 1500;

void setup() {
 pinMode(13,OUTPUT);  // LED
    // Funzione relativa a calibrazione con pulsein:
    mid_point =  calibraTrim(chPin) ; // Calibrazione del TRIM attivo sul canale
  pciSetup(10);
Serial.begin(9600); // Warning: interrupts e serial potrebbero dare problemi
} ;

void loop() {
    Serial.print(chValue);
    Serial.print(" - ");
    Serial.println(mid_point);
    delay(200);
}

// Functions
// Install Pin change interrupt for a pin, can be called multiple times
void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

ISR (PCINT0_vect) // handle pin change interrupt for D8 to D13 here
 {    
     digitalWrite(13,digitalRead(8) and digitalRead(9));
 } 
