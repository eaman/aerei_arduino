/* Toggle con transizioni tra On | OFF con interrupt


Sketch di esempio per accensione spegnimento di tutto l'impianto luci
tramite un interruttore a due posizioni della radio.

Output esempio: 
   1 Lampeggiatore in coda in PWM

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
Lampeggiatore coda = 9;

// Instanziamo gli oggetti per gli stati di transizione
Pwm codaPWM = 9;

void setup() {

}

void loop() {

switch (toggle) {
    case Off:
    // Spento
        coda.Low();

        if (chValue > soglia) {
            FSM_lastMillis = millis();
            toggle = toOn ; 
        }
        break;

    case On:
    // Acceso
        coda.Blink(1000); // Lampeggio in 1000ms = 1 secondo

        if (chValue <= soglia) {
            FSM_lastMillis = millis();
            toggle = toOff ; 
        }
        break;

    case ToOn:
    // Trans off -> on
        codaPWM.lUp(pausa);

        if (chValue > soglia && currentMillis - pausa > FSM_lastMillis ) { 
            toggle = On ; 
        } else if  (chValue <= soglia) {
            toggle = Off ; 
        }
        break;

    case ToOff:
    // Trans on -> off
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
