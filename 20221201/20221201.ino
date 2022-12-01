// C++ code
#define F_Sonar 8    //Front 핀을 8번에 연결한다.
#define Left_Sonar 11 //Left 핀을 11번에 연결한다.
#define Right_Sonar 10  //Right 핀을 10번에 연결한다.

//차량사이즈
int flag_mazor_1 = 0; //세트 변수 지정


//차량사이즈
float robot_width = 200;  //차량사이즈 변수 지정
float mazor_width = 500;  //폭 사이즈 변수 지정   
float mazor_width_tolerance =40; //오차 허용 사이즈 변수 지정

  
void setup()
{
  //digital pin은 input/Output 
  
  pinMode(F_Sonar, OUTPUT);   //front 출력 
  pinMode(Left_Sonar, OUTPUT);  //Left 출력
  pinMode(Right_Sonar, OUTPUT); //Right 출력
  Serial.begin(115200);     // 115200속도로 통신 BPC(bit por second)
}

float Right_Sonar_sensor()
{
  
  float duration=0.0;     //duration 지속시간 지역 변수 설정
  float distance=0.0;     //distance 거리 지역 변수 설정
  pinMode(Right_Sonar, OUTPUT); //10째에 꽅혀있는 Right를 켜준다. 
  digitalWrite(Right_Sonar, LOW); // Right_Sonar핀을 0V(전류꺼짐)출력
  digitalWrite(Right_Sonar, HIGH);// Right_Sonar핀을 5V(전류켜짐)출력
  delay(10);            //잠깐 켜진상태를 유지한다.
  digitalWrite(Right_Sonar, LOW); //Right_Sonar핀을 0V(전류꺼짐)출력
  pinMode(Right_Sonar, INPUT);    //Right_Sonar 입력
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
  float F_distance1, R_distancel, L_distance1; // F_distance1, R_distancel, L_distance1 지역변수 지정
  float measure_width; //measure_width 지역변수 지정
  
  F_distance1 = F_Sonar_sensor();     //F_Sonar_sensor()의 값을 F_distance1로 넣어준다. 
  R_distancel = Right_Sonar_sensor(); //Right_Sonar_sensor()의 값을 R_distancel로 넣어준다.
  L_distance1 = Left_Sonar_sensor();  //Left_Sonar_sensor()값을 L_distance1 넣어준다.
  
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
  
  measure_width = robot_width+ L_distance1  + R_distancel; //measure_width 값 정해주기 차량의 길이 + 외쪽 + 오른쪽
  
  if((measure_width>=(mazor_width - mazor_width_tolerance))&&(measure_width<=(mazor_width + mazor_width_tolerance)))
  {//만약 (measure_width값이 (거리의 폭 - 허용차 보다 이상) )이고 (measure_width값이 (거리의 폭 더하기 허용치)보다이하이면
    if((F_distance1>mazor_width)&&(F_distance1<mazor_width+ 400))
    {  //F_distance1가 (차량의 길이+왼쪽+오른쪽) 초과이고 F_distance1가 (차량의 길이+왼쪽+오른쪽)+400보다 미만이면
      flag_mazor_1 = 1;
        Serial.println("flag_mazor_1 set");
    }   //set 1통과
    else
    {
      flag_mazor_1 = 0;
  } ////set 1 실패
  }
  
  
  delay(500);
}
