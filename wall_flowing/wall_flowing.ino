//wall_flowing

#include <NewPing.h> 
#define MAX_DISTANCE 150

#define  Left_Pin1  3
#define  Left_Pin2  2
#define  Right_Pin1  7
#define  Right_Pin2  4
#define Left 5
#define Right 6

float R_Sonar_Distance = 0.0;
float R_Sonar_Distance_old = 0.0;
float R_Sonar_Error = 0.0;
float L_Sonar_Distance = 0.0;
float L_Sonar_Distance_old = 0.0;
float L_Sonar_Error = 0.0;
float F_Sonar_Distance = 0.0;
float F_Sonar_Distance_old = 0.0;
float F_Sonar_Error = 0.0;

float motor_diff=0;

NewPing sonar[3] =
{
  NewPing (8, 8, MAX_DISTANCE),
  NewPing (10, 10, MAX_DISTANCE),
  NewPing (11, 11, MAX_DISTANCE),
  
};

void read_sonar_sensor(void)  //초음파 센서 값을 읽는 함수
{
    
 R_Sonar_Distance = sonar[1].ping_cm() * 10;
 L_Sonar_Distance = sonar[2].ping_cm() * 10;
 F_Sonar_Distance = sonar[0].ping_cm() * 10;
 
 if(R_Sonar_Distance == 0) R_Sonar_Distance = MAX_DISTANCE *10.0;
 if(L_Sonar_Distance == 0) L_Sonar_Distance = MAX_DISTANCE *10.0;
 if(F_Sonar_Distance == 0) F_Sonar_Distance = MAX_DISTANCE *10.0;
}

void update_sonar_old(void)
{
  R_Sonar_Distance_old = R_Sonar_Distance;  //측정된거된값을 과거에 넣는다
  L_Sonar_Distance_old = L_Sonar_Distance;  //측정된거된값을 과거에 넣는다
  F_Sonar_Distance_old = F_Sonar_Distance;  //측정된거된값을 과거에 넣는다
}

void update_sonar_error(void)
{
  R_Sonar_Error = R_Sonar_Distance - R_Sonar_Distance_old;  //현재 값에서 옛날 값을 뺀것
  L_Sonar_Error = L_Sonar_Distance - L_Sonar_Distance_old;  //현재 값에서 옛날 값을 뺀것
  F_Sonar_Error = F_Sonar_Distance - F_Sonar_Distance_old;  //현재 값에서 옛날 값을 뺀것
}

void Moving(int t, int L_spd, int R_spd){ 
  digitalWrite(Left_Pin1, HIGH);
  digitalWrite(Left_Pin2, LOW);
  digitalWrite(Right_Pin1, HIGH);
  digitalWrite(Right_Pin2, LOW);
  analogWrite(Left, L_spd);
  analogWrite(Right, R_spd);
  delay(t);
  }
  
void setup() {
  
  pinMode(Left_Pin1, OUTPUT);
  pinMode(Left_Pin2, OUTPUT);
  pinMode(Right_Pin1, OUTPUT);
  pinMode(Right_Pin2, OUTPUT);
  Serial.begin(19200);
}


void loop() 
{
  
  float p_gain =1.3;
  int nm_sp_L = 100;
  int nm_sp_R = 100;
  
  read_sonar_sensor();
  update_sonar_error();
  update_sonar_old();
  motor_diff = R_Sonar_Error * p_gain; 
 
  Serial.print(R_Sonar_Distance); 
  Serial.print("\t");
  Serial.print(R_Sonar_Distance_old); 
  Serial.print("\t");
  Serial.println(R_Sonar_Error);

  if(R_Sonar_Error > 0){
    nm_sp_L++;
    nm_sp_R--;
    }
  if(R_Sonar_Error < 0){
    nm_sp_L--;
    nm_sp_R++;
    }
  
  
  Moving(1,nm_sp_L+(R_Sonar_Error*4),nm_sp_R-(R_Sonar_Error*3));
  
  delay(100);
  
}
