import keyboard
import requests
import time

# Base URL of your Arduino's IP address (from the previous code's Serial output)
BASE_URL = "http://192.168.1.111"  # Replace with your Arduino's IP address

# Variables to track current state
current_speed = 0
current_direction = "stop"

def send_command(speed, direction):
    """Send HTTP request to Arduino with speed and direction"""
    global current_speed, current_direction
    
    # Only send if state has changed
    if speed != current_speed or direction != current_direction:
        try:
            url = f"{BASE_URL}/set?in1={speed}&in2={direction}&in3=0&in4=0"
            response = requests.get(url, timeout=1)
            print(f"Sent: Speed={speed}, Direction={direction}")
            current_speed = speed
            current_direction = direction
        except requests.exceptions.RequestException as e:
            print(f"Error sending command: {e}")

def stop_car():
    """Stop the car"""
    send_command(0, "stop")

def main():
    print("RC Car Control - Use arrow keys to control")
    print("Up: Forward, Down: Backward, Left/Right: Turn")
    print("Press 'q' to quit")

    # Main control loop
    while True:
        # Forward movement
        if keyboard.is_pressed('up'):
            send_command(100, "forward")  # Speed 100 for forward
        # Backward movement
        elif keyboard.is_pressed('down'):
            send_command(100, "backward")  # Speed 100 for backward
        # Turn left
        elif keyboard.is_pressed('left'):
            send_command(100, "left")     # Speed 100 for left turn
        # Turn right
        elif keyboard.is_pressed('right'):
            send_command(100, "right")    # Speed 100 for right turn
        # Stop when no keys are pressed
        else:
            stop_car()

        # Check for quit
        if keyboard.is_pressed('q'):
            stop_car()
            print("Stopping program...")
            break

        # Small delay to prevent overwhelming the Arduino
        time.sleep(0.1)

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        stop_car()
        print("Program terminated")