#include <FirebaseJson.h>
#include <jsmn.h>
#include <FirebaseESP32.h>
#include <FirebaseESP32HTTPClient.h>


//2. Include ESP8266WiFi.h and must be included after FirebaseESP8266.h
#include <ESP8266WiFi.h>

/*
 * created by Rui Santos, https://randomnerdtutorials.com
 * 
 * Complete Guide for Ultrasonic Sensor HC-SR04
 *
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */
 
 
int trigPin = 5;    // Trigger
int echoPin = 4;    // Echo
long duration, cm, inches;

//3. Declare the Firebase Data object in global scope
FirebaseData firebaseData;

//4. Setup Firebase credential in setup()
Firebase.begin("micro-esp826.firebaseio.com", "FKjvBH0LigKZzZO3uSODfIJlRLs5CaAWk5yhNBz7");

//5. Optional, set AP reconnection in setup()
Firebase.reconnectWiFi(true);

//6. Optional, set number of error retry
 Firebase.setMaxRetry(firebaseData, 3);

//7. Optional, set number of error resumable queues
Firebase.setMaxErrorQueue(firebaseData, 30);

//8. Optional, use classic HTTP GET and POST requests.  
Firebase.enableClassicRequest(firebaseData, true);
 
void setup() {
  //Serial Port begin
  Serial.begin (9600);
  //Define inputs and outputs
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}
 
void loop() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  inches = (duration/2) / 74;   // Divide by 74 or multiply by 0.0135
  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  delay(250);
}
