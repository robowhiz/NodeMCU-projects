#include <DHT.h>  // Including library for dht 
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

String apiKey = "4UK3XE2333J27XE7";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "POCO M3";     // replace with your wifi ssid and wpa2 key
const char *password =  "********";

 // Domain Name with full URL Path for HTTP POST Request
const char* serverName = "http://api.thingspeak.com/update";

#define DHTPIN D5          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);
 
WiFiClient client;

float t_prev, h_prev;
unsigned long timer;
bool sent = false;

void setup() 
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(10);
  dht.begin();

  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 10 seconds (timerDelay variable), it will take 10 seconds before publishing the first reading.");
}

void loop() 
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

   if((WiFi.status()== WL_CONNECTED && t_prev != t && h_prev != h && millis() - timer > 20000) || !sent){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String httpRequestData = "api_key=" + apiKey + "&field1=" + String(h) + "&field2=" + String(t);           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);

      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      // Free resources
      http.end();
      if(httpResponseCode == 200){
        timer = millis();
        sent = true;
        digitalWrite(LED_BUILTIN, LOW);
        delay(5000);
        digitalWrite(LED_BUILTIN, HIGH);
      }
      else sent = false;
    }
    else if (WiFi.status() == WL_DISCONNECTED) {
      Serial.println("WiFi Disconnected");
    }
  
  t_prev = t;
  h_prev = h;
  Serial.printf("%0.2f\t%0.2f\n", t, h);
  delay(1000);
}