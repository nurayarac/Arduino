#include <Stepper.h>
#define STEPS 200
Stepper myStepper(STEPS, 4, 5, 6, 7);

int A = 0; 
int B = 0; 
int nos = 35; 
String inputString = ""; 
bool newData = false; 
bool receivingSteps = true; 

void setup() {
  Serial.begin(9600); 
  myStepper.setSpeed(60); 
  Serial.println("adım sayısını girin:");
}

void loop() {
  receiveSerialData();
  
  if (newData) {
    if (receivingSteps) {
      A = inputString.toInt(); 
      Serial.print("Girilmiş Adım Sayısı: ");
      Serial.println(A);
      Serial.println("Set sayısını girin:");
      receivingSteps = false; 
    } else {
      B = inputString.toInt(); 
      Serial.print("Girilmiş Set Sayısı: ");
      Serial.println(B);
      for (int i = 0; i < B; i++) {
        int stepsToMove = A * nos; 
        Serial.print("Motor şu kadar adım atacak: ");
        Serial.println(stepsToMove);
        myStepper.step(stepsToMove); 
        delay(500); 
      }
      receivingSteps = true; 
      Serial.println("Adım motoru kontrolü için adım sayısını girin:");
    }
    inputString = ""; 
    newData = false; 
  }
}

void receiveSerialData() {
  while (Serial.available() > 0) {
    char inChar = (char)Serial.read(); 
    if (inChar == '\n') { 
      newData = true;
    } else {
      inputString += inChar; 
    }
  }
}
