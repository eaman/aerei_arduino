/* Ailerons state machine

Pilotare un LED RGB in base al canale degli alettoni:

= 3 stati + 2 transizioni:
- piatto
- roll a sx
- roll a dx

Trasizioni per accentuare il cambio di assetto (ad esempio con dei blink
e introdurre un po' di inerzia temporale per il cambio di stato

*/

#include <common.h>

enum  { // Stati della FMS
  middle,   // centrale
  sxin,     // transizione a sx
  sx,       // sx
  dxin,     // transizione a dx
  dx        // dx
} ailstate  = middle;

// Un LED RGB
RGBLed ailerons(11,10,9);

const byte ailPin = A4;
int ail ; // Valore a 8bit per ailerons
int ailIn ; // Valore rilevato del 4 Ch della RX 



void setup() {
/* Bisognerebbe introdurre una calibrazione per compensare i TRIM
   ed eventualmente i dual rates.
- attivarla se allo start un ale e' al massimo
- fargli leggere i valori massimi 
- salvarli in eprom
- per i dual rates: si potrebbe intercettare valori oltre al max
  e in base a questi traslare le soglie automaticamente

Hint: leggere la soglia di rollio significativo in volo
      e inserirla nei riferimenti.
*/

  Serial.begin(9600);
}

void loop() {

 // Lettura Aileron channel: FAKE con un potenziometro
 //ailIn = analogRead(3);
 //ail = constrain(aliIn / 4 , 0, 255) ;

 // Lettura ailerons channel
 ailIn = pulseIn(ailPin, HIGH, 25000);
 if (ailIn != 0) {ail = constrain(ailIn, 1000, 2000); } ;
           // con un altra ricevente, fare una calibrazione nel caso.
           // Middle = 1512


 switch (ailstate) {
     case middle:
       // Alettoni piatti
       if (ail > 1600) { ailstate = sxin; } ;
       if (ail < 1400) { ailstate = dxin; } ;
       ailerons.White();

     break;

   case sxin:
   // Transizione a sx
       ailerons.Off();
       delay(1000);
       ailstate = sx;
     break;

   case sx:
   // dx
       ailerons.Green();
       if (ail < 1600) { ailstate = middle; } ;
       if (ail < 1400) { ailstate = dxin; } ;
     break;

   case dxin:
   // Transizione a dx
       ailerons.Off();
       delay(1000);
       ailstate = dx;
     break;

   case dx:
   // sx
       ailerons.Blue();
       if (ail > 1400) { ailstate = middle; } ;
       if (ail > 1600) { ailstate = dxin; } ;
     break;
  }

  Serial.print("ailIn: ");
  Serial.print(ailIn);
  Serial.print("\tail: ");
  Serial.print(ail);
  Serial.print("\t ailstate:");
  Serial.println(ailstate);
  //  delay(200);
 }
