// Motor A
int motor1Pin1 = 12; 
int motor1Pin2 = 14; 
int enable1Pin = 13; 

// Setting minimum duty cycle
int dutyCycle = 60;


void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial.println("Press an arrow key to see which one was pressed!");

  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  //Apply power to spin at maximum speed
  digitalWrite(enable1Pin, HIGH);

  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the incoming byte
    int incomingByte = Serial.read();
    
    // Check for arrow key codes (these are typical key codes, may vary by system)
    switch (incomingByte) {
      case 65: // Up arrow (may need adjustment based on your system)
        Serial.println("Moving Forward");
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);
        break;
      
      case 66: // Down arrow
        Serial.println("Down Arrow Pressed");
        break;
      
      case 67: // Right arrow
        Serial.println("Right Arrow Pressed");
        break;
      
      case 68: // Left arrow
        Serial.println("Left Arrow Pressed");
        break;
      
      default:
        Serial.print("Received key code: ");
        Serial.println(incomingByte);
        
        // Stop the DC motor
        Serial.println("Motor stopped");
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        break;
    }
  }
}