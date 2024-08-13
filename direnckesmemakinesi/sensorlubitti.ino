#include <Stepper.h>
#include <Servo.h>

const int STEPS_PER_REV = 200;
const int sensorPin = 3; 
const int motorSteps = STEPS_PER_REV / 100;

Stepper stepper_NEMA17(STEPS_PER_REV, 4, 5, 6, 7);
Servo deneme1;
Servo deneme2;
int pos = 0;

volatile int count = 0;      
int targetCount = 0;
int setCount = 0;
int currentSet = 0;
volatile bool motorRunning = false; 

void setup() {
  pinMode(sensorPin, INPUT);
  stepper_NEMA17.setSpeed(30);
  deneme1.attach(8);
  deneme2.attach(9);
  Serial.begin(9600);
  deneme1.write(0);   
  deneme2.write(90);  
  delay(1000);  
  Serial.println("Kaç nesne saymak istediğinizi girin:");
  
 
  attachInterrupt(digitalPinToInterrupt(sensorPin), detectCut, RISING);

}

void loop() {
  if (!motorRunning) {
    if (Serial.available() > 0) {
      String input = Serial.readStringUntil('\n');
      targetCount = input.toInt();
      
      if (targetCount > 0) { 
        Serial.print("Hedef sayı belirlendi: ");
        Serial.println(targetCount);

        Serial.println("Kaç set yapmak istediğinizi girin:");
        while (Serial.available() <= 0) {
          // Kullanıcıdan set sayısı girilmesini bekler
        }

        input = Serial.readStringUntil('\n');
        setCount = input.toInt();
        
        if (setCount > 0) { 
          Serial.print("Set sayısı belirlendi: ");
          Serial.println(setCount);
          motorRunning = true;
        }
      }
    }
  } else {
    if (count < targetCount) {
      stepper_NEMA17.step(motorSteps);
    } else {
      stopMotor();
      Serial.print("Set ");
      Serial.print(currentSet + 1);
      Serial.println(" tamamlandı.");
      moveServos(); 
      count = 0;  
      currentSet++;

      if (currentSet < setCount) {
        delay(1000);  
        startMotor();
      } else {
        Serial.println("Tüm setler tamamlandı.");
        while (1); 
      }
    }
  }
}

void detectCut() {
  count++;
  Serial.print("Sayım: ");
  Serial.println(count);
}

void startMotor() {
  stepper_NEMA17.setSpeed(60);
  motorRunning = true;
}

void stopMotor() {
  
  stepper_NEMA17.step(0);
  motorRunning = false;
}

void moveServos() {
  
  for (pos = 0; pos <= 90; pos += 1) {
    deneme1.write(pos);
    deneme2.write(90 - pos);
    delay(10);
  }
       
  for (pos = 90; pos >= 0; pos -= 1) {
    deneme1.write(pos);
    deneme2.write(90 - pos);
    delay(10);
  }
}
