#define  F_Sonar  8
#define  R_Sonar  10
#define  L_Sonar  11

float robot_width = 200; //차량의 폭
float mazor_width = 500; //결기장 폭 
float mazor_width_tolerance = 40; //오차 위범

int flag_mazor_1 = 0; // set 1

void setup()
{
  pinMode(F_Sonar, OUTPUT);
  pinMode(L_Sonar, OUTPUT);
  pinMode(R_Sonar, OUTPUT);
  Serial.begin(115200);
}

float F_sonar(void){
  
  float duration=0.0;
  float distance=0.0;
  pinMode(F_Sonar, OUTPUT);
  digitalWrite(F_Sonar,LOW);
  digitalWrite(F_Sonar,HIGH);
  delay(10);
  digitalWrite(F_Sonar,LOW);
  pinMode(F_Sonar, INPUT);
  duration=pulseIn(F_Sonar,HIGH);
  distance=((float)(340*duration)/1000)/2;
  return distance;
}

float R_sonar(void){
  
  float duration=0.0;
  float distance=0.0;
  pinMode(R_Sonar, OUTPUT);
  digitalWrite(R_Sonar,LOW);
  digitalWrite(R_Sonar,HIGH);
  delay(10);
  digitalWrite(R_Sonar,LOW);
  pinMode(R_Sonar, INPUT);
  duration=pulseIn(R_Sonar,HIGH);
  distance=((float)(340*duration)/1000)/2;
  return distance;
}

float L_sonar(void){
  
  float duration=0.0;
  float distance=0.0;
  pinMode(L_Sonar, OUTPUT);
  digitalWrite(L_Sonar,LOW);
  digitalWrite(L_Sonar,HIGH);
  delay(10);
  digitalWrite(L_Sonar,LOW);
  pinMode(L_Sonar, INPUT);
  duration=pulseIn(L_Sonar,HIGH);
  distance=((float)(340*duration)/1000)/2;
  return distance;
}


void loop() {
  float F_distance,R_distance,L_distance;
  float measure_widht=L_distance+R_distance+robot_width;
  if((measure_widht >= (mazor_width-mazor_width_tolerance)) && (measure_widht <= (mazor_width+mazor_width_tolerance))){
    if((F_distance>mazor_width) && (F_distance<mazor_width+400)){
      flag_mazor_1 = 1;
    }
    else{
      flag_mazor_1 = 0;
    }
  }
  else{
    flag_mazor_1 = 0;
  }
  
} 
