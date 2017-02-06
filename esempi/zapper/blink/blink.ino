/*
  Blink v1

  Accensione e spegnimanto di un ledA utilizzando variabili
  per impostare la velocita' del lampeggio.
  
 */

// Pin 13 ha un led collegato di default 
int ledA = 6;
int ledB = 7;

void setup() {                
  // Inizializziamo il PIN 13 come OUTPUT
  pinMode(ledA, OUTPUT);     
  pinMode(ledB, OUTPUT);     
}

void loop() {
  // 1st step
  digitalWrite(ledA, HIGH);   
  delay(150);              
  digitalWrite(ledA, LOW);  
  delay(50);              
  digitalWrite(ledB, HIGH);   
  delay(150);              
  digitalWrite(ledB, LOW);  
  delay(50);              

  // 2st step
  digitalWrite(ledA, HIGH);   
  delay(150);              
  digitalWrite(ledA, LOW);  
  delay(50);              


  // 3st step
  delay(150);            
  digitalWrite(ledA, LOW);  
  digitalWrite(ledB, LOW);  
  delay(50);            
  digitalWrite(ledA, HIGH);   
  digitalWrite(ledB, HIGH);   
  delay(350);              
  digitalWrite(ledA, LOW);  
  digitalWrite(ledB, LOW);  
  delay(50);            


  // Reverse
  // 1st step
  digitalWrite(ledB, HIGH);   
  delay(150);              
  digitalWrite(ledB, LOW);  
  delay(50);              
  digitalWrite(ledA, HIGH);   
  delay(150);              
  digitalWrite(ledA, LOW);  
  delay(50);              

  // 2st step
  digitalWrite(ledB, HIGH);   
  delay(150);              
  digitalWrite(ledB, LOW);  
  delay(50);              


  // 3st step
  delay(150);            
  digitalWrite(ledB, LOW);  
  digitalWrite(ledA, LOW);  
  delay(50);            
  digitalWrite(ledB, HIGH);   
  digitalWrite(ledA, HIGH);   
  delay(350);              
  digitalWrite(ledB, LOW);  
  digitalWrite(ledA, LOW);  
  delay(50);            


}

