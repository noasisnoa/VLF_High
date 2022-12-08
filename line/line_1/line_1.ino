
#include <NewPing.h>
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
  Serial.begin(9600);
}


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
  int line_index;
  int i;
  int sum=0;
  for(i=0;i<5;i++){
    line_sensor[i]=(digitalRead(A0+i));
    sum += line_sensor[i];
    Serial.print(line_sensor[i]);
    Serial.print("  ");
    }
  Serial.println("");
  if(sum==5) line_index = -10;
  if(sum==1){
    if(line_sensor[0]==1) line_index = -4;
    if(line_sensor[1]==1) line_index = -2;
    if(line_sensor[2]==1) line_index = 0;
    if(line_sensor[3]==1) line_index = 2;
    if(line_sensor[4]==1) line_index = 4;
    }
  if(sum==2){
    if(line_sensor[0]==1 && line_sensor[1]==1) line_index = -3;
    if(line_sensor[1]==1 && line_sensor[2]==1) line_index = -1;
    if(line_sensor[2]==1 && line_sensor[3]==1) line_index = 1;
    if(line_sensor[3]==1 && line_sensor[4]==1) line_index = 3;
    }
  if(sum==0){
    line_index = 0;
    }
    
  Serial.print(line_index);
  Serial.println("");
  return line_index;
  }

  
void loop() {
  int index;
  index=read_line_sensor();
  
  switch(index){
    case -4 : Front_(1,9,250); break;
    case -3 : Front_(1,10,200); break;
    case -2 : Front_(1,11,150); break;
    case -1 : Front_(1,11,100); break;
    case 0 : Front_(1,100,100); break;
    case 1 : Front_(1,100,11); break;
    case 2 : Front_(1,150,11); break;
    case 3 : Front_(1,200,10); break;
    case 4 : Front_(1,250,9); break;
    case -10 : Stop_(1); break;
  }}
