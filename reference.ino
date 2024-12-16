
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Define the RFID scanner's RX and TX pins
#define RFID_RX_PIN 2 // Connect the RFID's TX pin to NodeMCU's GPIO2
(D2)
#define RFID_TX_PIN 3 // Connect the RFID's RX pin to NodeMCU's GPIO3
(D3)
SoftwareSerial RFID(RFID_RX_PIN, RFID_TX_PIN); // Create a software
serial object
const char* ssid = "Your_SSID"; // Replace with your Wi-Fi SSID
const char* password = "Your_PASSWORD"; // Replace with your Wi-Fi
password
const char* FIREBASE_HOST = "your-firebase-database-url.firebaseio.com";
const char* FIREBASE_AUTH = "your-firebase-auth-token";
FirebaseData firebaseData;
void setup() {
Serial.begin(9600); // Initialize the serial monitor
RFID.begin(9600); // Initialize the RFID scanner's serial communication
// Connect to Wi-Fi
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.println("Connecting to WiFi...");
}
Serial.println("Connected to WiFi");
// Initialize Firebase
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.reconnectWiFi(true);
}
void loop() {
if (RFID.available()) {
String tagData = RFID.readString();
tagData.trim();
Serial.print("Scanned RFID tag: ");
Serial.println(tagData);
// Send data to Firebase
Firebase.setString(firebaseData, "/rfid/tagData", tagData);
if (firebaseData.dataType() == "string") {
Serial.print("Data sent to Firebase: ");
Serial.println(firebaseData.stringData());
} else {
Serial.println("Error sending data to Firebase");
}
}
}
