// Motor pin tanımlamaları
#define Z_STEP_PIN 46
#define Z_DIR_PIN 48
#define Z_ENABLE_PIN A8

// Motor hareket parametreleri
#define STEPS_PER_REVOLUTION 200 // Bir turda adım sayısı (DRV8825'te genellikle 200)
#define STEP_DELAY 100          // Adım başına bekleme süresi (mikrosaniye cinsinden) - Daha hızlı hareket için bu değeri düşürün
#define STEPS_PER_CYCLE 1000    // Döngü başına adım sayısı - Daha az adım atmak için bu değeri azaltın
#define NUM_SETS 3              // Toplam set sayısı
#define INITIAL_DELAY 2000     // Başlangıçta bekleme süresi (2 saniye)

void setup() {
  // Pin modlarını ayarla
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(Z_ENABLE_PIN, OUTPUT);

  // Motoru etkinleştir
  digitalWrite(Z_ENABLE_PIN, LOW); // DRV8825 sürücüsünde LOW etkinleştirme anlamına gelir

  // Başlangıçta motoru başlatmadan önce bekleme süresi ekle
  delay(INITIAL_DELAY);

  // Toplam 3 set işlemi
  for (int set = 0; set < NUM_SETS; set++) {
    executeSet();
    delay(1000); // Setler arasında bekleme süresi
  }

  // Döngüyü sonlandır
  while (true) {
    // Sonsuz döngü motoru durdurur
  }
}

void loop() {
  // loop() fonksiyonu boş bırakılmıştır, çünkü setup() sadece bir kez çalışır
}

void executeSet() {
  // Motoru aşağı hareket ettir
  digitalWrite(Z_DIR_PIN, LOW); // Motorun aşağı hareket etmesi için LOW
  moveMotor();

  // 1 saniye bekle
  delay(1000);

  // Motoru yukarı hareket ettir
  digitalWrite(Z_DIR_PIN, HIGH); // Motorun yukarı hareket etmesi için HIGH
  moveMotor();
}

void moveMotor() {
  for (int i = 0; i < STEPS_PER_CYCLE; i++) {
    digitalWrite(Z_STEP_PIN, HIGH);
    delayMicroseconds(STEP_DELAY);
    digitalWrite(Z_STEP_PIN, LOW);
    delayMicroseconds(STEP_DELAY);
  }
}
