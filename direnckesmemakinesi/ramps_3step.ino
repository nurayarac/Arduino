#include <Arduino.h>

#define X_STEP_PIN A0
#define X_DIR_PIN A1
#define X_ENABLE_PIN 38

#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN A8

#define SENSOR_PIN 3

#define STEPS_PER_REV 200
#define X_STEP_DELAY 700
#define Z_STEP_DELAY 50
#define STEPS_PER_CYCLE 1000
#define INITIAL_DELAY 1000

volatile int detectedCount = 0;
int resistanceCount = 0;
int setCount = 0;
int currentSet = 0;
bool xMotorRunning = false;
bool zMotorsRunning = false;

void setup() {
  Serial.begin(9600);

  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);

  pinMode(SENSOR_PIN, INPUT);

  digitalWrite(X_ENABLE_PIN, HIGH);
  digitalWrite(Z_ENABLE_PIN, HIGH);

  Serial.println("Lütfen direnç sayısını girin:");
  resistanceCount = readInteger();
  Serial.print("Belirlenen direnç sayısı: ");
  Serial.println(resistanceCount);

  Serial.println("Lütfen set sayısını girin:");
  setCount = readInteger();
  Serial.print("Belirlenen set sayısı: ");
  Serial.println(setCount);

  if (setCount <= 0) {
    Serial.println("Geçersiz set sayısı! Set sayısı 1 veya daha büyük olmalıdır.");
    while (true);
  }

  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), detectCut, RISING);
  Serial.println("Başlamaya hazır, dirençleri yerleştirin.");
}

void loop() {
  if (currentSet < setCount) {
    if (!xMotorRunning) {
      startXMotor();
    } else {
      if (detectedCount < resistanceCount) {
        digitalWrite(X_DIR_PIN, HIGH);
        digitalWrite(X_STEP_PIN, HIGH);
        delayMicroseconds(X_STEP_DELAY);
        digitalWrite(X_STEP_PIN, LOW);
        delayMicroseconds(X_STEP_DELAY);
      } else {
        stopXMotor();
        delay(200);
        startZMotors();
        delay(500);
        stopZMotors();
        resetForNextSet();
      }
    }
  } else {
    stopAllMotors();
    Serial.println("Tüm setler tamamlandı. Tüm motorlar durduruldu.");
    while (true);
  }
}

void detectCut() {
  if (xMotorRunning) {
    detectedCount++;
    Serial.print("Sensör tarafından algılanan sayım: ");
    Serial.println(detectedCount);
  }
}

void startXMotor() {
  xMotorRunning = true;
  detectedCount = 0;
  digitalWrite(X_ENABLE_PIN, LOW);
  Serial.println("X motoru çalışıyor.");
}

void stopXMotor() {
  digitalWrite(X_ENABLE_PIN, HIGH);
  xMotorRunning = false;
  detachInterrupt(digitalPinToInterrupt(SENSOR_PIN));
  Serial.println("X motoru durduruldu.");
}

void startZMotors() {
  digitalWrite(Z_ENABLE_PIN, LOW);
  
  digitalWrite(Z_DIR_PIN, LOW);
  moveZMotor();

  delay(1000);

  digitalWrite(Z_DIR_PIN, HIGH);
  moveZMotor();
  
  Serial.println("Z motorları çalışıyor.");
}

void moveZMotor() {
  for (int i = 0; i < STEPS_PER_CYCLE; i++) {
    digitalWrite(Z_STEP_PIN, HIGH);
    delayMicroseconds(Z_STEP_DELAY);
    digitalWrite(Z_STEP_PIN, LOW);
    delayMicroseconds(Z_STEP_DELAY);
  }
}

void stopZMotors() {
  digitalWrite(Z_ENABLE_PIN, HIGH);
  Serial.println("Z motorları durduruldu.");
}

void stopAllMotors() {
  stopXMotor();
  stopZMotors();
}

void resetForNextSet() {
  currentSet++;
  Serial.print("Set ");
  Serial.print(currentSet);
  Serial.println(" tamamlandı, bir sonraki sete geçiliyor.");
  stopZMotors();
  delay(200);
  digitalWrite(X_ENABLE_PIN, LOW);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), detectCut, RISING);
  startXMotor();
}

int readInteger() {
  while (Serial.available() == 0) {}
  int value = Serial.parseInt();
  while (Serial.available() > 0) { Serial.read(); }
  return value;
}
