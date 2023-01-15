#include <NewPing.h>
#define  Left_Pin1  3
#define  Left_Pin2  2
#define  Right_Pin1  7
#define  Right_Pin2  4

#define Left 5
#define Right 6

#define MAX_DISTANCE 250
float R_Sonar_Distance = 0.0;
float R_Sonar_Distance_old = 0.0;
float R_Sonar_Error = 0.0;
float L_Sonar_Distance = 0.0;
float L_Sonar_Distance_old = 0.0;
float L_Sonar_Error = 0.0;
float F_Sonar_Distance = 0.0;
float F_Sonar_Distance_old = 0.0;
float F_Sonar_Error = 0.0;

//NewPing을 이용하여 Sonar값 구하기, 저장하기///////////////////////////////////////////////////////////////

NewPing sonar[3] =
{
  NewPing (8, 8, MAX_DISTANCE),
  NewPing (10, 10, MAX_DISTANCE),
  NewPing (11, 11, MAX_DISTANCE),
  
};

void read_sonar_sensor(){

 F_Sonar_Distance = sonar[0].ping_cm() * 10;
 R_Sonar_Distance = sonar[1].ping_cm() * 10;
 L_Sonar_Distance = sonar[2].ping_cm() * 10;

 if(F_Sonar_Distance == 0) F_Sonar_Distance = MAX_DISTANCE *10.0;
 if(R_Sonar_Distance == 0) R_Sonar_Distance = MAX_DISTANCE *10.0;
 if(L_Sonar_Distance == 0) L_Sonar_Distance = MAX_DISTANCE *10.0;

 /*
 Serial.print("F_Sonar_Distance :");
 Serial.print(F_Sonar_Distance);
 Serial.print(" ");

 Serial.print("R_Sonar_Distance :");
 Serial.print(R_Sonar_Distance);
 Serial.print(" ");

 Serial.print("L_Sonar_Distance :");
 Serial.print(L_Sonar_Distance);
 Serial.print("\n");
 */

}

void update_sonar_old(void){ //초음파 센서의 옛날값 저장
    R_Sonar_Distance_old = R_Sonar_Distance;
    L_Sonar_Distance_old = L_Sonar_Distance;
    F_Sonar_Distance_old = F_Sonar_Distance;
  }

void update_sonar_error(void){ //초음파 센서의 옛날값과 현재값의 차이 저장
    R_Sonar_Error = R_Sonar_Distance - R_Sonar_Distance_old;
    L_Sonar_Error = L_Sonar_Distance - L_Sonar_Distance_old;
    F_Sonar_Error = F_Sonar_Distance - F_Sonar_Distance_old;
  }

//모터 설정 1:전진, 2:후진, 3:우회전, 4:자회전, 5:정지///////////////////////////////////////////////////////
void motor_control(int direction, int L_spd, int R_spd){
  switch(direction){
    case 1: digitalWrite(Left_Pin1, HIGH);  
            digitalWrite(Left_Pin2, LOW);
            digitalWrite(Right_Pin1, HIGH);
            digitalWrite(Right_Pin2, LOW);
            analogWrite(Left, L_spd);
            analogWrite(Right, R_spd);
            break;
    
    case 2: digitalWrite(Left_Pin1, LOW);  
            digitalWrite(Left_Pin2, HIGH);
            digitalWrite(Right_Pin1, LOW);
            digitalWrite(Right_Pin2, HIGH);
            analogWrite(Left, L_spd);
            analogWrite(Right, R_spd);
            break;

    case 3: digitalWrite(Left_Pin1, HIGH); 
            digitalWrite(Left_Pin2, LOW);
            digitalWrite(Right_Pin2, HIGH);
            digitalWrite(Right_Pin1, LOW);
            analogWrite(Left, L_spd);
            analogWrite(Right, R_spd);
            break;
    
    case 4: digitalWrite(Left_Pin2, HIGH); 
            digitalWrite(Left_Pin1, LOW);
            digitalWrite(Right_Pin1, HIGH);
            digitalWrite(Right_Pin2, LOW);
            analogWrite(Left, L_spd);
            analogWrite(Right, R_spd);
            break;

    case 5: digitalWrite(Left_Pin1, LOW);
            digitalWrite(Left_Pin2, LOW);
            digitalWrite(Right_Pin1, LOW);
            digitalWrite(Right_Pin2, LOW);
            analogWrite(Left, L_spd);
            analogWrite(Right, R_spd);
            break;        
  }
}

//Line 읽기 설정////////////////////////////////////////////////////////////////////////////////////////

int line_sensor[5]={0,0,0,0,0};
 
int read_line_sensor(){
  
  int line_index;
  int i;
  int sum = 0;
  
  for(i=0;i<5;i++){
    line_sensor[i]=(digitalRead(A0+i));
    sum += line_sensor[i];
    //Serial.print(line_sensor[i]);
    //Serial.print("  ");
    }
    
  //Serial.println("");
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
    
  //Serial.print(line_index);
  //Serial.println("");
  
  return line_index;

}
int index;

int line_following(){

  index = read_line_sensor();
  read_sonar_sensor();
  
  switch(index){
    case -4 :  motor_control(1,9,255); break;
    case -3 :  motor_control(1,10,205); break;
    case -2 :  motor_control(1,11,155); break;
    case -1 :  motor_control(1,11,105); break;
    case 0 :  motor_control(1,100,100); break;
    case 1 :  motor_control(1,105,11); break;
    case 2 :  motor_control(1,155,11); break;
    case 3 :  motor_control(1,205,10); break;
    case 4 :  motor_control(1,255,9); break;
    case -10 :  motor_control(5,0,0); break;
    }
}

