/*
Mr. Harms' Coding & Robotics Class
Aldersgate Christian Academy
05.11.2023

The following code for Arduino is written to allow you to control your 
robocar with a TV remote. Many of the common infrared remotes can work for this.
To learn which codes your remote transmits, run this code and open the serial monitor
With the serial monitor running, you will see displayed the codes as they are read by
the IR receiver. You will then need to use those codes down in the switch statement
in place of the values that are already there.
*/
#include <IRremote.h>
#include <Servo.h>  //servo library
Servo myservo;      // create servo object to control servo

int Echo = A4;  
int Trig = A5; 

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define carSpeed 250
#define turnSpeed 175
int distance = 0;


const byte IR_RECEIVE_PIN = 12;

void setup()
{
   myservo.attach(3);  // attach servo on pin 3 to servo object
   Serial.begin(9600);
   pinMode(Echo, INPUT);    
   pinMode(Trig, OUTPUT);
   Serial.println("IR Receive test");
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop()
{
   distance = Distance_test();
   //The following code checks if the distance is less than 20 and the car is not moving backwards
   //If all are true, the stop() function is called to stop the car.
   if(distance <= 20 && !(digitalRead(IN1) == 0 && digitalRead(IN2) == 1 && digitalRead(IN3) == 1 && digitalRead(IN4) == 0)){
     stop();
   }
  
   if (IrReceiver.decode())
   {
      Serial.print("Your remote just gave a code of: ");
      Serial.println(IrReceiver.decodedIRData.command);

      /*
      In the switch statement below, replace the values for each case with
      the code for the corresponding button on your IR remote.
      */ 
      switch(IrReceiver.decodedIRData.command){
        case 276: Serial.println("FORWARD"); forward(); delay(100); break;
        case 277: Serial.println("RIGHT"); turnRight(); delay(100); break;
        case 278: Serial.println("BACKWARDS"); backward(); delay(100); break;
        case 279: Serial.println("LEFT"); turnLeft(); delay(100); break;
        case 233: Serial.println("STOP"); stop(); delay(100); break;
        case 232: Serial.println("DANCE"); dance(); break;
        case 247: Serial.println("LOOK LEFT"); lookLeft(); break;
        case 246: Serial.println("LOOK STRAIGHT"); lookStraight(); break;
        case 259: Serial.println("LOOK RIGHT"); lookRight(); break;
     }
      
      IrReceiver.resume();
      
   }
}

void forward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go forward!");
  Serial.println(digitalRead(IN1));
  Serial.println(digitalRead(IN2));
  Serial.println(digitalRead(IN3));
  Serial.println(digitalRead(IN4));
  myservo.write(90); 
  
}

void backward(){
  analogWrite(ENA, carSpeed);
  analogWrite(ENB, carSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  Serial.println("go back!");
  myservo.write(90);
}

void turnRight(){
  digitalWrite(ENA,turnSpeed); //enable L298n A channel
  digitalWrite(ENB,turnSpeed); //enable L298n B channel
  digitalWrite(IN1,HIGH); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,LOW); //set IN4 low level 
  Serial.println("Slow right");//send message to serial monitor
  myservo.write(45); 
}

void turnLeft(){
  digitalWrite(ENA,turnSpeed); //enable L298n A channel
  digitalWrite(ENB,turnSpeed); //enable L298n B channel
  digitalWrite(IN1,LOW); //set IN1 hight level
  digitalWrite(IN2,LOW);  //set IN2 low level
  digitalWrite(IN3,LOW);  //set IN3 low level
  digitalWrite(IN4,HIGH); //set IN4 low level
  Serial.println("Slow left");//send message to serial monitor
  myservo.write(135); 
}
void spinLeft(){
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  Serial.println("go left!");
}

void spinRight(){
  analogWrite(ENA, turnSpeed);
  analogWrite(ENB, turnSpeed);
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

void dance(){
   forward();
   delay(1000);
   spinLeft();
   delay(500);
   spinRight();
   delay(1000);
   spinLeft();
   delay(500);
   forward();
   delay(1000);
   spinLeft();
   delay(500);
   spinRight();
   delay(1000);
   spinLeft();
   delay(500);
   backward();
   delay(1000);
   spinLeft();
   delay(500);
   spinRight();
   delay(1000);
   spinLeft();
   delay(500);
   stop();
}
//Ultrasonic distance measurement Sub function
int Distance_test() {
  digitalWrite(Trig, LOW);   
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);  
  delayMicroseconds(20);
  digitalWrite(Trig, LOW);   
  float Fdistance = pulseIn(Echo, HIGH);  
  Fdistance= Fdistance / 58;       
  return (int)Fdistance;
}  
void lookStraight(){
  myservo.write(90);
}
void lookLeft(){
  myservo.write(135);
}
void lookRight(){
  myservo.write(45);
}
