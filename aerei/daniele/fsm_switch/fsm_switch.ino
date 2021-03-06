/* Aereo di Daniele

FSM: il throttle e' a posto
Prototipo: F8 Bearcat

Output:
   2 LED PWM ai lati con lampeggio alternato
   2 LED PWM alle estremita ali

Input:
    2 interrupts per th e alettone
    PIN 2:  alettone
    PIN 3:  throttle
    PIN A1: interruttore On/Off


NOTE: aggiunta libreria aero per gestione interruttore,
	  da testare.

    TODO
* testare
* Vedere la calibrazione automatica
* Min e max a 1000 - 2000 per alettone

*/

#include <common.h>
#include <aero.h>
# define dEBUG

// Instanziamo un LED fuori dal loop
Lampeggiatore left = 6;
Lampeggiatore right = 9;
Lampeggiatore codasx = 5;
Lampeggiatore codadx = 10;

Pwm pleft = 6;
Pwm pright = 9;
Pwm pcodasx = 5;
Pwm pcodadx = 10;

// Variabili per interrupt 0 si PIN 2
volatile unsigned int chValue2 = 1500; // Valore computato
volatile unsigned int chStart2 = 1500; // Inizio rilevamento

// Variabili per interrupt 1 su PIN 3
volatile unsigned int chValue3 = 1500; // Valore computato
volatile unsigned int chStart3 = 1500; // Inizio rilevamento

const byte chPin = A1; // PIN interruttore generale

// Variabili per autocalibrazione 0
const byte chPin2 = 2; // PIN per la calibrazione alettone
int mid_point2 = 1500;

// Variabili per autocalibrazione 1
const byte chPin3 = 3; // PIN per la calibrazione
int mid_point3 = 1000;

// Variabili
int caso ;
int thrBit;

void setup() {
  // I PINs vengono impostati dal constructor al momento
  // della dichiarazione dell'ogetto.
right.Invert();
codadx.Invert();

  // HI -> LOW --> LOW -> HI
  // per avere 2 LED che lampeggiano alternativamente
    // Funzione relativa a calibrazione con pulsein:
    mid_point2 =  calibraTrim(chPin2) ; // Calibrazione del TRIM attivo sul canale
    //mid_point3 =  calibraTrim(chPin3) ; // Calibrazione del TRIM attivo sul canale
    attachInterrupt(0, chRise2, RISING); // PIN 2 su 328p / 168
    attachInterrupt(1, chRise3, RISING); // PIN 3 su 328p / 168
#ifdef dEBUG
Serial.begin(9600); 
#endif
}

void loop() {
if (toggleRead(A0)) { // Interruttore generale
// Gestione throttle
    if (chValue3 < 1050) {
        // IDLE
//pleft.Up(1000);
//pright.Up(1000);
pcodasx.UD(2000);
pcodadx.UD(2000);
pleft.lUp(1000);
pright.lDown(1000);


    }
    else if (chValue3 > 1900) {
        // Throttle al massimo: LED laterali lampeggiano a caso,
        // Sotto luminosita' a caso
        caso = random(30, 250) ;
pleft.Set(caso); 
pright.Set(caso); 
pcodasx.Set(caso);
pcodadx.Set(caso);
        delay(caso);
    }
    else {
        // Throttle medio
        thrBit = map(chValue3,1050, 1900, 0, 255);
        codasx.Blink(1220 - 4 * thrBit );
        codadx.Blink(1220 - 4 * thrBit );
left.Blink(map(chValue2,1000,2000,200,800 ));
right.Blink(map(chValue2,1000,2000,800,200 ));
    }

#ifdef DEBUG
    Serial.print("PIN2: ");
    Serial.print(chValue2);
    Serial.print(" -base: ");
    Serial.print(mid_point2);

    Serial.print(" |-| PIN3:");
    Serial.print(chValue3);
    Serial.print(" -base: ");
    Serial.println(mid_point3);
    delay(200);
#endif
} else { // Interruttore off
pleft.Set(0); 
pright.Set(0); 
pcodasx.Set(0);
pcodadx.Set(0);
}
}
// Functions
void chRise2() {
    attachInterrupt(0, chFall2, FALLING);
    chStart2 = micros();
}

void chFall2() {
    attachInterrupt(0, chRise2, RISING);
    chValue2 = micros() - chStart2;
}
// Seconod iterrupt
void chRise3() {
    attachInterrupt(1, chFall3, FALLING);
    chStart3 = micros();
}

void chFall3() {
    attachInterrupt(1, chRise3, RISING);
    chValue3 = micros() - chStart3;
}
