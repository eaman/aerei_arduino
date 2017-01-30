/* Esempio

   Come caricare e usare un oggetto e una funzione
   facente parte della libreria.
*/

#include <common.h>

void setup() {
  // I PINs vengono impostati dalla dichiarazione dell'ogetto.
}

// Instanziamo un LED
RGBLed led(11, 10,9); //Istanziamo un oggetto led (common catodo)
// facente parte della classe RGBLed
//RGBLed led(10,9,11,255); // Inizializzazione Common anodo, valori invertiti

void loop() {
  led.White();

}

/* Colori disponibili:
    Red 
    Green 
    Blue 
    Magenta 
    Cyano 
    White 
    Yellow 

Nota: per aggiungerne uno senza modificare la libreria originale
si potrebbe usara l'ereditarieta': vedi esempio "eredita.ino" .
*/
