#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
int m11 = D8; 
int m12 = D1; 

XboxSeriesXControllerESP32_asukiaaa::Core xboxController("68:6c:e6:56:a7:b2");

struct Button {
  const char* name;
  bool* state;
  void (*action)();
};

void actionA() { Serial.println("🎮 A Tuşuna Basıldı!"); }
void actionB() { Serial.println("🎮 B Tuşuna Basıldı!"); }
void actionX() { Serial.println("🎮 X Tuşuna Basıldı!"); }
void actionY() { Serial.println("🎮 Y Tuşuna Basıldı!"); }
void actionRB() { Serial.println("🎮 RB Tuşuna Basıldı! Motor çalıştırılıyor...");  }
void actionLB() { Serial.println("🎮 LB Tuşuna Basıldı! Motor durdu.");  }
void actionStart() { Serial.println("🎮 Start Tuşuna Basıldı!"); }
void actionSelect() { Serial.println("🎮 Select Tuşuna Basıldı!"); }
void actionDpadUp() { Serial.println("🎮 D-Pad Yukarı!"); }
void actionDpadDown() { Serial.println("🎮 D-Pad Aşağı!"); }
void actionDpadLeft() { Serial.println("🎮 D-Pad Sol!"); }
void actionDpadRight() { Serial.println("🎮 D-Pad Sağ!"); }


Button buttons[] = {
  {"A", &xboxController.xboxNotif.btnA, actionA},
  {"B", &xboxController.xboxNotif.btnB, actionB},
  {"X", &xboxController.xboxNotif.btnX, actionX},
  {"Y", &xboxController.xboxNotif.btnY, actionY},
  {"RB", &xboxController.xboxNotif.btnRB, actionRB},
  {"LB", &xboxController.xboxNotif.btnLB, actionLB},
  {"Start", &xboxController.xboxNotif.btnStart, actionStart},
  {"Select", &xboxController.xboxNotif.btnSelect, actionSelect},
  {"DpadUp", &xboxController.xboxNotif.btnDirUp, actionDpadUp},
  {"DpadDown", &xboxController.xboxNotif.btnDirDown, actionDpadDown},
  {"DpadLeft", &xboxController.xboxNotif.btnDirLeft, actionDpadLeft},
  {"DpadRight", &xboxController.xboxNotif.btnDirRight, actionDpadRight}
};

void setup() {
  Serial.begin(115200);
  xboxController.begin();

  pinMode(m11, OUTPUT);
  pinMode(m12, OUTPUT);
}

void loop() {
  xboxController.onLoop();

  if (xboxController.isConnected()) {
    uint16_t yValue = xboxController.xboxNotif.joyLVert;
    if (yValue >= 28000 && yValue <= 36000) {
      motor(m11, m12, 0, 0);  
    } else if (yValue < 28000) {  
      motor(m11, m12, map(yValue, 0, 28000, 255, 0), 0);
    } else if (yValue > 36000 && yValue <= 65535) {
      motor(m11, m12, 0, map(yValue, 36000, 65535, 0, 255));
    }

    for (auto &button : buttons) {
      if (*(button.state)) {
        button.action();
      }
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
