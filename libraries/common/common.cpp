/*  Common
 *
 *  Oggetti di uso comune
 */

#include "Arduino.h"
#include "common.h"


//////////////////////
// RGB LED
// Common anode

RGBLed::RGBLed(byte pinR, byte pinG, byte pinB) {
      redPin    = pinR ;
      greenPin  = pinG ;
      bluePin   = pinB ;

      // Equvalente del Setup() per inizializzare i PIN
      pinMode(redPin, OUTPUT);
      pinMode(greenPin, OUTPUT);
      pinMode(greenPin, OUTPUT);
};

void RGBLed::SetColor (byte r, byte g, byte b) {
// Imposta il colore di un LED RGB
      analogWrite(redPin,   r);
      analogWrite(greenPin, g);
      analogWrite(bluePin,  b);
    };

void RGBLed::Red () {
// Accende il LED di rosso
      SetColor(0,255,255);
    };

void RGBLed::Green () {
// Accende il LED di verde
      SetColor(255,0,255);
    };

void RGBLed::Blue () {
// Accende il LED di blu
      SetColor(255,255,0);
    };

void RGBLed::Magenta () {
// Accende il LED di magenta
      SetColor(0,255,0);
    };

void RGBLed::Cyano () {
// Accende il LED di Cyano
      SetColor(255,0,0);
    };

void RGBLed::Yellow () {
// Accende il LED di giallo
      SetColor(0,0,255);
    };

void RGBLed::White () {
// Accende il LED 
      SetColor(0,0,0);
    };

void RGBLed::Off () {
// Spegne il LED 
      SetColor(255,255,255);
    };



/////////////////////////////////////
// Lampeggiatore
// Constructor
Lampeggiatore::Lampeggiatore(int pin)
{
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    ledState = LOW;
    previousMillis = 0;
    interval = 500;
};

// Una funzione facente parte di una classe prende il nome di "metodo" della stessa:
void Lampeggiatore::Invert() {
    // Inverte il lampeggio
    ledState = HIGH ;
}

void Lampeggiatore::Blink() {
    // Illumina il led a 500ms

    if(millis() - previousMillis > interval) {
        // save the last time you blinked the LED
        previousMillis = millis();

        // if the LED is off turn it on and vice-versa:
        ledState = !ledState ; // Inverti il LED
    }
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
};

void Lampeggiatore::Blink(long time) {
    // Illumina il led secondo un intervallo passato come argomento

    if(millis() - previousMillis > time) {
        // save the last time you blinked the LED
        previousMillis = millis();

        // if the LED is off turn it on and vice-versa:
        ledState = !ledState ; // Inverti il LED
    }
    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
};

void Lampeggiatore::Blink(long up, long down) {
    // Illumina il ledB precisando ontime e downtime

    if((ledState == HIGH)&& (millis() - previousMillis > up)) {
    // save the last time you blinked the LED
    	previousMillis = millis();
        ledState = LOW  ;
    }
    else if((ledState == LOW)&& (millis() - previousMillis > down)) {
    	previousMillis = millis();
        ledState = HIGH  ;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(ledPin, ledState);
};

/////////////////////////////////////
// Pwm
// Constructor
Pwm::Pwm(int pin)
    // Gestione del PWM utilizzando millis
    // per non bloccare il processore con delay
    // Warning: serialWrite puo' interferire con i tempi.
{
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
    previousMillis = 0;
    byte brightness = 0 ;
    increment = 1;
};

void Pwm::Up(long speed) {
    // Aumenta progressivamente la luminosita' usanndo millis()
    // quindi senza bloccare il processore
    // Viene usato un float, in alternativa un coseno

    if (millis() != previousMillis)  { // si potrebbe togliere
            brightness = 255.0 /(float)speed * millis() ;
            analogWrite(ledPin, brightness);

        previousMillis = millis();
    };
}

void Pwm::Down(long speed ) {
    // Riduce progressivamente la luminosita' usanndo millis()
    // quindi senza bloccare il processore

    if (millis() != previousMillis)  {
            brightness = 255 - 255.0 /(float)speed * millis() ;
            analogWrite(ledPin, brightness);

        previousMillis = millis();
    };
}

void Pwm::UD(long speed ) {
    // Aumenta e riduce in sequenza la luminosita' usanndo millis()
    brightness = 128 + 127 * cos(2 * PI / speed * millis());
    analogWrite(ledPin, brightness);  
}


/////////////////////////////////////
// Sequenza
// Constructor
Sequenza::Sequenza (byte passed[], byte dim) {
    ledPins = passed ;
    size = dim ;
    for (int thisPin = 0; thisPin < size; thisPin++) {
        pinMode(ledPins[thisPin], OUTPUT);
    }
    previousMillis = millis();
    digitalWrite(ledPins[0], HIGH);
}

void Sequenza::Update(long value) {
    // Incrementa dal primo all'ultimo valore dell'array
    interval = value;
    if (millis() - previousMillis >= interval) {
        previousMillis = millis();

        if ( i < size - 1 ) {
            // Spegni precedente led
            digitalWrite(ledPins[i], LOW);

            // Accendi successivo led
            digitalWrite(ledPins[++i], HIGH);
        }

        else if  (i == size - 1 )   {
            // Ultimo caso
            i = 0;
            previousMillis = millis();
            digitalWrite(ledPins[i], HIGH);
            digitalWrite(ledPins[ size - 1 ], LOW);
        }
    }
}


void Sequenza::Reverse(long value) {
    interval = value;
    if (millis() - previousMillis >= interval) {
        previousMillis = millis();

        if  (i == 0)   { // Entry point, ultimo LED
            digitalWrite(ledPins[size -1],HIGH);
            digitalWrite(ledPins[0],LOW);
            i = size -1 ;
        }
        else {
            digitalWrite(ledPins[i],LOW);
            digitalWrite(ledPins[--i],HIGH);
        }
    }
}

void Sequenza::UD(long value) {
    interval = value;
    if (millis() - previousMillis >= interval) {
        previousMillis = millis();
        // Spegni precedente led
        digitalWrite(ledPins[i], LOW);
        i = i + inc ;
        // Accendi successivo led
        digitalWrite(ledPins[i], HIGH);

        if (i == 0 || i == size -1) {
            inc = -inc ;
        }
    }
}


//////////////////
// Funzioni


void brilla(byte pin, int velocita ) { // Defalt value di velocita' solo nell'Header
  // Accende e spegne il LED accetando un argomento 
  // per impostare la velocita'.

pinMode(pin, OUTPUT); 
  // sequenze di istruzione: accendere e spegnere il LED
  digitalWrite(pin, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(velocita);               // wait for a second
  digitalWrite(pin, LOW);    // turn the LED off by making the voltage LOW
  delay(velocita);               // wait for a second
};


byte lum(byte val) { 
    // Mappatura dell'intervallo 0-255 con correzione di luminosita.
    // storata in SRAM
return pgm_read_byte_near(BCORRECT + val);
};
