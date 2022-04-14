
// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int count = 0;
int active = 1;
int fin = 0;
int limitRep = 30;
int tmpPause = 30;
  
void setup() {
  pinMode(10, INPUT);
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("NB DE REPETITION:");
}

void loop() {
  // recuperation de l'etat du capteur
  int currentState = digitalRead(10);
  Serial.print("Current state: ");
  Serial.println(currentState);
  
  if(count == limitRep){
  	fin = 1;
  } 
  
  if (active == 1 && currentState == 1 && fin == 0){
  	active = 0;
    count++;
  }
  if (active == 0 && currentState == 0 && fin == 0){
  	active = 1;
  }
  
  // Affichage du nombre de repetition
  if (fin == 0){
    lcd.setCursor(0, 1);
  	lcd.print(count);
  } else {
    // fin de la serie
    lcd.clear();
  	lcd.print("FIN DE SERIE");
    delay(3000);
    
    for (int i=tmpPause; i>0; i--){
		lcd.clear();
    	lcd.print("Reprise dans ");
  		lcd.print(i);
      	delay(1000);
    }
    
    lcd.clear();
    lcd.print("NB DE REPETITION:");
	count = 0;
	active = 1;
	fin = 0;
    
  }
}

 