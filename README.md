# Wi-Fi Controlled Car with ESP8266

This is my **Wi-Fi controlled car project** built using an **ESP8266 NodeMCU**.  
The car can be controlled from a web interface hosted on the ESP8266, allowing movement in all directions — either with on-screen buttons or a connected game controller.

## 🎥 Demo Video
[https://youtube.com/shorts/4PICd1fZP5o?feature=share](https://youtu.be/a0p9oSavT8Y)

## 📦 Components Used
- ESP8266 NodeMCU
- Motor driver module (L298N / L293D)
- DC motors (x4)
- Wheels & chassis
- Power supply
- Jumper wires

## ⚙️ Pin Connections (Wheel Motors)
| Motor Position  | Forward Pin | Backward Pin |
|-----------------|-------------|--------------|
| Right Front     | D1          | D2           |
| Right Back      | D3          | D4           |
| Left Front      | D5          | D6           |
| Left Back       | D7          | D8           |

## 💡 Features
- Control car via any device connected to its Wi-Fi
- Two control modes:
  - On-screen buttons (web interface)
  - Physical game controller connected to your device
- Forward, backward, left, right, and stop commands
- Real-time command response

## 📚 What I Learned
- Setting up and programming the ESP8266
- Hosting a web server on the ESP8266
- Handling HTTP requests to control hardware
- Interfacing motors using a motor driver
- Basic HTML & CSS for the control UI
- Using JavaScript for real-time input handling
- Project wiring and circuit assembly
- 
## 🛠 How to Run
1. Flash the provided `.ino` file to your ESP8266 using Arduino IDE.
2. Wire the motors and driver as per the pin connections table.
3. Power the ESP8266 and car chassis.
4. Follow the steps in **How It Works** to connect and control.

## 🚀 How It Works
1. **Power on** the car.
2. **Connect** your phone or laptop to the car’s Wi-Fi network:  
   - **SSID:** `ESP`  
   - **Password:** `12345678`  
3. **Open Chrome** (or any browser) and go to:  
      192.168.4.1
4. You can now control the car using:  
- The on-screen directional buttons  
- A connected USB/Bluetooth game controller
## 📬 Contact
[![Discord](https://img.shields.io/badge/Discord-adarsh0910-7289DA?logo=discord&logoColor=white)](https://discordapp.com/users/your_discord_id)

## 📜 License
This project is licensed under the [MIT License](LICENSE) – feel free to use, modify, and share with credit.
