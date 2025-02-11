#include <esp_now.h> //ESP-NOW ve WiFi teknolojilerini kullanabilmek için gerekli yazılım araçlarını 
#include <WiFi.h> //programa ekliyor. Yani, cihazlar arası kablosuz iletişim için gerekli kütüphaneleri ekliyoruz.

uint8_t receiverMac[] = {0XF4,0X12,0XFA,0XDF,0X36,0X40};  // veri gönderilecek alıcı cihazın MAC adresi belirleniyor
esp_now_peer_info_t peerInfo;
//alıcı cihaz hakkında bilgi tutacak bir yapıdır 
void OnDataSent(const uint8_t *mac, esp_now_send_status_t status) {
  Serial.print("Gönderme Durumu: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Başarılı" : "Başarısız");
}
//Bu, veri gönderildikten sonra çalışacak bir fonksiyondur. Gönderme işleminin başarılı mı yoksa
// başarısız mı olduğunu anlamamıza yardımcı olur.

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW başlatılamadı!");
    return;
  }
  //ESP-NOW başlatılır. Eğer başlatılamazsa, ekrana "ESP-NOW başlatılamadı!" yazdırılır ve işlem durur.

  esp_now_register_send_cb(OnDataSent); //veri gönderildiğinde OnDataSent fonksiyonunun çalışmasını sağlar.

  // Peer (alıcı) cihazı ekleyelim
  memcpy(peerInfo.peer_addr, receiverMac, 6);
  peerInfo.channel = 0;  //Alıcı cihazla aynı kanalda iletişim kurmayı sağlar. Burada 0 değeri, tüm kanalları kapsar.
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Peer ekleme başarısız!");
    return;
  } else {
    Serial.println("Peer başarıyla eklendi!");
  }
}

void loop() {
  int veri = 123;
  esp_err_t result = esp_now_send(receiverMac, (uint8_t*)&veri, sizeof(veri));

  if (result == ESP_OK) {
    Serial.println("Veri başarıyla gönderildi");
  } else {
    Serial.println("Veri gönderme hatası!");
  }

  delay(2000);
}
