//www.elegoo.com
//Custom code modified by Mr. Harms
//05.09.2023

//Line Tracking IO define
#define LT_R !digitalRead(10)
#define LT_M !digitalRead(4)
#define LT_L !digitalRead(2)

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define carSpeed 175
#define turnSpeed 150

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
}

void back(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
}

void turnRight(){
  digitalWrite(ENA,turnSpeed); //enable L298n A channel
  digitalWrite(ENB,turnSpeed); //enable L298n B channel
  digitalWrite(IN1,HIGH); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,LOW); //set IN4 low level 
  Serial.println("Slow right");//send message to serial monitor
}

void turnLeft(){
  digitalWrite(ENA,turnSpeed); //enable L298n A channel
  digitalWrite(ENB,turnSpeed); //enable L298n B channel
  digitalWrite(IN1,LOW); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 low level
  Serial.println("Slow left");//send message to serial monitor
}
void spinLeft(){
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void spinRight(){
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  Serial.println("go right!");
} 

void stop(){
   digitalWrite(ENA, LOW);
   digitalWrite(ENB, LOW);
   Serial.println("Stop!");
} 

void setup(){
  Serial.begin(9600);
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
}

void loop() {
  if(LT_M){
    forward();
  }
  else if(LT_R) { 
    turnRight();
    while(LT_R);                             
  }   
  else if(LT_L) {
    turnLeft();
    while(LT_L);  
  }
  else if (!LT_M && !LT_R && !LT_L){
    spinLeft();
    while(!LT_M && !LT_R && !LT_L);
  }
}

