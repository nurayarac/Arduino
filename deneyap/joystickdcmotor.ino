int m11 = D8;
int m12 = D1;
int VRy = A1;
int yValue=0;

void setup()
{
  Serial.begin(115200);
  pinMode(D8, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(VRy, INPUT);
  
}

void loop()
{
  yValue= analogRead(VRy);
  if(yValue <= 2800){
    motor(m11, m12, 0, map(yValue,2800,0,70,255));
    Serial.print("y:");
    Serial.println(yValue);
  }
  else if(yValue >= 3900){
    motor(m11, m12, map(yValue,3900,4095,70,255),0);
    Serial.print("y:");
    Serial.println(yValue);
  }
  else{
    motor(m11, m12, 0, 0);
    Serial.print("y:");
    Serial.println(yValue);
  }
  delay(200);
 /* motor(m11, m12, 0, 150);
  delay(2000); 
  */
}

void motor(int motorpin1, int motorpin2, int i, int j)
{
  if((i == 0 && j == 0) || (i > 0 && j > 0)){
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, LOW);
  }
  else{
    analogWrite(motorpin1, i);
    analogWrite(motorpin2, j);
  }
}
