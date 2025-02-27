//www.elegoo.com

//Edited by Mr. Harms
//02/27/2025
//This starter code will help you get your RoboCar moving


//    The direction of the car's movement
//  ENA   ENB   IN1   IN2   IN3   IN4   Description  
//  HIGH  HIGH  HIGH  LOW   LOW   HIGH  Car is running forward
//  HIGH  HIGH  LOW   HIGH  HIGH  LOW   Car is running back
//  HIGH  HIGH  LOW   HIGH  LOW   HIGH  Car is turning left
//  HIGH  HIGH  HIGH  LOW   HIGH  LOW   Car is turning right
//  HIGH  HIGH  LOW   LOW   LOW   LOW   Car is stopped
//  HIGH  HIGH  HIGH  HIGH  HIGH  HIGH  Car is stopped
//  LOW   LOW   N/A   N/A   N/A   N/A   Car is stopped


// Define IO pins for motor controller module
const int ENA = 5;  // Enable pin for motor A
const int ENB = 6;  // Enable pin for motor B
const int IN1 = 7;  // Control pin 1 for motor A
const int IN2 = 8;  // Control pin 2 for motor A
const int IN3 = 9;  // Control pin 1 for motor B
const int IN4 = 11; // Control pin 2 for motor B
const int echoPin = A4; // attach pin A4 Arduino to pin Echo of HC-SR04
const int trigPin = A5; //attach pin A5 Arduino to pin Trig of HC-SR04
long duration; // variable for the duration of sound wave travel

void forward(){ 
  digitalWrite(ENA,HIGH); // Enable motor A
  digitalWrite(ENB,HIGH); // Enable motor B
  digitalWrite(IN1,HIGH); // Set motor A to move forward
  digitalWrite(IN2,LOW);  // Set motor A to move forward
  digitalWrite(IN3,LOW);  // Set motor B to move forward
  digitalWrite(IN4,HIGH); // Set motor B to move forward
  Serial.println("Forward"); // Print movement direction to serial monitor
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
  
  return dist; // Return the measured distance
}

// Before executing loop() function, 
// setup() function will execute first and only execute once
void setup() {
  Serial.begin(9600); // Open serial communication and set the baud rate
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
  forward();  // Move forward
  delay(1000); // Wait for 1 second
  back();     // Move backward
  delay(1000); // Wait for 1 second
}
