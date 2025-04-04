from flask import Flask, request, jsonify, render_template
import requests

app = Flask(__name__, template_folder='/home/ubuntu/coding/OT-IoT-Lab/templates')

# ESP8266 base URL (replace with your ESP8266's IP address)
ESP8266_URL = "http://192.168.1.112"  # Update this with your ESP8266's IP

def control_car(command):
    """Send command to ESP8266 to control the RC car"""
    try:
        # Map commands to ESP8266 parameters
        speed = 100 if command != "stop" else 0
        direction = command
        
        # Send HTTP GET request to ESP8266
        url = f"{ESP8266_URL}/set?in1={speed}&in2={direction}&in3=0&in4=0"
        print("sending ["+direction+"]")
        response = requests.get(url, timeout=2)
        if response.status_code == 200:
            print(f"Executing command: {command}")
            return {"status": "success", "command": command}
        else:
            print(f"Failed to send command: {command}, Status: {response.status_code}")
            return {"status": "error", "message": "ESP8266 communication failed"}
            
    except requests.exceptions.RequestException as e:
        print(f"Error sending command to ESP8266: {e}")
        return {"status": "error", "message": str(e)}

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/control', methods=['POST'])
def control():
    data = request.get_json()
    if 'command' not in data:
        return jsonify({"error": "No command provided"}), 400
    
    command = data['command'].lower()
    allowed_commands = ['forward', 'backward', 'left', 'right', 'stop']
    
    if command not in allowed_commands:
        return jsonify({"error": "Invalid command"}), 400
    
    response = control_car(command)
    return jsonify(response)

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=7444, debug=True)