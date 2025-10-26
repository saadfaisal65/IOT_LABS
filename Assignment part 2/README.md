# 🧠 Embedded IoT Systems – Assignment 1

**Name:** Saad Faisal  
**Reg No:** 23-NTU-CS-1281  
**Course:** Embedded IoT Systems  
**Instructor:** Sir Nasir Mehmood  
**Date:** 26-Oct-2025  

---

## 🧭 Overview
This repository contains **two ESP32-based IoT projects** created for the *Embedded IoT Systems* course.  
Both were built and verified on the **Wokwi Simulator**, focusing on **hardware control**, **input handling**, and **OLED display integration**.

---

## 🔹 Task 1 – Smart Multi-Device Controller using ESP32

### 📘 Description
This project demonstrates control of multiple components — **LEDs, push buttons, buzzer, and OLED display** — through the ESP32.  
Each button toggles devices and the OLED screen updates live to display the current system state.

### 🧩 Components
- ESP32 DevKitC V4  
- OLED Display 128x64 (I2C)  
- LEDs × 3  
- Push Buttons × 2  
- Buzzer × 1  
- 420Ω Resistors × 3  
- Jumper Wires  

### ⚙️ Pin Mapping

| Component | Label | GPIO Pin |
|------------|--------|-----------|
| LED 1 | D2 | 2 |
| LED 2 | D4 | 4 |
| LED 3 | D5 | 5 |
| Button 1 | D26 | 26 |
| Button 2 | D27 | 27 |
| Buzzer | D15 | 15 |
| OLED SDA | SDA | 21 |
| OLED SCL | SCL | 22 |

### ▶️ Simulation Link
🔗 [View on Wokwi](https://wokwi.com/projects/445847070420105217)

### 📸 Screenshots
![OLED Output](LED_Mode_Controller_with_OLED_and_Buzzer/Screenshots/Task1_output.jpg)  
![Simulation Setup](LED_Mode_Controller_with_OLED_and_Buzzer/Screenshots/Task1_wokwi.png)  
![Hardware Circuit](LED_Mode_Controller_with_OLED_and_Buzzer/Screenshots/Task1_hardware.jpg)

---

## 🔹 Task 2 – Button Press Duration Detection (Short vs Long Press)

### 📘 Description
This project detects **short and long button presses** using the ESP32.  
A **short press** toggles an LED, while a **long press** triggers a buzzer. The OLED screen displays the detected press type.

### 🧩 Components
- ESP32 DevKitC V4  
- OLED Display 128x64 (I2C)  
- LED × 1  
- Push Button × 1  
- Buzzer × 1  
- Resistor × 1  

### ⚙️ Pin Mapping

| Component | Label | GPIO Pin |
|------------|--------|-----------|
| LED | D5 | 5 |
| Button | D25 | 25 |
| Buzzer | D18 | 18 |
| OLED SDA | SDA | 21 |
| OLED SCL | SCL | 22 |

### ▶️ Simulation Link
🔗 [View on Wokwi](https://wokwi.com/projects/445847363242323969)

### 📸 Screenshots
![OLED Output](Task2_Button_Press_Detection/Screenshots/Task2_output.jpg)  
![Simulation Setup](Task2_Button_Press_Detection/Screenshots/Task2_wokwi.png)  
![Hardware Circuit](Task2_Button_Press_Detection/Screenshots/Task2_hardware.jpg)

---

## ⚙️ Features
✅ Real-time OLED display feedback  
✅ Button-based LED and buzzer control  
✅ Detection of both short and long press durations  
✅ Fully simulated on **Wokwi IoT Simulator**  

---

## 🎯 Learning Outcomes
- Interfaced ESP32 with **I2C-based OLED**  
- Implemented **GPIO handling and debounce logic**  
- Detected button press duration using **millis()**  
- Strengthened understanding of **embedded hardware integration**

---

### 📁 Repository Structure

---

### 🧠 Author
**Saad Faisal**  
📧 [saadfaisal065@gmail.com](mailto:saadfaisal065@gmail.com)  
💻 *Computer Science Student – NTU Faisalabad*  

---

⭐ *If you found this project helpful, consider starring the repository!*
