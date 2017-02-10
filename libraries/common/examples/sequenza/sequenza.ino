/*
  For Loop with millis()

Blink di un array di led in sucessione,
utilizzando millis() per non blocking.
L'array puo' contenere un numero arbitrario di led
(l'ordine in cui compaiono e' l'ordine in cui brillano).

OOP version.

 Schemi:
 - http://lab.piffa.net/schemi/8_led_single_res_bb.png
 - http://lab.piffa.net/schemi/8_led_single_res_schem.png

 http://www.arduino.cc/en/Tutorial/ForLoop
 */
#include <common.h>
void setup() {
};

byte pins[] = {  // PIN dei LED che compongono la sequenza
  2, 3, 4, 5, 6, 7
}; 
Sequenza seq = Sequenza(pins,sizeof(pins)); // Array dei PINs, quanti elementi compongono l'array

void loop() {
  seq.Update(200); // Passa al segmento successivo ogni 200ms
};



