#include <Stepper.h>

const int STEPS_PER_REV = 200;
const int sensorPin = 8;
const int motorSteps = STEPS_PER_REV / 10;

Stepper stepper_NEMA17(STEPS_PER_REV, 3, 4, 5, 6);

int count = 0;
int targetCount = 0;
bool motorRunning = false;

void setup() {
  pinMode(sensorPin, INPUT);
  stepper_NEMA17.setSpeed(60);
  Serial.begin(9600);
  Serial.println("Kaç nesne saymak istediğinizi girin:");
}

void loop() {
  if (!motorRunning) {
    if (Serial.available() > 0) {
      targetCount = Serial.parseInt();
      Serial.print("Hedef sayı belirlendi: ");
      Serial.println(targetCount);
      motorRunning = true;
      startMotor(); 
    }
  } else {
    if (count < targetCount) {
      if (digitalRead(sensorPin) == HIGH) {
        count++;
        Serial.print("Sayım: ");
        Serial.println(count);
        delay(50);
        while (digitalRead(sensorPin) == HIGH); 
      }

      stepper_NEMA17.step(motorSteps);
    } else {

      Serial.println("Hedef sayıya ulaşıldı.");
      while (1); 
      stopMotor(); 
    }
  }
}

void startMotor() {
  stepper_NEMA17.setSpeed(60);
  motorRunning = true;
}

void stopMotor() {
  stepper_NEMA17.step(0);
  motorRunning = false;
}