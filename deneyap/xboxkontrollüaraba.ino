#include "deneyap.h"
#include <XboxSeriesXControllerESP32_asukiaaa.hpp> 

XboxSeriesXControllerESP32_asukiaaa::Core xboxController("68:6c:e6:56:a7:b2");

int sagileri = D0;
int saggeri = D1;
int solileri = D12;
int solgeri = D13;
int ENApin= D8;
int ENBpin =D14;

void setup() {
  Serial.begin(115200); 
  xboxController.begin();
  pinMode(sagileri, OUTPUT);
  pinMode(saggeri, OUTPUT);
  pinMode(solileri, OUTPUT);
  pinMode(solgeri, OUTPUT);
  pinMode(ENApin , OUTPUT);
  pinMode(ENBpin, OUTPUT);
}

void hareket(int sag, int sag_geri, int sol, int sol_geri,int hiz) {
  digitalWrite(sagileri, sag);
  digitalWrite(saggeri, sag_geri);
  digitalWrite(solileri, sol);
  digitalWrite(solgeri, sol_geri);
  analogWrite(ENApin , hiz);
  analogWrite(ENBpin, hiz);
}

void loop() {
  xboxController.onLoop();
  if(xboxController.isConnected()) {
    int yValuesol = xboxController.xboxNotif.joyLVert;  
    int xValuesol = xboxController.xboxNotif.joyLHori;  
    //int yValuesag = xboxController.xboxNotif.joyRVert;
    //int xValuesag = xboxController.xboxNotif.joyRHori;

    if(yValuesol < 25000 ){
      int motorHiz = map(yValuesol , 25000 , 0 , 70, 255);
      hareket(HIGH,LOW,HIGH,LOW,motorHiz);
    }
    else if(yValuesol > 43000){
      int motorHiz = map(yValuesol , 43000 , 65535 , 70, 255);
      hareket(LOW,HIGH,LOW,HIGH,motorHiz);
    }
    else if(xValuesol < 26000){
      int motorHiz= map(xValuesol , 26000 , 0 , 70,255);
      hareket(LOW,HIGH,HIGH,LOW,motorHiz);
    }
    else if(xValuesol >40000){
      int motorHiz = map(xValuesol , 40000, 65535 , 70, 255);
      hareket(HIGH,LOW,LOW,HIGH,motorHiz);
    }
    else if(yValuesol> 25000 && yValuesol< 43000 && xValuesol>26000 && xValuesol<40000){ 
      analogWrite(ENApin, 0);
      analogWrite(ENBpin , 0);
    }

    

    delay(200);
  }
}
