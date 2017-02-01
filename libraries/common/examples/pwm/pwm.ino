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
led.Up(2000);     // Aumenta la luminosita' linearmente in 2 sec
//led.Up(2000,1000); // Aumenta la luminosita' linearmente in 2 sec, 1sec di ritardo

//led.lUp(2000);     // Aumenta la luminosita' con correzione luminosita' per LED
// led.Down(1000);   // Diminuisce la luminosita' in 1 sec
// led.lDown(1000);   // Diminuisce la luminosita' con correzione luminosita'
// led.UD(4000);     // Aumenta e poi diminuisce la luminostia' in 4 sec (coseno)
// Tutti questi metodi accettano un valore opzionale per il ritardo

// led.set(100);   // Imposta il valore del PWM da 0-255
// led.lSet(100);   // Imposta il valore del PWM con correzione luminosita' 
// analogWrite(lum100); // Equivalente a sopra
}
