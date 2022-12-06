#include <NewPing.h>
#define  Left_Pin1  3
#define  Left_Pin2  2
#define  Right_Pin1  7
#define  Right_Pin2  4

int Left = 5;
int Right = 6;

void Front_(int t, int L_spd, int R_spd){ 
  digitalWrite(Left_Pin1, HIGH);
  digitalWrite(Left_Pin2, LOW);
  digitalWrite(Right_Pin1, HIGH);
  digitalWrite(Right_Pin2, LOW);
  analogWrite(Left, L_spd);
  analogWrite(Right, R_spd);
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

 
int line_sensor[5]={0,0,0,0,0};

int read_line_sensor(){
  int i;
  int sum=0;
  for(i=0;i<5;i++){
    line_sensor[i]= 1 - digitalRead(A0+i);
    sum += line_sensor[i];
    Serial.print(line_sensor[i]);
    Serial.print("  ");
    }
    Serial.println("");
    //line_sensor[0] line_sensor[1] line_sensor[2] line_sensor[3] line_sensor[4]
    //     -4         -3        -2       -1       0      1      2     3     4   

    int line_index;
   
    if(sum==1)
    {
      if(line_sensor[0]==1) line_index = -4;
      if(line_sensor[1]==1) line_index = -2;
      if(line_sensor[2]==1) line_index =  0;
      if(line_sensor[3]==1) line_index =  2;
      if(line_sensor[4]==1) line_index =  4;
    }
    if(sum==2)
    {
      if( (line_sensor[0]==1) && (line_sensor[1] ==1) ) line_index = -3;
      if( (line_sensor[1]==1) && (line_sensor[2] ==1) ) line_index = -1;
      if( (line_sensor[2]==1) && (line_sensor[3] ==1) ) line_index =  1;
      if( (line_sensor[3]==1) && (line_sensor[4] ==1) ) line_index =  3;
    }
    if(sum==0){
      line_index = -10;
    }
    Serial.print(line_index);
    Serial.println("");
    return line_index;
     //예제 )불이 전부 나올때는 -10이 나오도록 해라
  }

void loop() {
 /*int R_moter_speed,L_moter_speed;
  
  read_line_sensor();
  F_distance=(float)(F_sensor.ping())*10/US_ROUNDTRIP_CM;  //정면 초음파 센서값을 실수로 F_distance에 저장_mm단위
  L_distance=(float)(L_sensor.ping())*10/US_ROUNDTRIP_CM;  //왼쪽 초음파 센서값을 실수로 L_distance에 저장_mm단위
  R_distance=(float)(R_sensor.ping())*10/US_ROUNDTRIP_CM;  //오른쪽 초음파 센서값을 실수로 R_distance에 저장_mm단위
  

  float measure_widht=L_distance+R_distance+robot_width; //오른쪽,왼쪽 초음파 센서와 기체폭을 통해 측정한 현재 측정된 길의 폭

  float turn_90_mm=120;*/
  
  read_line_sensor();
  
  int index;
  index = read_line_sensor();

  switch(index){

    case -4: Front_(1, 200, 100);break;
    case -3:Front_(1, 200, 100 );break;
    case -2:Front_(1, 200, 100);break;
    case -1:Front_(1, 200, 100); break;
    case 0:Front_(1, 100, 100);break;
    case 1:Front_(1, 100, 200);break;
    case 2:Front_(1, 100, 200);break;
    case 3:Front_(1, 100, 200);break;
    case 4:Front_(1, 100,200);break;
    case -10:Stop_(1);break;


    }
}
