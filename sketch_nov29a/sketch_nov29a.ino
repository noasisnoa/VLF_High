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


void loop() {
  //Go IN1Pin, In2Pin 신호를 다르게하면서 전진
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, LOW);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, LOW);
  delay(5000); //5sec

  //Back IN1Pin, In2Pin 신호를 다르게하면서 후진
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, LOW);
  digitalWrite(IN4Pin, HIGH);
  delay(5000);

  //Back(Stop) IN1Pin, In2Pin 동시에 HIGH를 주거나 LOW를 주면 멈춘다.
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, HIGH);
  digitalWrite(IN3Pin, HIGH);
  digitalWrite(IN4Pin, HIGH);
  delay(5000);
}
