#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SoftwareSerial.h>

const char *ssid = "POCO M3";
const char *password = "********";

ESP8266WebServer server(80);
SoftwareSerial wifi(D1, D2);

IPAddress x[30];
int ip_count, selected_ip;

String condition = "y";

void handleRoot() {
  // IPAddress ip_client = server.client().remoteIP();
  // for(int i = 0; i <= ip_count; i++){
  //   if(ip_client == x[i])break;
  //   if(i == ip_count){
  //     x[ip_count] = server.client().remoteIP();
  //     ip_count++;
  //   }
  // }
  server.send(200, "text/html", "\
<html>\
    <head>\
        <title>WiFi Controlled Car</title>\
        <style>\
            body {\
                display: flex;\
                align-items: center;\
                justify-content: center;\
                height: 100vh;\
                margin: 0;\
            }\
\
            .center {\
                text-align: center;\
            }\
\
            button {\
                font-size: 90px;\
                margin: 5px;\
            }\
        </style>\
    </head>\
    <body>\
        <div class=\"center\">\
            <button onclick='send(\"f\")'>Forward</button><br>\
            <button onclick='send(\"b\")'>Backward</button><br>\
            <button onclick='send(\"l\")'>Left</button><br>\
            <button onclick='send(\"r\")'>Right</button><br>\
            <button onclick='send(\"s\")'>Stop</button>\
        </div>\
\
        <script>\
            function send(val) {\
                var xhr = new XMLHttpRequest();\
                xhr.open('GET', '/data?data=' + val, true);\
                xhr.send();\
            }\
        </script>\
    </body>\
</html>\
");
}

void handleSend() {
  String data = server.arg("data");
  // if(x[selected_ip] == server.client().localIP())Serial.println(data);
  // for(int i = 0; i < ip_count; i++)Serial.println(x[i]);
  if (condition == "y")wifi.println(data);
  Serial.println(data);
  server.send(200);
}

void handleSelect() {
  condition = server.arg("data");
  // selected_ip = data.toInt();
  // Serial.println(data);
  server.send(200);
}

void setup() {
  Serial.begin(115200);
  wifi.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Setup HTTP server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/data", HTTP_GET, handleSend);
  server.on("/select", HTTP_GET, handleSelect);
  server.begin();
}

void loop() {
  server.handleClient();
}
