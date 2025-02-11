#include <WiFi.h>
//bir WiFi cihazının MAC adresini (her cihazın kendine ait bir kimliği) ekrana yazdırır.
void setup() {
  Serial.begin(115200); //bilgisayara veya başka bir cihaza mesaj gönderip alabilmek için seri iletişim başlatır. Burada hız olarak 115200 seçilmiş.
  WiFi.mode(WIFI_STA); //WiFi ağına bağlanmaya çalışacak
  Serial.println("Slave Cihazın MAC Adresi:");
  Serial.println(WiFi.macAddress()); //WiFi cihazının MAC adresini (kimlik numarasını) ekranda gösterecek.
}

void loop() {}
