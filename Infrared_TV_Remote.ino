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

#define ENA 5
#define ENB 6
#define IN1 7
#define IN2 8
#define IN3 9
#define IN4 11

#define carSpeed 175
#define turnSpeed 175


const byte IR_RECEIVE_PIN = 12;

void setup()
{
   Serial.begin(9600);
   Serial.println("IR Receive test");
   IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
}

void loop()
{
   if (IrReceiver.decode())
   {
      Serial.print("Your remote just gave a code of: ");
      Serial.println(IrReceiver.decodedIRData.command);

      /*
      In the switch statement below, replace the values for each case with
      the code for the corresponding button on your IR remote.
      */ 
      switch(IrReceiver.decodedIRData.command){
        case 123: Serial.println("FORWARD"); forward(); delay(100); break;
        case 124: Serial.println("RIGHT"); turnRight(); delay(100); break;
        case 125: Serial.println("BACKWARDS"); backward(); delay(100); break;
        case 126: Serial.println("LEFT"); turnLeft(); delay(100); break;
        case 70: Serial.println("STOP"); stop(); delay(100); break;
        case 150: Serial.println("DANCE"); dance(); break;
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
}

void backward(){
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
