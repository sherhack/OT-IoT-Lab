#include <ESP8266WiFi.h>

// Replace with your network credentials
const char* ssid = "##############";
const char* password = "##############";

// Create a web server on port 80
WiFiServer server(80);

// Variables to store the 4 inputs
String input1 = "";
String input2 = "";
String input3 = "";
String input4 = "";

void setup() {
  Serial.begin(115200);
  
  // Connect to WiFi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  
  // Start the server
  server.begin();
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  while (!client.available()) {
    delay(1);
  }
  
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  client.flush();
  
  // Parse the inputs from the URL
  // Expected format: http://[IP]/set?in1=value1&in2=value2&in3=value3&in4=value4
  
  if (request.indexOf("/set") != -1) {
    int pos1 = request.indexOf("in1=");
    int pos2 = request.indexOf("in2=");
    int pos3 = request.indexOf("in3=");
    int pos4 = request.indexOf("in4=");
    
    if (pos1 != -1) {
      input1 = request.substring(pos1 + 4, request.indexOf('&', pos1));
    }
    if (pos2 != -1) {
      input2 = request.substring(pos2 + 4, request.indexOf('&', pos2));
    }
    if (pos3 != -1) {
      input3 = request.substring(pos3 + 4, request.indexOf('&', pos3));
    }
    if (pos4 != -1) {
      input4 = request.substring(pos4 + 4, request.indexOf(' ', pos4));
    }
    
    // Print received inputs to Serial Monitor
    Serial.println("Received inputs:");
    Serial.println("Input 1: " + input1);
    Serial.println("Input 2: " + input2);
    Serial.println("Input 3: " + input3);
    Serial.println("Input 4: " + input4);
  }

  
  delay(1);
  client.stop();
}