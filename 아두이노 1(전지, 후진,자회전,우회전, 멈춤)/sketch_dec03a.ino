

int Left_Pin1 = 3;
int Left_Pin2 = 2;
int Right_Pin1 = 7;
int Right_Pin2 = 4;

int Left = 5;
int Right = 6;

void setup() {
  pinMode(Left_Pin1, OUTPUT);
  pinMode(Left_Pin2, OUTPUT);
  pinMode(Right_Pin1, OUTPUT);
  pinMode(Right_Pin2, OUTPUT);
  analogWrite(Left, 255);
  analogWrite(Right, 255);
  Serial.begin(9600);
}


void Front_(int t, int spd){ 
  digitalWrite(Left_Pin1, HIGH);
  digitalWrite(Left_Pin2, LOW);
  digitalWrite(Right_Pin1, HIGH);
  digitalWrite(Right_Pin2, LOW);
  analogWrite(Left, spd);
  analogWrite(Right, spd);
  delay(t);
  }

void Back_( int t, int spd){ //1,2핀에 서로 신호를 다르게하면 후진 
  digitalWrite(Left_Pin1, LOW);
  digitalWrite(Left_Pin2, HIGH);
  digitalWrite(Right_Pin1, LOW);
  digitalWrite(Right_Pin2, HIGH);
  analogWrite(Left, spd);
  analogWrite(Right, spd);
  delay(t);
  }


void Right_( int t, int spd){ //Right 1,2 핀에 다른 신호를 주면 우회전
  digitalWrite(Left_Pin1, HIGH);
  digitalWrite(Left_Pin2, LOW);
  digitalWrite(Right_Pin2, HIGH);
  digitalWrite(Right_Pin1, LOW);
  analogWrite(Left, spd);
  analogWrite(Right, spd);
  delay(t);
  }


void Left_( int t, int spd){ //Left 1,2핀에 다른 신호를 주면 죄회전
  digitalWrite(Left_Pin2, HIGH);
  digitalWrite(Left_Pin1, LOW);
  digitalWrite(Right_Pin1, HIGH);
  digitalWrite(Right_Pin2, LOW);
  analogWrite(Left, spd);
  analogWrite(Right, spd);
  delay(t);
  }

void Stop_(int t){ //Left 1,2핀에 다른 신호를 주면 죄회전
  digitalWrite(Left_Pin1, LOW);
  digitalWrite(Left_Pin2, LOW);
  digitalWrite(Right_Pin1, LOW);
  digitalWrite(Right_Pin2, LOW);
  delay(t);
  }
  
void loop() {
  Front_(2000, 100); //3초동안 150의 속도로 앞으로 전진
  Back_(2000, 100);
  Right_(1000, 95); //3초동안 100의 속도로 우회전 (90도로 꺽는 속도 찾아야 해)
  Left_(1000, 95);
  Stop_(500);
  
}
