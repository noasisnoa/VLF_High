#define MOTOR_DIR 4
#define MOTOR_PWM 5

//////////////////// steering Servo Control///////////////////////////////////////
#include <Servo.h>
#define RC_SERVO_PIN 8         // 나는 8번이야
#define NEURAL_ANGLE 70    /// 70 이었을때 바퀴가 직진이다.    
#define LEFT_STEER_ANGLE -40  //서보의 방향에 따라 -또는 +가 될 수 있다.
#define RIGHT_STEER_ANGLE 40

Servo Steeringservo;
int Steering_Angle = NEURAL_ANGLE;  //초기값은 NEURAL_ANGLE으로
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

void loop()
{
  Serial.print("Motor Control");
  motor_control(1, 80);
  steering_control();
  delay(1000);
 
}
