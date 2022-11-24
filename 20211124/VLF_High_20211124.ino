// C++ code
#define F_Sonar 8
#define Left_Sonar 11
#define Right_Sonar 10

//차량사이즈
int flag_mazor_1 = 0;


//차량사이즈
float robot_width = 200;
float mazor_width = 500;
float mazor_width_tolerance =40;

  
void setup()
{
  //digital pin은 input/Output 
  
  pinMode(F_Sonar, OUTPUT);
  pinMode(Left_Sonar, OUTPUT);
  pinMode(Right_Sonar, OUTPUT);
  Serial.begin(115200);// 115200속도로 통신 BPC(bit por second)
}

float Right_Sonar_sensor()
{
  
  float duration=0.0;
  float distance=0.0;
  pinMode(Right_Sonar, OUTPUT);
  digitalWrite(Right_Sonar, LOW);
  digitalWrite(Right_Sonar, HIGH);
  delay(10);
  digitalWrite(Right_Sonar, LOW);
  pinMode(Right_Sonar, INPUT);
  duration = pulseIn(Right_Sonar, HIGH);
  distance=(34.0*duration)/2.0/1000.0; //10000 을 1000으로 바꿔줘야지  mm단위가 나온다. 
  return distance;        
  
}


float Left_Sonar_sensor()
{
  
  float duration=0.0;
  float distance=0.0;
  pinMode(Left_Sonar,OUTPUT);
  digitalWrite(Left_Sonar, LOW);
  digitalWrite(Left_Sonar,HIGH);
  delay(10);
  digitalWrite(Left_Sonar, LOW);
  pinMode(Left_Sonar, INPUT);
  duration = pulseIn(Left_Sonar, HIGH);
  distance=(34.0*duration)/2.0/1000.0;
  return distance;        
  
}
  
  float F_Sonar_sensor()
{
  
  float duration=0.0;
  float distance=0.0;
  pinMode(F_Sonar,OUTPUT);
  digitalWrite(F_Sonar, LOW);
  digitalWrite(F_Sonar,HIGH);
  delay(10);
  digitalWrite(F_Sonar, LOW);
  pinMode(F_Sonar, INPUT);
  duration = pulseIn(F_Sonar, HIGH);
  distance=(34.0*duration)/2.0/1000.0;
  return distance;        
  
}



void loop()  //반복 실행하는 함수, 모든 코들가 들어감, 메인 함수의 역활
{
  float F_distance1, R_distancel, L_distance1;
  float measure_width;
  
  F_distance1 = F_Sonar_sensor();
  R_distancel = Right_Sonar_sensor();
  L_distance1 = Left_Sonar_sensor();
  
  Serial.print("F_Distance:");
  Serial.print(F_distance1);
  Serial.print("mm\n");
  
  Serial.print("R_Distance:");
  Serial.print(R_distancel);
  Serial.print("mm\n");
  
  Serial.print("L_Distance:");
  Serial.print(L_distance1);
  Serial.print("mm\n");
  Serial.print("\n");
  
  measure_width = L_distance1 + robot_width + R_distancel;
  
  if((measure_width>=(mazor_width - mazor_width_tolerance))&&(measure_width<=(mazor_width + mazor_width_tolerance)))
	{
    if((F_distance1>mazor_width)&&(F_distance1<mazor_width+ 400))
   	{
    	flag_mazor_1 = 1;
        Serial.println("flag_mazor_1 set");
  	}
  	else
  	{
    	flag_mazor_1 = 0;
	}
  }
  
  
  delay(500);
}
