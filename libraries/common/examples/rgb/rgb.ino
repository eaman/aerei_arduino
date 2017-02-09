/* Esempio

   Come caricare e usare un oggetto e una funzione
   facente parte della libreria.
*/

#include <common.h>

void setup() {
  // I PINs vengono impostati dalla dichiarazione dell'ogetto.
}

// Instanziamo un LED
RGBLed led(11, 10,9); //Istanziamo un oggetto led (default common catodo)
// facente parte della classe RGBLed
// RGBLed led(11, 10,9,255); // Stessa cosa: 255 = common catodo = (255 - value)
//RGBLed led(10,9,11,0); // Inizializzazione Common anodo

void loop() {
  led.Red();
}

/* Colori disponibili:
    Red 
    Green 
    Blue 
    Magenta 
    Cyano 
    White 
    Yellow 
    Off
    Rand = random
    SetColor(byte r, byte g, byte b)

Nota: per aggiungerne un colore senza modificare la libreria originale
si potrebbe usara l'ereditarieta': vedi esempio "eredita.ino" .
*/
