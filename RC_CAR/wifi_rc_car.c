#include <ESP8266WiFi.h>

// Motor A
int motor1Pin1 = 12; 
int motor1Pin2 = 14; 
int enable1Pin = 13; 

// Motor B
int motor2Pin1 = 5; 
int motor2Pin2 = 4; 
int enable2Pin = 0; 


// Pela numeração do GPIO:
int LED_FRONT  = D8; 
int LED_BACK  = 1; //TX

// Setting minimum duty cycle
int dutyCycle = 60;

// Replace with your network credentials
const char* ssid = "#################";
const char* password = "##############";

// Create a web server on port 80
WiFiServer server(80);

// Variables to store the 4 inputs
String input1 = "";
String input2 = "";
String input3 = "";
String input4 = "";

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial.println("Press an arrow key to see which one was pressed!");
  
  pinMode(LED_FRONT, OUTPUT);
  pinMode(LED_BACK, OUTPUT);

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);

  // testing
  Serial.print("Testing DC Motor...");
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
  //Apply power to spin at maximum speed
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(enable2Pin, HIGH);

   
    // Assuming input2 is a String variable from your previous context
    if (input2 == "forward") {
        Serial.println("Moving Forward");
        digitalWrite(LED_FRONT, HIGH);
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);
    }
    else if (input2 == "left") {
        Serial.println("Left Arrow Pressed");
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
    }
    else if (input2 == "backward") {
        Serial.println("Down Arrow Pressed");
        digitalWrite(LED_BACK, HIGH);
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);
    }
    else if (input2 == "right") {
        Serial.println("Right Arrow Pressed");
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
    }
    else {
        digitalWrite(LED_BACK, LOW);
        digitalWrite(LED_FRONT, LOW);
        // Stop the DC motor (default case)
        Serial.println("Motor stopped");
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
    }
  }

  delay(1);
  client.stop();
}