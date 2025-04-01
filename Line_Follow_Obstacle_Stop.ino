//Custom code modified by Mr. Harms
//03.28.2024

//Line Tracking IO define
#include <Servo.h> //servo library
Servo myservo; // create servo object to control servo

#define LT_R digitalRead(10)
#define LT_M digitalRead(4)
#define LT_L digitalRead(2)


const int ENA = 5;  // Enable pin for motor A
const int ENB = 6;  // Enable pin for motor B
const int IN1 = 7;  // Control pin 1 for motor A
const int IN2 = 8;  // Control pin 2 for motor A
const int IN3 = 9;  // Control pin 1 for motor B
const int IN4 = 11; // Control pin 2 for motor B

#define carSpeed 125
#define turnSpeed 250
#define spinSpeed 250

int echo = A4;  
int trig = A5;

int dist = 1000;
int threshold = 15;
int sensorReading = 4;


void forward(){
  myservo.write(90);
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
  myservo.write(45);
  analogWrite(ENA,turnSpeed); //enable L298n A channel
  analogWrite(ENB,turnSpeed); //enable L298n B channel
  digitalWrite(IN1,HIGH); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,LOW); //set IN4 low level 
  Serial.println("Slow right");//send message to serial monitor
}

void turnLeft(){
  myservo.write(135);
  analogWrite(ENA,turnSpeed); //enable L298n A channel
  analogWrite(ENB,turnSpeed); //enable L298n B channel
  digitalWrite(IN1,LOW); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 low level
  Serial.println("Slow left");//send message to serial monitor
}
void spinLeft(){
  myservo.write(180);
  analogWrite(ENA, spinSpeed);
  analogWrite(ENB, spinSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void spinRight(){
  myservo.write(0);
  analogWrite(ENA, spinSpeed);
  analogWrite(ENB, spinSpeed);
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

int getDistance()   
{
  digitalWrite(trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(trig, LOW);   
  float Fdistance = pulseIn(echo, HIGH);  
  Fdistance= Fdistance/58;       
  return (int)Fdistance;
}

void setup(){
  myservo.attach(3);// attach servo on pin 3 to servo object
  myservo.write(90);
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(echo, INPUT);    
  pinMode(trig, OUTPUT);  
  pinMode(LT_R,INPUT);
  pinMode(LT_M,INPUT);
  pinMode(LT_L,INPUT);
}

int lastKnownDirection = 0; // 0 = Center, 1 = Right, -1 = Left

void loop() {
  int distance = getDistance(); // Get distance from sensor

  if (distance <= threshold) {
    stop(); // Stop if obstacle detected within threshold
    Serial.println("Obstacle detected!");
    return; // Skip rest of loop
  }

  if (LT_M) { // Middle sensor on the line
    forward();
    lastKnownDirection = 0;
  }
  else if (LT_R) { // Right sensor on the line
    turnRight();
    while (LT_R); // Keep turning right until line is lost
    lastKnownDirection = 1;
  }
  else if (LT_L) { // Left sensor on the line
    turnLeft();
    while (LT_L); // Keep turning left until line is lost
    lastKnownDirection = -1;
  }
  else if (!LT_M && !LT_R && !LT_L) { // No line detected
    if (lastKnownDirection == 1) {
      turnRight();
    } else if (lastKnownDirection == -1) {
      turnLeft();
    } else {
      spinLeft(); // Default action if direction is unknown
    }
    while (!LT_M && !LT_R && !LT_L);
  }
}