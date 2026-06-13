# 🚍 Smart Transit Queue Management System

> An Intelligent Embedded System for Smart Transportation, Queue Automation, and Real-Time Passenger Management

![Arduino](https://img.shields.io/badge/Arduino-UNO-blue)
![Processing](https://img.shields.io/badge/Processing-IDE-orange)
![Embedded Systems](https://img.shields.io/badge/Domain-Embedded%20Systems-green)
![IoT Ready](https://img.shields.io/badge/Future-IoT%20Ready-yellow)
![License](https://img.shields.io/badge/License-MIT-lightgrey)

---

# 📖 Project Overview

The **Smart Transit Queue Management System** is an embedded systems project developed for the **LearnOBots Disruptive Education Exhibition**.

The project automates passenger seat reservation, queue management, gate control, and occupancy monitoring in public transportation systems such as metro buses and shuttle services.

Passengers reserve seats through a keypad interface. The system generates a unique token number, manages passengers using a FIFO queue mechanism, and automatically opens the entry gate when a passenger approaches.

A real-time Processing dashboard displays seat status, passenger count, revenue collection, token information, and bus occupancy statistics.

---

# 🎯 Objectives

- Automate seat reservation process
- Eliminate manual queue management
- Improve passenger boarding efficiency
- Provide real-time transportation analytics
- Demonstrate Embedded Systems concepts
- Integrate Hardware and Software in a complete solution

---

# 🚀 Features

## Smart Seat Reservation

Passengers can reserve available seats using a keypad.

- Available seats displayed on LCD
- Reserved seats cannot be selected again
- Instant confirmation provided

---

## Token Generation

Each passenger receives a unique booking token.

Example:

```text
Seat: 3
Token: A001
```

---

## FIFO Queue Management

The system manages passengers in the order of booking.

```cpp
queueSeat[rear] = seat;
tokenList[rear] = token;
rear++;
```

---

## Automated Entry Gate

The HC-SR04 ultrasonic sensor detects passengers.

When a passenger approaches:

```cpp
if(dist > 0 && dist < 10)
```

The gate opens automatically:

```cpp
gate.write(90);
```

---

## Real-Time Dashboard

The Processing application displays:

- Seat availability
- Passenger count
- Revenue statistics
- Bus status
- Booking events
- Token information

---

## Bus Occupancy Monitoring

The system automatically identifies when the bus reaches maximum capacity.

```cpp
if(passengers >= 4)
```

Status changes to:

```text
BUS FULL
```

---

## Automatic Bus Reset

After the waiting period:

```cpp
resetBus();
```

The next bus becomes available automatically.

---

# 🛠 Hardware Components

| Component | Quantity |
|------------|----------|
| Arduino UNO | 1 |
| LCD I2C 16x2 | 1 |
| HC-SR04 Ultrasonic Sensor | 1 |
| SG90 Servo Motor | 1 |
| 4x4 Matrix Keypad | 1 |
| Buzzer | 1 |
| Red LED | 1 |
| Breadboard | 1 |
| Jumper Wires | Multiple |

---

# 🔌 Circuit Connections

## LCD I2C

| LCD Pin | Arduino |
|----------|----------|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

---

## Keypad

| Keypad | Arduino |
|---------|----------|
| R1 | D2 |
| R2 | D3 |
| R3 | D4 |
| R4 | D5 |
| C1 | D6 |
| C2 | D7 |
| C3 | D8 |
| C4 | D9 |

---

## Servo Motor

| Servo | Arduino |
|---------|----------|
| Signal | D10 |
| VCC | 5V |
| GND | GND |

---

## HC-SR04

| Sensor | Arduino |
|---------|----------|
| Trig | D11 |
| Echo | D12 |
| VCC | 5V |
| GND | GND |

---

## Buzzer

| Buzzer | Arduino |
|---------|----------|
| Positive | A0 |
| Negative | GND |

---

## LED

| LED | Arduino |
|------|----------|
| Positive | A1 |
| Negative | GND through 220Ω resistor |

---

# 🏗 System Architecture

```text
                    +----------------+
                    | Passenger      |
                    +--------+-------+
                             |
                             v
                    +----------------+
                    | Keypad Booking |
                    +--------+-------+
                             |
                             v
                    +----------------+
                    | Token Creation |
                    +--------+-------+
                             |
                             v
                    +----------------+
                    | Queue Manager  |
                    +--------+-------+
                             |
                             v
                    +----------------+
                    | Ultrasonic     |
                    | Detection      |
                    +--------+-------+
                             |
                             v
                    +----------------+
                    | Servo Gate     |
                    +--------+-------+
                             |
                             v
                    +----------------+
                    | Dashboard      |
                    | Monitoring     |
                    +----------------+
```

---

# 📊 Dashboard Features

The Processing dashboard provides:

### Live Seat Monitoring

- Green = Available
- Red = Occupied

### Statistics

- Passengers Entered
- Revenue Collected
- Bus Completed
- Available Seats

### Event Monitoring

- Seat Reserved
- Passenger Entered
- Bus Full
- New Bus Arrived

---

# 💻 Software Stack

| Technology | Purpose |
|------------|----------|
| Arduino IDE | Embedded Programming |
| Processing IDE | Dashboard Development |
| C++ | Arduino Programming |
| Java (Processing) | GUI Dashboard |
| Serial Communication | Data Transfer |

---

# 📂 Repository Structure

```text
Smart-Transit-Queue-Management-System
│
├── Arduino
│   └── SmartTransit.ino
│
├── Processing
│   └── Dashboard.pde
│
├── Documentation
│   └── Project_Report.pdf
│
├── Circuit-Diagram
│   └── circuit_diagram.png
│
├── Images
│   ├── hardware_setup.jpg
│   ├── dashboard.png
│   └── exhibition.jpg
│
├── README.md
│
└── LICENSE
```

---

# ⚙ Working Principle

### Step 1

Passenger selects a seat using keypad.

### Step 2

System verifies seat availability.

### Step 3

Token number is generated.

Example:

```text
A001
A002
A003
```

### Step 4

Passenger joins queue.

### Step 5

Ultrasonic sensor detects passenger.

### Step 6

Servo gate opens automatically.

### Step 7

Passenger count and revenue update.

### Step 8

When bus becomes full:

```text
BUS FULL
```

### Step 9

System waits for next bus.

### Step 10

Automatic reset occurs.

---

# 📈 Algorithms Used

## FIFO Queue Algorithm

```cpp
front++;
rear++;
```

Used for passenger management.

---

## Seat Validation Algorithm

```cpp
if(booked[seat])
```

Prevents duplicate bookings.

---

## Token Generation Algorithm

```cpp
String token = "A00";
token += String(counter++);
```

---

## Distance Measurement

```cpp
distance = duration * 0.034 / 2;
```

Calculates passenger proximity.

---

# 🔬 Learning Outcomes

This project demonstrates:

- Embedded Systems Design
- Sensor Integration
- Human Machine Interfaces
- Real-Time Monitoring
- Queue Management Algorithms
- Automation Systems
- Transportation Technology
- Serial Communication
- Dashboard Development
- System Integration

---

# 🚀 Future Enhancements

## IoT Integration

- ESP32
- WiFi Monitoring
- Cloud Dashboard

## RFID Ticketing

- Smart Card Verification
- Contactless Entry

## Mobile Application

- Online Seat Reservation
- Live Tracking

## AI Analytics

- Passenger Prediction
- Peak-Hour Forecasting

## Robotics Integration

- Autonomous Bus Terminal System
- Smart Transport Automation

## Computer Vision

- Face Recognition
- Passenger Counting
- Security Monitoring

---

# 🎓 Academic Value

This project is suitable for:

- Final Year Projects
- Science Exhibitions
- Robotics Competitions
- Embedded Systems Portfolio
- IoT Portfolio
- MS Computer Science Applications
- Robotics Scholarship Applications
- Research Demonstrations

---

# 👨‍💻 Developer

**Munawar Johar**

Frontend Developer | Embedded Systems Enthusiast | Computer Science Graduate

### Skills

- Embedded Systems
- Arduino Development
- IoT Solutions
- ReactJS
- JavaScript
- Processing IDE
- Automation Systems

---

# 📜 License

This project is released under the MIT License.

Feel free to use, modify, and distribute for educational and research purposes.

---
## How You Can Support:

If you find this project helpful in your learning journey, your support means the world!  Show your appreciation by starring (✨) this repository. 

If you're feeling generous, consider buying me a coffee ☕ to fuel future coding endeavors and keep the caffeine levels up!

[**Buy Me a Coffee**](https://www.buymeacoffee.com/munawarjohar)
