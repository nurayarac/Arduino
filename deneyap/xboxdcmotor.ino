#include <XboxSeriesXControllerESP32_asukiaaa.hpp>

int m11 = D8; 
int m12 = D1; 

XboxSeriesXControllerESP32_asukiaaa::Core xboxController("68:6c:e6:56:a7:b2");

void setup() {
  Serial.begin(115200);
  xboxController.begin();
  
  pinMode(D8, OUTPUT);
  pinMode(D1, OUTPUT);
}

void loop() {
  xboxController.onLoop();  
  if (xboxController.isConnected()) {
    uint16_t yValue = xboxController.xboxNotif.joyLVert;  
    
    if (yValue <= 28000) {  
      motor(m11, m12, map(yValue, 0, 28000, 0, 255), 0);  
      //Serial.print("y:");
     // Serial.println(yValue);
    }
   
    else if (yValue > 36000) {  
      motor(m11, m12, 0, map(yValue, 36000, 65535, 0, 255));  
     // Serial.print("y:");
     // Serial.println(yValue);
    }
    else {
      motor(m11, m12, 0, 0);  
      //Serial.print("y:");
      //Serial.println(yValue);
    }
  } else {
    Serial.println("Bağlantı yok");
    if (xboxController.getCountFailedConnection() > 2) {
      ESP.restart();  
    }
  }

  delay(200);  
}

void motor(int motorpin1, int motorpin2, int i, int j) {
  if ((i == 0 && j == 0) || (i > 0 && j > 0)) {
    digitalWrite(motorpin1, LOW);  
    digitalWrite(motorpin2, LOW);
  } else {
    analogWrite(motorpin1, i);  
    analogWrite(motorpin2, j);
  }
}
