/*
  Common Class

  Oggetti comuni

*/

#include "Arduino.h"
#include <avr/pgmspace.h>

#ifndef common_h
#define common_h

// Variabili
const uint8_t BCORRECT[256] PROGMEM = { // Tabella per correzione luminosita' PWM
   0,0,0,1,1,1,2,1,1,2,1,2,2,2,3,2,
   2,2,3,2,2,3,2,3,3,3,4,3,3,3,4,4,
   4,5,4,5,4,5,5,6,5,5,6,5,6,6,7,6,
   7,7,8,7,8,8,9,8,9,10,9,10,10,11,10,11,
   11,12,11,12,13,12,13,13,14,14,15,15,15,16,16,17,
   17,17,18,18,19,19,20,20,21,21,22,22,23,23,24,24,
   25,25,26,26,27,28,28,29,29,30,31,31,32,32,33,34,
   34,35,36,37,37,38,39,39,40,41,42,43,43,44,45,46,
   47,47,48,49,50,51,52,53,54,54,55,56,57,58,59,60,
   61,62,63,64,65,66,67,68,70,71,72,73,74,75,76,77,
   79,80,81,82,83,85,86,87,88,90,91,92,94,95,96,98,
   99,100,102,103,105,106,108,109,110,112,113,115,116,118,120,121,
   123,124,126,128,129,131,132,134,136,138,139,141,143,145,146,148,
   150,152,154,155,157,159,161,163,165,167,169,171,173,175,177,179,
   181,183,185,187,189,191,193,196,198,200,202,204,207,209,211,214,
   216,218,220,223,225,228,230,232,235,237,240,242,245,247,251,255
};

// Inserirne una con 32 valori


class RGBLed {
  // Classe rappresentativa di un LED RGB
  protected:    // Vedi esempio Ereditarieta'
    byte redPin ;
    byte greenPin ;
    byte bluePin ;
    byte redValue ;
    byte greenValue ;
    byte blueValue ;

  public:
    RGBLed (byte pinR, byte pinG, byte pinB) ;
	void SetColor (byte r, byte g, byte b) ;
	void Red ();
    void Green ();
    void Blue ();
    void Magenta ();
    void Cyano ();
    void White ();
    void Yellow ();
    void Off ();
};



class Lampeggiatore {
    // Lampeggia un LED utilizzando millis()
    // Variabili
    int ledPin ;           // il numero del LED pin
    long interval ;        // milliseconds di intervallo nel lampeggiare
    unsigned long previousMillis ;  // precedente cambio di stato
    int ledState ;         // stato attuale del LED, pubblico per invertirlo

    // Constructor: come viene instanziato un oggetto facente parte della classe
public:
    Lampeggiatore(int pin);
    void Invert();   // Inverte il lampeggio 
    void Blink(); 	// Lampeggia ogni 500ms
    void Blink(long interval); // Lampeggia inpostando l'intervallo
    void Blink(long on, long down); // Imposta il tempo acceso e il tempo spento
};



////////////////////////////
class Pwm {
    /*
       PWM per un LED: aumentare progressivamente la luminosita'.
       Utilizza la funzione millis() invece che un delay()
       in modo da non blocare il processore.
    */
    // Variabili
    int ledPin ;           // il numero del LED pin
    int speed ;            // velocita' del ciclo in ms
    unsigned long previousMillis ;  //precedente cambio di stato
    byte increment ;        // aumenta brighteness nel loop UD

    // Constructor: come viene instanziato un oggetto facente parte della classe
public:
    Pwm(int pin);  // numero di pin, velocita' di ciclo
    void Up(long speed);
    void Down(long speed);
    void UD(long speed);
    byte brightness  ;      // luminostia' iniziale
};



////////////////////////////
class Sequenza {
    // Lampeggia LED in sequenza utilizzando millis()
    unsigned long previousMillis ;
    byte i = 0;
    byte *ledPins;
    byte size;
    int inc = 1;
    long interval;
    
  public:
    Sequenza (byte passed[], byte dim) ; // Array contentente i PINS, dimensioni array
    void Update(long value) ;  // Accende in sequenza
    void Reverse(long value) ; // Invertita
    void UD(long value) ; // Up & Down
};
















//////////////////////
// Funzioni

void brilla(byte pin, int velocita = 200) ;
#endif

byte lum(byte val);
