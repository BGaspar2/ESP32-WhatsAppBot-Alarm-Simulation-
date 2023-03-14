//USED ​​LIBRARIES
#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h>
// CALLMEBOT CREDENTIALS
String apiKey = "YOUR-API-KEY";
String phone_number = "YOUR-PHONE-NUMBER";
String url;

const int LIGHT = 26; // Pin led
const int Button = 14; //PIN Button
int switchState = 0;     // actual read value from pin4
int oldSwitchState = 0;  // last read value from pin4
int lightsOn = 0;        // is the switch on = 1 or off = 0


// Define your WIFI settings.

const char *ssid = "YOUR-SSID-NETWORK";

const char *password = "YOUR-PASSWORD-NETWORK";


void message_to_whatsapp(String message)  //is our user defined function that will send messages to whatsapp messenger.
{
//adding all the numbers, your api key, your message in a complete url
  url = "https://api.callmebot.com/whatsapp.php?phone=" + phone_number + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Message sent successfully");
  } else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();
}




void setup() {
  Serial.begin(9600);
  pinMode(LIGHT, OUTPUT);
  pinMode(Button, INPUT);
  //thing.SetWiFi(, "");
  // It is just for assuring connection is alive.
  WiFi.mode(WIFI_OFF);
  delay(1000);
  // This mode allows NodeMCU to connect any WiFi directly.
  WiFi.mode(WIFI_STA);
  // Connect NodeMCU to your WiFi.

  WiFi.begin(ssid, password);

  Serial.print("\n\n");

  Serial.print("Try to connect to WiFi. Please wait! ");

  Serial.print("\n\n");
  // Halt the code until connected to WiFi.
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("*");
  }
  // If connection is successful, turn control led(if used) on and write WiFi SSID to serial monitor along with assigned IPAddress.
  Serial.print("\n\n");
  Serial.print("-------------------------------------");
  Serial.print("\n\n");
  Serial.print("Connection is successful!");
  Serial.print("\n\n");
  Serial.print("Connected WiFi SSID : ");
  Serial.print(ssid);
  Serial.print("\n\n");
  Serial.println("Connected IPAddress : ");
  Serial.println(WiFi.localIP());
  Serial.print("\n\n");
}


void loop() {

  if (digitalRead(Button) == HIGH) {
    // toggle
    digitalWrite(LIGHT, HIGH);
  }
  if (digitalRead(LIGHT) == HIGH) {
    delay(5000);
    message_to_whatsapp("URGENT MESSAGE: ALARM ON 🚨!! To turn it off write deactivate or the number 2");
    Serial.print("\n");
    delay(5000);
  }
}
