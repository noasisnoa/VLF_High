#include <NewPing.h>

#define  F_Sonar  8
#define  R_Sonar  10
#define  L_Sonar  11
#define MAX_DISTANCE 400
#define NUM_SONAR 3

#define  L_Sonar  11
#define  Left_Pin1  3
#define  Left_Pin2  2
#define  Right_Pin1  7
#define  Right_Pin2  4

#define Left 5
#define Right 6

#define robot_width 200; //차량의 폭
#define mazor_width 500; //결기장 폭 
#define mazor_width_tolerance 40; //오차 위범

int distance[NUM_SONAR] ; //array stores distances for each

NewPing sonar[NUM_SONAR] = {
  NewPing(F_Sonar,F_Sonar, MAX_DISTANCE),
  NewPing(R_Sonar,R_Sonar, MAX_DISTANCE),
  NewPing(L_Sonar,L_Sonar, MAX_DISTANCE),
  };

void updataSonar(){
  
  for(int i=0; i<NUM_SONAR; i++){
    distance[i] = sonar[i].ping_cm(); //update distance
    }
  }

void setup()
{
  pinMode(Left_Pin1, OUTPUT);
  pinMode(Left_Pin2, OUTPUT);
  pinMode(Right_Pin1, OUTPUT);
  pinMode(Right_Pin2, OUTPUT);
  analogWrite(Left, 255);
  analogWrite(Right, 255); 
  Serial.begin(19200);
}

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
///////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() { 
  float F_distance,R_distance,L_distance;
  float measure_widht=L_distance+R_distance+robot_width;

  updataSonar(); //updata the distance array

  F_distance = distance[0];
  R_distance = distance[1];
  L_distance = distance[2]; 

  Serial.print("F_Distance:");
  Serial.print(F_distance);
  Serial.print("mm\n"); 

  Serial.print("R_Distance:");
  Serial.print(R_distance);
  Serial.print("mm\n");

  Serial.print("L_Distance:");
  Serial.print(L_distance);
  Serial.print("mm\n");

 
  if(F_distance <= 20){
    Stop_(1000);

    if(L_distance > R_distance){
      Left_(1000, 83);
      Stop_(100);
    }
    else{
      Right_(1000, 83);
      Stop_(100);
    }
  }
  else{
    Front_(1,150);
  }
} 
