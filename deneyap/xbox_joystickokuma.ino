#include <XboxSeriesXControllerESP32_asukiaaa.hpp>
XboxSeriesXControllerESP32_asukiaaa::Core xboxController("68:6c:e6:56:a7:b2");
void setup() {
  Serial.begin(115200);
  Serial.println("Setup tamamlandı, loop'a geçiliyor...");
  
  xboxController.begin();
}

void loop() {
  xboxController.onLoop();

  if (xboxController.isConnected()) {
    int joyLX = xboxController.xboxNotif.joyLHori;  
    int joyLY = xboxController.xboxNotif.joyLVert;  

    Serial.print("JoyX: ");
    Serial.print(joyLX);
    Serial.print("\tJoyY: ");
    Serial.println(joyLY);

  } else {
    Serial.println("Xbox controller bağlı değil");
  }

  delay(1000);  
}
