/* Cirso TransStates

Output:
   2 LED ai lati con lampeggio alternato
   1 LED in coda lampeggio a freq doppia

Input:
   1 interruttore su interrupt 0 per accensione / spegnimento luci

FSM per la gesrione delle transizioni tra i 2 stati.

*/

#include <common.h>

// FSM gestione interruttore luci
enum  { // Stati della FMS
    On,     // Acceso
    toOff,  // Trans On -> Off
    Off,    // Spento
    toOn    // Trans OFF -> On
} toggle  = Off;

// Variabili per interrupt 0
volatile unsigned int chValue = 1500; // Valore computato
volatile unsigned int chStart = 1500; // Inizio rilevamento
const int soglia = 1400; // soglia per scatto toggle a 2 posizioni

// Var FSM
unsigned long FSM_lastMillis = 0 ; // Timestamp per la FSM degli alettoni
unsigned long pausa = 2000;  // Pausa per la transizione durante gli stati 2, 4 della FSM

// Instanziamo gli oggetti per gli stati On / Off
Lampeggiatore left = 5;
Lampeggiatore right = 6;
Lampeggiatore coda = 9;

// Instanziamo gli oggetti per gli stati di transizione
Pwm leftPWM = 5;
Pwm righatPWM = 6;
Pwm codaPWM = 9;

void setup() {
    // I PINs vengono impostati dal constructor al momento
    // della dichiarazione dell'ogetto.

    right.Invert() ;  // Opzionale: inverte l'ordine del lampeggio da
    // HI -> LOW --> LOW -> HI
    // per avere 2 LED che lampeggiano alternativamente
}

void loop() {

switch (toggle) {
    case Off:
    // Spento
        left.Low();
        right.Low();
        coda.Low();

        if (chValue > soglia) {
            FSM_lastMillis = millis();
            toggle = toOn ; 
        }
        break;

    case On:
    // Acceso
        left.Blink();   // Lampeggia con un default di 1sec (0.5 HI 0.5 LOW)
        right.Blink();
        coda.Blink(1000); // Lampeggio in 1000ms = 1 secondo

        if (chValue <= soglia) {
            FSM_lastMillis = millis();
            toggle = toOff ; 
        }
        break;

    case ToOn:
    // Trans off -> on
        leftPWM.lUp(pausa);   
        rightPWM.lUp(pausa);
        codaPWM.lUp(pausa);

        if (chValue > soglia && currentMillis - pausa > FSM_lastMillis ) { 
            toggle = On ; 
        } else if  (chValue <= soglia) {
            toggle = Off ; 
        }
        break;

    case ToOff:
    // Trans on -> off
        leftPWM.lDown(pausa);   
        rightPWM.lDown(pausa);
        codaPWM.lDown(pausa);

        if (chValue <= soglia && currentMillis - pausa > FSM_lastMillis ) { 
            toggle = Off ; 
        } else if  (chValue > soglia) {
            toggle = On ; 
        }
        break;
} ;
}

// Functions
void chRise() {
    attachInterrupt(0, chFall, FALLING);
    chStart = micros();
};

void chFall() {
    attachInterrupt(0, chRise, RISING);
    chValue = micros() - chStart;
};
