/* Ereditarieta'
   
   La classe SuperLED definita in questo sketch
   eredita le caratteristiche di RGBLed e introduce un nuovo metodo
   per un nuovo colore custom.

*/

#include <common.h> // L'orine e' importante: prima l'include,
                    // poi la dichiarazione della nuova classe (non a fondo pagina)
                    // poi potremo usare la nuova classe

class SuperLED : public RGBLed { // Ereditamo dalla classe RGBLed
    // Nuovi colori per RGBLed

  using RGBLed::RGBLed ;  // Richiamiamo il constructor del genitore
  public:
    void Violet () {        // Nuovo metodo
    // Accende il LED di viola

          analogWrite(redPin,   255 - 238);
          analogWrite(greenPin, 255 - 130);
          analogWrite(bluePin,  255 - 238);
        };
};

void setup() {
  // I PINs vengono impostati dalla dichiarazione dell'ogetto.
}

// Instanziamo un LED
SuperLED led(11, 10, 9); //Istanziamo un oggetto led facente parte
                         // della inuova classe SuperLed che eredita da RGBLed

void loop() {
  led.Violet(); // Nuovo metodo
  delay(1000);
  led.Off();    // Vecchio metodo
  delay(1000);  
}

