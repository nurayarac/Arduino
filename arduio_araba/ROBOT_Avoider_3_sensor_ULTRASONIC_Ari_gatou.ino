const int Echo1 = A4; //sol_sensor echo
const int Trig1 = A5; //sol_sensor trig
const int Echo2 = A2; //merkezi_sensor echo
const int Trig2 = A3; //merkezi_sensor trig
const int Echo3 = A0; //sağ_sensor echo
const int Trig3 = A1; //sağ_sensor trig

const int in1 = 5; // motor pinleri
const int in2 = 4;
const int in3 = 3;
const int in4 = 2;
const int ENA = 10; // PWM hız kontrolü
const int ENB = 9;

// Sabitler
const int threshold_distance = 30; // Engelden kaçınma mesafesi (cm)
const int motorSpeed = 50; // Motor hızı

void setup() {
  // Ultrasonik sensör pinlerini giriş ve çıkış olarak ayarla
  pinMode(Echo1, INPUT);
  pinMode(Trig1, OUTPUT);
  pinMode(Echo2, INPUT);
  pinMode(Trig2, OUTPUT);
  pinMode(Echo3, INPUT);
  pinMode(Trig3, OUTPUT);

  // Motor pinlerini çıkış olarak ayarla
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Seri bağlantıyı başlat
  Serial.begin(9600);
}

void loop() {
  // Engelden kaçınma algoritması
  int left_distance = getDistance(Trig1, Echo1);
  int central_distance = getDistance(Trig2, Echo2);
  int right_distance = getDistance(Trig3, Echo3);

  Serial.print("Left Distance: ");
  Serial.println(left_distance);
  Serial.print("Central Distance: ");
  Serial.println(central_distance);
  Serial.println(right_distance);

  if (central_distance > threshold_distance) {
    // Merkezde engel yoksa ileri git
    moveForward();
  } else {
    // Engeli algıladıysa, sağa ya da sola dön
    if (left_distance > right_distance) {
      // Sol tarafta daha fazla alan varsa sağa dön
      turnRight();
    } else {
      // Sağ tarafta daha fazla alan varsa sola dön
      turnLeft();
    }
  }
}

// Ultrasonik sensörlerden mesafe ölçümü fonksiyonu
int getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH) / 58.2; // Mikro saniye cinsinden süreyi cm cinsine çevirir
}

// İleri gitme fonksiyonu
void moveForward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

// Sağa dönme fonksiyonu
void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}

// Sola dönme fonksiyonu
void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
}