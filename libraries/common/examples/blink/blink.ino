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

//led.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da 
                // HI -> LOW --> LOW -> HI
                // per avere 2 LED che lampeggiano alternativamente
}

void loop() {
  led.Blink();    // Lampeggia con un default di 1sec (0.5 HI 0.5 LOW) 
//  led.Blink(400);  // Lampeggia ogni 400ms
//  led.Blink(400,200);  // Imposta il tempo acceso e il tempo spento a 400ms, 200ms di ritardo
//  led.Blink(300,700,0);  // acceso per 300ms, spento per 700 ms, ritardo = 0ms
//  led.Blink(300,700,500);  // acceso per 300ms, spento per 700 ms, ritardo = 500s
//  led.High();   // Stato su HI
//  led.Low();    // Stato su LOW
//  led.Swap();   // Inverte lo Stato
}
