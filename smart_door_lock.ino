#include <WiFi.h>
#include <IOXhop_FirebaseESP32.h>

#define FIREBASE_HOST "smart-door-lock-d389e.firebaseio.com"
#define FIREBASE_AUTH "fw3NmHedGViwmS8n41Qb8oH1aE6qjUAFZMwHujcv"

#define WIFI_SSID "Alex"
#define WIFI_PASSWORD "Alex#123"

String fireStatus = "";
const int relayPin = 23;

void setup() {

  Serial.begin(9600);
  delay(500);

  pinMode (relayPin, OUTPUT);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Serial.println("Success");
  digitalWrite(relayPin, HIGH);

}

void loop() {

  String value = Firebase.getString("/lockStatus");

  if (value == "1") {
    digitalWrite(relayPin, LOW);
  }
  else {
    digitalWrite(relayPin, HIGH);
  }


}
