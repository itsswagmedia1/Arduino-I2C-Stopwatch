# Wiring Notes - Arduino Stopwatch

This document outlines the pin configurations and hardware mapping for the Arduino Uno Stopwatch project.

## 1. I2C LCD Display Connection
The 16x2 LCD uses an I2C backpack interface (HW-61) to reduce the pin count to just 4 wires.

| LCD Backpack Pin | Arduino Uno Pin | Wire Color (As per photo) | Function |
| :--- | :--- | :--- | :--- |
| **GND** | GND | Brown | Ground Power |
| **VCC** | 5V | Red | 5V Main Power |
| **SDA** | A4 | Orange | Serial Data Line |
| **SCL** | A5 | Yellow | Serial Clock Line |

## 2. Push Buttons Connection
The buttons utilize the internal `INPUT_PULLUP` resistors of the ATmega328P. No external resistors are wired on the PCB.

* **Button 1 (Start / Stop / Continue):** Connected to **Digital Pin 2** and **GND**.
* **Button 2 (Reset):** Connected to **Digital Pin 3** and **GND**.

*Note: When a button is pressed, the input pin state drops from HIGH (5V) to LOW (0V).*