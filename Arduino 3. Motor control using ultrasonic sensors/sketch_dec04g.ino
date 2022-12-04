#define  F_Sonar  8
#define  R_Sonar  10
#define  L_Sonar  11
#define  Left_Pin1  3
#define  Left_Pin2  2
#define  Right_Pin1  7
#define  Right_Pin2  4

int Left = 5;
int Right = 6;

float robot_width = 200; //차량의 폭
float mazor_width = 500; //결기장 폭 
float mazor_width_tolerance = 40; //오차 위범

int flag_mazor_1 = 0; // set 1

//모터 설정
///////////////////////////////////////////////////////////////////////////////////////////////////////

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

//초음파 설정
///////////////////////////////////////////////////////////////////////////////////////////////////////

float F_sonar(void){
  
  float duration=0.0;
  float distance=0.0;
  pinMode(F_Sonar, OUTPUT);
  digitalWrite(F_Sonar,LOW);
  digitalWrite(F_Sonar,HIGH);
  delay(10);
  digitalWrite(F_Sonar,LOW);
  pinMode(F_Sonar, INPUT);
  duration=pulseIn(F_Sonar,HIGH);
  distance=((float)(340*duration)/1000)/2;
  return distance;
}

float R_sonar(void){
  
  float duration=0.0;
  float distance=0.0;
  pinMode(R_Sonar, OUTPUT);
  digitalWrite(R_Sonar,LOW);
  digitalWrite(R_Sonar,HIGH);
  delay(10);
  digitalWrite(R_Sonar,LOW);
  pinMode(R_Sonar, INPUT);
  duration=pulseIn(R_Sonar,HIGH);
  distance=((float)(340*duration)/1000)/2;
  return distance;
}

float L_sonar(void){
  
  float duration=0.0;
  float distance=0.0;
  pinMode(L_Sonar, OUTPUT);
  digitalWrite(L_Sonar,LOW);
  digitalWrite(L_Sonar,HIGH);
  delay(10);
  digitalWrite(L_Sonar,LOW);
  pinMode(L_Sonar, INPUT);
  duration=pulseIn(L_Sonar,HIGH);
  distance=((float)(340*duration)/1000)/2;
  return distance;
}

//아두이노 세팅 
///////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(Left_Pin1, OUTPUT);
  pinMode(Left_Pin2, OUTPUT);
  pinMode(Right_Pin1, OUTPUT);
  pinMode(Right_Pin2, OUTPUT);
  analogWrite(Left, 255);
  analogWrite(Right, 255);

  pinMode(F_Sonar, OUTPUT);
  pinMode(L_Sonar, OUTPUT);
  pinMode(R_Sonar, OUTPUT);
  Serial.begin(115200);//스크린프린트르 115200의 속도로 보여준다. 
}

void loop() {
  float F_distance,R_distance,L_distance;
  float measure_widht=L_distance+R_distance+robot_width;

  F_distance = F_sonar();
  R_distance = R_sonar();
  L_distance = L_sonar(); 

  Serial.print("F_Distance:");
  Serial.print(F_distance);
  Serial.print("mm\n");
  
  Serial.print("R_Distance:");
  Serial.print(R_distance);
  Serial.print("mm\n");
  
  Serial.print("L_Distance:");
  Serial.print(L_distance);
  Serial.print("mm\n");
  
  if(F_distance <= 200){
    Stop_(1000);

    if(L_distance > R_distance){
      Left_(1000, 110);
      Stop_(100);
    }
    else{
      Right_(1000, 110);
      Stop_(100);
    }
  }
  else{
    Front_(1,150);
  }

}
