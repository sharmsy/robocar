//www.elegoo.com

//Edited by Mr. Harms
//03/25/2025
//This starter code will help get your RoboCar, distance sensor and servo moving


//  The direction of the car's movement
//  ENA   ENB   IN1   IN2   IN3   IN4   Description  
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car is running forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car is running back
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car is turning left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car is turning right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car is stopped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car is stopped
//  LOW   LOW   N/A   N/A   N/A   N/A   Car is stopped


// Define IO pins for motor controller module
#include <Servo.h> // includes servo library
Servo myservo; // create servo object to control servo
const int ENA = 5;  // Enable pin for motor A
const int ENB = 6;  // Enable pin for motor B
const int IN1 = 7;  // Control pin 1 for motor A
const int IN2 = 8;  // Control pin 2 for motor A
const int IN3 = 9;  // Control pin 1 for motor B
const int IN4 = 11; // Control pin 2 for motor B
const int echoPin = A4; // attach pin A4 Arduino to pin Echo of HC-SR04
const int trigPin = A5; //attach pin A5 Arduino to pin Trig of HC-SR04
long duration; // variable for the duration of sound wave travel
int rightDistance = 0,leftDistance = 0,middleDistance = 0 ;
const int threshold = 25;

void forward(){ 
  digitalWrite(ENA,HIGH); // Enable motor A
  digitalWrite(ENB,HIGH); // Enable motor B
  digitalWrite(IN1,HIGH); // Set motor A to move forward
  digitalWrite(IN2,LOW);  // Set motor A to move forward
  digitalWrite(IN3,LOW);  // Set motor B to move forward
  digitalWrite(IN4,HIGH); // Set motor B to move forward
  Serial.println("Forward"); // Print movement direction to serial monitor
}

void turnLeft(){ 
  digitalWrite(ENA,HIGH); // Enable motor A
  digitalWrite(ENB,HIGH); // Enable motor B
  digitalWrite(IN1,LOW); // Set motor A to move forward
  digitalWrite(IN2,LOW);  // Set motor A to move forward
  digitalWrite(IN3,LOW);  // Set motor B to move forward
  digitalWrite(IN4,HIGH); // Set motor B to move forward
  Serial.println("Left"); // Print movement direction to serial monitor
}

void turnRight(){ 
  digitalWrite(ENA,HIGH); // Enable motor A
  digitalWrite(ENB,HIGH); // Enable motor B
  digitalWrite(IN1,HIGH); // Set motor A to move forward
  digitalWrite(IN2,LOW);  // Set motor A to move forward
  digitalWrite(IN3,LOW);  // Set motor B to move forward
  digitalWrite(IN4,LOW); // Set motor B to move forward
  Serial.println("Right"); // Print movement direction to serial monitor
}

void stop(){ 
  digitalWrite(ENA,HIGH); // Enable motor A
  digitalWrite(ENB,HIGH); // Enable motor B
  digitalWrite(IN1,LOW); // Set motor A to move forward
  digitalWrite(IN2,LOW);  // Set motor A to move forward
  digitalWrite(IN3,LOW);  // Set motor B to move forward
  digitalWrite(IN4,LOW); // Set motor B to move forward
  Serial.println("Stop"); // Print movement direction to serial monitor
}

void back(){
  digitalWrite(ENA,HIGH); // Enable motor A
  digitalWrite(ENB,HIGH); // Enable motor B
  digitalWrite(IN1,LOW);  // Set motor A to move backward
  digitalWrite(IN2,HIGH); // Set motor A to move backward
  digitalWrite(IN3,HIGH); // Set motor B to move backward
  digitalWrite(IN4,LOW);  // Set motor B to move backward
  Serial.println("Back"); // Print movement direction to serial monitor
}

// Function to measure distance using an ultrasonic sensor
int getDistance()
{
  int dist; // Variable to store calculated distance
  digitalWrite(trigPin, LOW); // Ensure trigger pin is low before starting
  delayMicroseconds(2); // Short delay to stabilize sensor
  
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds to send out a pulse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculating the distance in centimeters
  dist = duration * 0.034 / 2; // Speed of sound (0.034 cm/µs) divided by 2 (round trip)
  Serial.println(dist);
  return dist; // Return the measured distance
}

void stopAndTurn()
{
  stop();
  delay(500);
  myservo.write(10);//10°-180° turn the servo to the LEFT      
  delay(1000);      
  rightDistance = getDistance();  //set the rightDistance variable to the distance it reads to the RIGHT
  Serial.print("rightDistance=");
  Serial.println(rightDistance); //print out the distance value
  
  myservo.write(180);//10°-180° turn the servo to the LEFT      
  delay(1000);      
  leftDistance = getDistance();  //set the rightDistance variable to the distance it reads to the LEFT
  Serial.print("leftDistance=");
  Serial.println(leftDistance); //print out the distance value
  myservo.write(90);
 
  if((rightDistance<=threshold)||(leftDistance<=threshold))
  {
    back();
    delay(300);
    stopAndTurn();
    
  }
 
  else if(rightDistance>leftDistance)  
  {
    turnRight();
    delay(650);
  }
  else if(rightDistance<leftDistance)
  {
  turnLeft();
  delay(650);
  }

  else
  {
  forward();
  }
} //end of stopAndTurn function

// Before executing loop() function, 
// setup() function will execute first and only execute once
void setup() {
  myservo.write(90);
  Serial.begin(9600); // Open serial communication and set the baud rate
  myservo.attach(3);// attach servo on pin 3 to servo object
  pinMode(IN1,OUTPUT); // Set motor control pins as output
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
  pinMode(ENA,OUTPUT); // Set motor enable pins as output
  pinMode(ENB,OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets pin 3 as an OUTPUT
  pinMode(echoPin, INPUT); // Sets pin 2 as an INPUT
}

// Repeat execution
void loop() {
  if(getDistance() < 25)
  {
    stop();
  }
  else{
    forward();  // Move forward
  }
}