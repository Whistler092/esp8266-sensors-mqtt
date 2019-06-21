#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>

// Connect to the WiFi
const char* ssid = "WIFI";
const char* password = "WIFIPASS";
const char* mqtt_server = "192.168.0.22";
char* ip = "";

WiFiClient espClient;
PubSubClient client(espClient);

const byte ledPin = 0;  //Pin With LED on AdaFruit


void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(ledPin, OUTPUT);

}

void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();

  sendTemp();
  delay(1000); 

}

void sendTemp(){
  int sensorValue = analogRead(0);
  
  if (sensorValue >= 400) (Serial.print("¿ESTAMOS EN EL CONGELADOR?"));
  else if ((sensorValue <= 399) && (sensorValue >=300)) (Serial.print("EL VENTILADOR ESTÁ PRENDIDO"));
  else if (sensorValue <= 299) (Serial.print("EL VENTILADOR ESTÁ APAGADO"));
  Serial.println(sensorValue);

  String payload = "{\"temp\":";
  payload += "\""+(String)sensorValue+"\"";
  payload += ",\"ip\":";
  payload += "\""+ip2Str(WiFi.localIP())+"\"";
  payload += "}";
  client.publish("temp",  (char*)payload.c_str() );
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    char receivedChar = (char)payload[i];
    Serial.print(receivedChar);
    if (receivedChar == '0')
      // ESP8266 Huzzah outputs are "reversed"
      digitalWrite(ledPin, HIGH);
    if (receivedChar == '1')
      digitalWrite(ledPin, LOW);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266 Client")) {
      Serial.println("connected");
      // ... and subscribe to topic
      client.subscribe("ledStatus");

      // Once connected, publish an announcement...      
      String payload = "{\"message\":";
      payload += "\"Esp 8266 conectada correctamente\"";
      payload += ",\"ip\":";
      payload += "\""+ip2Str(WiFi.localIP())+"\"";
      payload += "}";
      client.publish("espConnected",  (char*)payload.c_str() );
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

String ip2Str(IPAddress ip){
  String s="";
  for (int i=0; i<4; i++) {
    s += i  ? "." + String(ip[i]) : String(ip[i]);
  }
  return s;
}
