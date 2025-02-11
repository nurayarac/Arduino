#include <esp_now.h>
#include <WiFi.h>
//mac-veriyi gönderen cihazın MAC adresi. Hangi cihazdan veri geldiğini buradan anlayabiliriz.
//incomingData: Bu, gelen verinin kendisi. Gönderilen veri burada yer alır.
//len-gelen verinin uzunluğunu (yani kaç byte olduğunu) gösterir
void OnDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
  int gelenVeri;
  memcpy(&gelenVeri, incomingData, sizeof(gelenVeri)); //Bu satır, gelen veriyi (incomingData) gelenVeri adlı değişkene kopyalar.
  Serial.print("Gelen Veri: ");
  Serial.println(gelenVeri);
}

void setup(){
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); //Cihazı WiFi istemci (yani bağlanacak cihaz) olarak ayarlar.
  Serial.println("Slave Cihazın MAC Adresi:");
  Serial.println(WiFi.macAddress());

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı!");
    return;
  }
//Bu satır, ESP-NOW'un başlatılmaya çalışıldığını kontrol eder. Eğer başarılı olursa, bir şey yapılmaz, 
//ama başarısız olursa, ekrana "ESP-NOW başlatılamadı!" mesajı yazdırılır ve işlem sonlanır.

  esp_now_register_recv_cb(OnDataRecv); //veri geldiğinde çalışacak olan OnDataRecv fonksiyonunu kaydeder
}

void loop() {
}
