/* Esempio

   Utilizzo dell'oggetto PWM:
   Gestione del PWM utilizzando millis
   per non bloccare il processore con delay
*/

#include <common.h>

// Instanziamo un LED fuori dal loop
Pwm led = 9;

void setup() {
// I PINs vengono impostati dal constructor al momento 
// della dichiarazione dell'ogetto.
}

void loop() {
  led.Up(2000);     // Aumenta la luminosita' in 2 sec
  led.Down(1000);   // Diminuisce la luminosita' in 1 sec
  led.UD(4000);     // Aumenta e poi diminuisce la luminostia' in 4 sec.
}
