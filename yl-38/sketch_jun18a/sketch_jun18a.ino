#include <math.h>


void setup() {
  // initialize serial communication at 9600 bits per second:

  Serial.begin(9600);
  /*pinMode(1, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(15, OUTPUT);*/

  Serial.println("Cargando...");


}

double Thermistor(int RawADC) {
  double Temp;
  Temp = log(10000.0 * ((1024.0 / RawADC - 1)));
  //         =log(10000.0/(1024.0/RawADC-1)) // for pull-up configuration
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;            // Convert Kelvin to Celcius
  /*Temp = (Temp * 9.0) / 5.0 + 32.0; // Convert Celcius to Fahrenheit*/
  return Temp;
}

// the loop routine runs over and over again forever:
void loop() {
  // Set LED colour to their Digital Ouputs.  Read the input on analog pin 0:
  /*int yellow = 1;
    int blue = 3;
    int red = 15;*/
  int sensorValue = analogRead(0);
  /*Serial.println(sensorValue);*/
  /*int T = T - sensorValue;273.15;*/

  Serial.print("Temperature: ");
  Serial.println(int(Thermistor(sensorValue)));  // display Fahrenheit
  Serial.println(" C");

  delay(500);

  // Set the initial state of the LEDs to OFF
  /*digitalWrite(1, LOW);
    digitalWrite(3, LOW);
    digitalWrite(15, LOW);

    // Logic Loop that sets the required LED to ON
    if (sensorValue >= 1000) (digitalWrite(yellow, HIGH));
    else if ((sensorValue <= 999) && (sensorValue >=901)) (digitalWrite(blue, HIGH));
    else if (sensorValue <= 900) (digitalWrite(red, HIGH));
    else ;
  */
  // Prints the condition of soil.  Dry, Wet or Perfect
  /*if (sensorValue >= 400) (Serial.print("¿ESTAMOS EN EL CONGELADOR?"));
    else if ((sensorValue <= 399) && (sensorValue >=300)) (Serial.print("EL VENTILADOR ESTÁ PRENDIDO"));
    else if (sensorValue <= 299) (Serial.print("EL VENTILADOR ESTÁ APAGADO"));
  */
  /*
    // print out the value you read:
    Serial.print("Marijuana Soil Humidity is: ");
    Serial.println(sensorValue);
    delay(500);        // delay in between reads for stability
  */


}