//100mm앞에서 stop////////////////////////////////////////////////////////////////////////////////////////

void stop_at_hundredmm(){
 
  if(F_Sonar_Distance <= 300){
    
    motor_control(5,0,0);
  
  }else{
    line_following();
   }  
}

////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  pinMode(Left_Pin1, OUTPUT);
  pinMode(Left_Pin2, OUTPUT);
  pinMode(Right_Pin1, OUTPUT);
  pinMode(Right_Pin2, OUTPUT);
  Serial.begin(115200);
}

///turn_right_90//////////////////////////////////////////////////////////////////////////////////////
int a=0;
int mission_flag = 0;
void turn_right_90(void){
  
  int min_Distance = 0;
  
  if(F_Sonar_Distance <= 650){ //700 + 650 +640
    
    min_Distance = F_Sonar_Distance;
    motor_control(3,100,100);
    delay(400);  //0.5초
    
    while(1){
      
      read_sonar_sensor();
      motor_control(3,100,100);
      
      if(L_Sonar_Distance <= min_Distance-50)  //+5  30  40// -60
      {  motor_control(3,100,100);
         delay(80+a);
        mission_flag++;
        break;
      }
    }
  }
}
///wall_fillowing1////////////////////////////////////////////////////////////////////////////////////

void wall_fillowing(){
    motor_control(1,100+(L_Sonar_Error*3)*1.5,(80-(L_Sonar_Error*3))*1.5);
    delay(5);
    update_sonar_old();
    }
 
///mode_obstacle////////////////////////////////////////////////////////////////////////////////////

int mode_obstacle(){
if(F_Sonar_Distance <= 400){
      motor_control(5,0,0);
      delay(100);
      while(1){
        read_sonar_sensor();
        motor_control(3,100,100);////////////////////////////////
        if(L_Sonar_Distance<=400){
          break;
          }
        }
      motor_control(1,100,100); ////수정
      delay(300);  //1000
      while(1){
        index = read_line_sensor();
        motor_control(1,30,150); ////수정 ////////////////////////////////////////////////////////////////
        if(index !=0){
           while(1){
             index = read_line_sensor();
             motor_control(1,100,100);
              if(index>0){
                motor_control(3,100,100);////////////////////////////////
                delay(300);
                break;
                }
              }
            break;
            }
          }
        }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////  

void loop() {
  read_sonar_sensor();
  update_sonar_error();
  
   if(mission_flag == 0)
  {
    read_sonar_sensor();
    read_line_sensor();
  
    line_following();

    mode_obstacle();
    //stop_at_hundredmm();
    read_sonar_sensor();

    ///////////////////////////motor_control(1,120,120);

     if(L_Sonar_Distance+R_Sonar_Distance<=1200)
      {
        mission_flag = 1;
      }

  }
  
  
  if(mission_flag == 1)
  {

    read_sonar_sensor();
    update_sonar_error();
    motor_control(1,120,120);
    index = read_line_sensor();

    //wall_fillowing();
    /*if(index != 0){
      mission_flag = 2;
      }*/

   if(R_Sonar_Distance >= 1500)
   {
       wall_fillowing();
       turn_right_90();
       
      //한쪽 벽만 따라가는 것
   }
   else
   {
      if(L_Sonar_Distance > R_Sonar_Distance)
      {
        motor_control(1,80,120); //좌측으로 붙기    
      }
      else if(L_Sonar_Distance < R_Sonar_Distance && L_Sonar_Distance!=0 &&  R_Sonar_Distance !=0)
      {
        motor_control(1,120,80); //우측으로 붙기
      }
      else if(L_Sonar_Distance == R_Sonar_Distance)
      {
        //line_following();
        motor_control(1,120,120);

      }

    }
    
  }
  if(mission_flag == 2)
  {
    a = 10;
    read_sonar_sensor();
    update_sonar_error();
    motor_control(1,120,120);
    index = read_line_sensor();

    //wall_fillowing();
    /*if(index != 0){
      mission_flag = 2;
      }*/

   if(R_Sonar_Distance >= 1500)
   {
       wall_fillowing();
       turn_right_90();
       
      //한쪽 벽만 따라가는 것
   }
   else
   {
      if(L_Sonar_Distance > R_Sonar_Distance)
      {
        motor_control(1,80,120); //좌측으로 붙기    
      }
      else if(L_Sonar_Distance < R_Sonar_Distance && L_Sonar_Distance!=0 &&  R_Sonar_Distance !=0)
      {
        motor_control(1,120,80); //우측으로 붙기
      }
      else if(L_Sonar_Distance == R_Sonar_Distance)
      {
        //line_following();
        motor_control(1,120,120);

      }

    }
    
  }
  
  if(mission_flag == 3)
  {

    read_sonar_sensor();
    update_sonar_error();
    motor_control(1,120,120);
    index = read_line_sensor();

    //wall_fillowing();
    if(index != 0){
      mission_flag = 4;
      }

   if(R_Sonar_Distance >= 1500)
   {
       wall_fillowing();
       //turn_right_90();
       
      //한쪽 벽만 따라가는 것
   }
   else
   {
      if(L_Sonar_Distance > R_Sonar_Distance)
      {
        motor_control(1,80,120); //좌측으로 붙기    
      }
      else if(L_Sonar_Distance < R_Sonar_Distance && L_Sonar_Distance!=0 &&  R_Sonar_Distance !=0)
      {
        motor_control(1,120,80); //우측으로 붙기
      }
      else if(L_Sonar_Distance == R_Sonar_Distance)
      {
        //line_following();
        motor_control(1,120,120);

      }

    }
    
  }

  if(mission_flag == 4){
    
    line_following();
    
    }

}
