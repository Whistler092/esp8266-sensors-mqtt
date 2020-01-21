/*
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED_BUILTIN to find the pin with the internal LED
*/
int Status = 12;
int SENSOR = 13;
uint32_t timer = 0;


void setup() {
  Serial.begin(115200);
  
  pinMode(Status, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  pinMode(SENSOR, INPUT);

  
}

// the loop function runs over and over again forever
void loop() { 
  long state = digitalRead(SENSOR);
  Serial.println(state);
  Serial.print("Time: ");
  timer = millis();
  Serial.println(timer);
  if(state == HIGH){
    digitalWrite(Status, HIGH);
    Serial.println("Motion Detected!");
    delay(1000);
  }else {
    digitalWrite(Status, LOW);
    Serial.println("Motion Absent!");
    delay(1000);
  }
  
  
}
