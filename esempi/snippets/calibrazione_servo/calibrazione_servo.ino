/* Calibrazione Trim servo

   Esempio su come calibrare il segnale di un servo.
   I canali come alettoni / elevatore possono avere un TRIM
   (generalmente il throttle non ha un TRIM impostato),
   questa funzione nel setup serve per trovare il punto medio
   all'avvio dello sketch.

Nota: questa funzione usa PULSEIN in modo da poter lavorare su
qualunque PIN, considerando che in genere viene eseguita 
una sola volta nel SETUP.

Se si vuole qualcosa non blocking sostituire PULSEIN con 
un interrupt.

*/

#include <common.h>

const byte ailPin = A4;

int mid_point = 1500 ; // centro del segnale, trimmato nel setup

void setup() {
    Serial.begin(9600); // Se abilitato la calibrazione viene tracciata su seriale
    // Abilitando anche DEBUG nella libreria

    mid_point =  calibraTrim(ailPin) ; // Pin a cui e' collegato il canale
//mid_point =  calibraTrim(ailPin,11) ; // + LED di servizio per calibrazione

Serial.print("Valore calibrato: ");
Serial.println(mid_point);
}

void loop() {
}
