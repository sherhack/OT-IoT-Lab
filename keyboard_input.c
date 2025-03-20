void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial.println("Press an arrow key to see which one was pressed!");
}

void loop() {
  // Check if data is available to read
  if (Serial.available() > 0) {
    // Read the incoming byte
    int incomingByte = Serial.read();
    
    // Check for arrow key codes (these are typical key codes, may vary by system)
    switch (incomingByte) {
      case 65: // Up arrow (may need adjustment based on your system)
        Serial.println("Up Arrow Pressed");
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
        break;
    }
  }
}