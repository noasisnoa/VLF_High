int IN1Pin =2;
int IN2Pin =3;
int IN3Pin =7;
int IN4Pin =4;

//모터의 힘을 설정해주는 핀
int ENAPin = 5;
int ENBPin = 6;

void setup() {
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(IN3Pin, OUTPUT);
  pinMode(IN4Pin, OUTPUT);
  analogWrite(ENAPin, 150);
  analogWrite(ENBPin, 150);
}

void Front(int t){
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  analogWrite(ENAPin, 150);
  analogWrite(ENBPin, 150);
  delay(t); //5sec
}

void dack(int t){
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
  delay(t);
}

void Left(int t, int c, int p){
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  analogWrite(ENAPin, c);
  analogWrite(ENBPin, p);
  delay(t); //5sec
}

void Right(int t, int c, int p){
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  analogWrite(ENAPin, c);
  analogWrite(ENBPin, p);
  delay(t); //5sec
}

void Stop(){
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, HIGH);
  delay(5000);
}

void loop() {
  Front(5000);
  Left(5000, 90, 30);
  Right(5000, 30, 90);
  dack(3000);
  Stop();
}
