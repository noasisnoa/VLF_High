int IN1Pin =2;
int IN2Pin =3;
int IN3Pin =4;
int IN4Pin =7;

//모터의 힘을 설정해주는 핀
int ENAPin = 5;
int ENBPin = 6;

void setup() {
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT);
  pinMode(IN3Pin, OUTPUT);
  pinMode(IN4Pin, OUTPUT);
  analogWrite(ENAPin, 225);
  analogWrite(ENBPin, 225);
}

void Front(int t){
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  delay(t); //5sec
}

void dack(int t){
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  delay(t); //5sec
}

void Left(int t){
   digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  delay(t); //5sec
}

void Right(int t){
   digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
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
  Front(200);
  dack(200);
  Left(200);
  Right(200);
}
