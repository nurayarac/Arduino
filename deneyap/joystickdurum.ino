#include "deneyap.h"

int xkonum;
int ykonum;
int butondurum;

void setup() {
  Serial.begin(115200);
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(D0, INPUT_PULLUP);

}

void loop() {
  xkonum= analogRead(A0);
  ykonum= analogRead(A1);
  butondurum= digitalRead(D0);

  Serial.print("x konumu: ");
  Serial.print(xkonum);
  Serial.print(" y konumu: ");
  Serial.print(ykonum);
  Serial.print(" Buton durum: ");
  Serial.println(butondurum);

  delay(1000);

}
