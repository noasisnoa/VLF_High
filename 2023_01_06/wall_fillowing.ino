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

////////////////////////////////////////////////////////////////////////////////////////////////////////

void read_sonar_sensor(void){

 F_Sonar_Distance = sonar[0].ping_cm() * 10;
 R_Sonar_Distance = sonar[1].ping_cm() * 10;
 L_Sonar_Distance = sonar[2].ping_cm() * 10;

 if(F_Sonar_Distance == 0) F_Sonar_Distance = MAX_DISTANCE *10.0;
 if(R_Sonar_Distance == 0) R_Sonar_Distance = MAX_DISTANCE *10.0;
 if(L_Sonar_Distance == 0) L_Sonar_Distance = MAX_DISTANCE *10.0;
 
 Serial.print("F_Sonar_Distance :");
 Serial.print(F_Sonar_Distance);
 Serial.print(" ");

 Serial.print("R_Sonar_Distance :");
 Serial.print(R_Sonar_Distance);
 Serial.print(" ");

 Serial.print("L_Sonar_Distance :");
 Serial.println(L_Sonar_Distance);

}

void update_sonar_old(void)
{
  F_Sonar_Distance_old = F_Sonar_Distance;  //측정된거된값을 과거에 넣는다
  R_Sonar_Distance_old = R_Sonar_Distance;  //측정된거된값을 과거에 넣는다
  L_Sonar_Distance_old = L_Sonar_Distance;  //측정된거된값을 과거에 넣는다
}

void update_sonar_error(void)
{
  F_Sonar_Error = F_Sonar_Distance - 95;  //현재 값에서 옛날 값을 뺀것
  R_Sonar_Error = R_Sonar_Distance - 95;  //현재 값에서 옛날 값을 뺀것
  L_Sonar_Error = L_Sonar_Distance - 95;  //현재 값에서 옛날 값을 뺀것
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

void setup()
{
  pinMode(Left_Pin1, OUTPUT);
  pinMode(Left_Pin2, OUTPUT);
  pinMode(Right_Pin1, OUTPUT);
  pinMode(Right_Pin2, OUTPUT);
  
  Serial.begin(115200);
}

void loop() 
{
 
  read_sonar_sensor();

   if(L_Sonar_Distance > 200 && R_Sonar_Distance > 200 )
    if(L_Sonar_Distance > R_Sonar_Distance)
    {
      motor_control(1,60,120);
      //좌측으로 붙기
    }
    else if(L_Sonar_Distance < R_Sonar_Distance && L_Sonar_Distance!=0 &&  R_Sonar_Distance !=0)
    {
      motor_control(1,120,60);
      //우측으로 붙기
    }
    else if(L_Sonar_Distance == R_Sonar_Distance)
    {
      motor_control(1,120,120);     
    }

}
