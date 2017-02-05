/* Calibrazione Trim servo

   Esempio su come calibrare il segnale di un servo.
   I canali come alettoni / elevatore possono avere un TRIM
   (generalmente il throttle non ha un TRIM impostato),
   questa funzione nel setup serve per trovare il punto medio
   all'avvio dello sketch.

*/

#include <common.h>

const byte ailPin = A4;
// int ail ; // Valore a 8bit per ailerons
// int ailIn ; // Valore rilevato del 4 Ch della RX

int mid_point = 1500 ; // centro del segnale, trimmato nel setup

void setup() {
    Serial.begin(9600); // Se abilitato la calibrazione viene tracciata su seriale

    mid_point =  calibraTrim(ailPin) ; // Pin a cui e' collegato il canale
//mid_point =  calibraTrim(aliPin,11) ; // + LED di servizio per calibrazione
    while(1); // Stoppa Arduino
}

void loop() {
}
