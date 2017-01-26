/* Esempio

   Come caricare e usare un oggetto e una funzione
   facente parte della libreria.
*/

#include <common.h>

void setup() {
  // I PINs vengono impostati dalla dichiarazione dell'ogetto.
}

// Instanziamo un LED
RGBLed led(11, 10, 9); //Istanziamo un oggetto led facente parte
                       // della classe RGBLed

void loop() {
  led.Red();
  delay(1000);
  led.SetColor(255, 0, 255) ; // Mettiamo il LED in Green
  delay(1000);
  led.Off();
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
