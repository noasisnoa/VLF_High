#define MOTOR_DIR 4
#define MOTOR_PWM 5
#define DEBUG 1 //1하면 출력을 할 것이다.

//////////////////// steering Servo Control///////////////////////////////////////
#include <Servo.h>
#define RC_SERVO_PIN 8         // 나는 8번이야
#define NEURAL_ANGLE 75    /// 70 이었을때 바퀴가 직진이다.    
#define LEFT_STEER_ANGLE -40  //서보의 방향에 따라 -또는 +가 될 수 있다.
#define RIGHT_STEER_ANGLE 40

Servo Steeringservo;
int Steering_Angle = NEURAL_ANGLE;  //초기값은 NEURAL_ANGLE으로

void motor_control(int direction, int speed)
{
  Serial.println("Motor Conteol");
  digitalWrite(MOTOR_DIR, direction); //ordigitalWrite(MOTOR_DIR, 0);
  analogWrite(MOTOR_PWM, speed);  
}

void steering_control()

{
  if(Steering_Angle <= LEFT_STEER_ANGLE + NEURAL_ANGLE)  Steering_Angle  = LEFT_STEER_ANGLE + NEURAL_ANGLE;
  if(Steering_Angle >= RIGHT_STEER_ANGLE + NEURAL_ANGLE)  Steering_Angle = RIGHT_STEER_ANGLE + NEURAL_ANGLE;
  Steeringservo.write(Steering_Angle);  
}

////////////Sensor///////////////////////////////////////////////////////////////////////////
#include <NewPing.h>
#define SONAR_NUM 3
#define MAX_DISTANCE 150 //cm
float UlteasonicSeneorData[SONAR_NUM];

NewPing sonar[SONAR_NUM] ={
  NewPing(48, 50, MAX_DISTANCE), //앞
  NewPing(42, 44, MAX_DISTANCE),// 오른쪽
  NewPing(9, 10, MAX_DISTANCE) // 왼쪽
  };

void serial_com(void)
{
  if(DEBUG != 1) 
  {
      return;
  }
  
  Serial.print("F_Sonar : ");
  Serial.print(UlteasonicSeneorData[0]);   //1인 경우에는 다음과 같이 sonar 값을 출략한다. 
  Serial.print(" ");
    
  Serial.print("R_Sonar : ");
  Serial.print(UlteasonicSeneorData[1]);
  Serial.print(" ");

  Serial.print("L_Sonar : ");
  Serial.println(UlteasonicSeneorData[2]);   //1인 경우에는 다음과 같이 sonar 값을 출략한다. 
  Serial.print(" ");
  
}

void read_ultrasonic_sensor(void)
{
   UlteasonicSeneorData[0] = sonar[0].ping_cm();
   UlteasonicSeneorData[1] = sonar[1].ping_cm();
   UlteasonicSeneorData[2] = sonar[2].ping_cm();

   if( UlteasonicSeneorData[0] == 0.0 )
   { 
      UlteasonicSeneorData[0] = (float)MAX_DISTANCE;
      UlteasonicSeneorData[1] = (float)MAX_DISTANCE;
      UlteasonicSeneorData[2] = (float)MAX_DISTANCE;
   }
  
}
//////////////////// /////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
void setup() 
{
    Serial.begin(115200);
    pinMode(MOTOR_DIR, OUTPUT);
    pinMode(MOTOR_PWM, OUTPUT);

    Steeringservo.attach(RC_SERVO_PIN);  // 8번 핀을 서보로 사용하겠다.
    Steeringservo.write(NEURAL_ANGLE);  //초기에느 90도 중립을, 0~90도로 움직인다.
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


void loop()
{
  read_ultrasonic_sensor();
  serial_com();
  motor_control(1, 80);
  steering_control();
 
}
