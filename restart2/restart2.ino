//초음파 설정
#define  Front_Sonar  8  
#define  Right_Sonar  10 
#define  Left_Sonar  11

////my 3,2,7, 4
//// 3,2,7,4


//모터 설정
#define Left_Pin_1 2 
#define Left_Pin_2  3  
#define Right_Pin_1  7 
#define Right_Pin_2  4 

#define Left_Pin 5 //왼쪽모터 속도 제어 핀
#define Rright_Pin 6 //오른쪽모터 속도 제어 핀

//설정
float robot_width = 200; 
float mazor_width = 500; 
float mazor_width_tolerance = 40;


void setup() {
  pinMode(Front_Sonar, OUTPUT);
  pinMode(Left_Sonar, OUTPUT); 
  pinMode(Right_Sonar, OUTPUT); 
  
  pinMode(Left_Pin_1,OUTPUT);
  pinMode(Left_Pin_2,OUTPUT); 
  pinMode(Right_Pin_1,OUTPUT);
  pinMode(Right_Pin_2,OUTPUT);
  
  analogWrite(Left_Pin,80);  
  analogWrite(Rright_Pin,80); 
  Serial.begin(115200); 
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
  distance=((float)(340*duration)/1000)/2; //10000 을 1000으로 바꿔줘야지  mm단위가 나온다. 
  return distance;        
}

float Left_Sonar_sensor()
{
  
  float duration=0.0;     //duration 지속시간 지역 변수 설정
  float distance=0.0;     //distance 거리 지역 변수 설정
  pinMode(Left_Sonar, OUTPUT); //10째에 꽅혀있는 Right를 켜준다. 
  digitalWrite(Left_Sonar, LOW); // Right_Sonar핀을 0V(전류꺼짐)출력
  digitalWrite(Left_Sonar, HIGH);// Right_Sonar핀을 5V(전류켜짐)출력
  delay(10);            //잠깐 켜진상태를 유지한다.
  digitalWrite(Left_Sonar, LOW); //Right_Sonar핀을 0V(전류꺼짐)출력
  pinMode(Left_Sonar, INPUT);    //Right_Sonar 입력
  duration = pulseIn(Left_Sonar, HIGH);
  distance=((float)(340*duration)/1000)/2; //10000 을 1000으로 바꿔줘야지  mm단위가 나온다. 
  return distance;        
}

float Front_Sonar_sensor()
{
  
  float duration=0.0;     //duration 지속시간 지역 변수 설정
  float distance=0.0;     //distance 거리 지역 변수 설정
  pinMode(Front_Sonar, OUTPUT); //10째에 꽅혀있는 Right를 켜준다. 
  digitalWrite(Front_Sonar, LOW); // Right_Sonar핀을 0V(전류꺼짐)출력
  digitalWrite(Front_Sonar, HIGH);// Right_Sonar핀을 5V(전류켜짐)출력
  delay(10);            //잠깐 켜진상태를 유지한다.
  digitalWrite(Front_Sonar, LOW); //Right_Sonar핀을 0V(전류꺼짐)출력
  pinMode(Front_Sonar, INPUT);    //Right_Sonar 입력
  duration = pulseIn(Front_Sonar, HIGH);
  distance=((float)(340*duration)/1000)/2; //10000 을 1000으로 바꿔줘야지  mm단위가 나온다. 
  return distance;        
}

void Front(int t,int c,int p){
  analogWrite(Left_Pin,c); 
  analogWrite(Rright_Pin,p);
  
  digitalWrite(Left_Pin_1,HIGH);  
  digitalWrite(Left_Pin_2,LOW);   
  digitalWrite(Right_Pin_1,HIGH);  
  digitalWrite(Right_Pin_2,LOW);  
  delay (t);
  }

void dack(int t){
  digitalWrite(Left_Pin_2,HIGH);  
  digitalWrite(Left_Pin_1,LOW);   
  digitalWrite(Right_Pin_2,HIGH);  
  digitalWrite(Right_Pin_1,LOW);
  delay(t);
}

void Left(int t, int c, int p){
  analogWrite(Left_Pin,c); 
  analogWrite(Rright_Pin,p);
   
  digitalWrite(Left_Pin_2,HIGH);  
  digitalWrite(Left_Pin_1,LOW);   
  digitalWrite(Right_Pin_1,HIGH);  
  digitalWrite(Right_Pin_2,LOW); 
  delay(t); 
}

void Right(int t, int c, int p){
  analogWrite(Left_Pin,c); 
  analogWrite(Rright_Pin,p);
  
  digitalWrite(Left_Pin_1,HIGH);  
  digitalWrite(Left_Pin_2,LOW);   
  digitalWrite(Right_Pin_2,HIGH);  
  digitalWrite(Right_Pin_1,LOW); 
  delay(t); 
}

void Stop(int t){
  digitalWrite(Left_Pin_1, LOW);
  digitalWrite(Left_Pin_2, LOW);
  digitalWrite(Right_Pin_1, LOW);
  digitalWrite(Right_Pin_2, LOW);
  delay(t);
}


void loop()  //반복 실행하는 함수, 모든 코들가 들어감, 메인 함수의 역활
{
  float F_distance1, R_distancel, L_distance1; // F_distance1, R_distancel, L_distance1 지역변수 지정
  float measure_width; //measure_width 지역변수 지정

  
  F_distance1 = Front_Sonar_sensor();     //F_Sonar_sensor()의 값을 F_distance1로 넣어준다. 
  R_distancel = Right_Sonar_sensor(); //Right_Sonar_sensor()의 값을 R_distancel로 넣어준다.
  L_distance1 = Left_Sonar_sensor();  //Left_Sonar_sensor()값을 L_distance1 넣어준다.
  Serial.print("F : ");
  Serial.print(F_distance1);
  Serial.print("mm   ");
  if(F_distance1 <= 200)
  {  
    Stop(100);
    if(R_distancel > L_distance1){
      Stop(200);
      Left(700, 80, 80);
      Stop(200);
      }
      else{
      Stop(200);
      Right(700, 80, 80);
      Stop(200);
      }   
  } 
  else{
    Front(1, 80, 80);
    }  
}



  
