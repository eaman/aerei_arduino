/* Esempio

   Utilizzo dell'oggetto Lampeggiatore:
   Lampeggia un LED utilizzando millis()
*/

#include <common.h>

// Instanziamo un LED fuori dal loop
Lampeggiatore led = 13;

void setup() {
// I PINs vengono impostati dal constructor al momento 
// della dichiarazione dell'ogetto.

led.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da 
                // HI -> LOW --> LOW -> HI
                // per avere 2 LED che lampeggiano alternativamente
}

void loop() {
  led.Blink();    // Lampeggia con un default di 1sec (0.5 HI 0.5 LOW) 
//  led.Blink(500);  // Lampeggia ogni 500ms
//  led.Blink(500,200);  // Imposta il tempo acceso e il tempo spento
//  led.High();   // Stato su HI
//  led.Low();    // Stato su LOW
//  led.Swap();   // Inverte lo Stato
}
