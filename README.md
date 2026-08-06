# 🚀 STM32 NUCLEO-F446RE HC-SR04 / RCWL-9610 Driver Example

An example of developing a **C/C++ ultrasonic sensor driver** for STM32 using the HAL library.

This project demonstrates how to create a reusable hardware layer for ultrasonic distance sensors, hiding low-level GPIO and Timer Input Capture operations behind a simple C++ class.

## 🎬 Demo

![Ultrasonic Sensor Demo](docs/demo.gif)

## ✨ Features

* 🔧 Object-oriented C++ driver design
* ⚡ STM32 HAL based implementation
* ⏱️ Timer Input Capture for precise echo pulse measurement
* 📏 Distance calculation in centimeters
* 🔌 Separation between application code and sensor driver logic
* 🔄 Reusable driver architecture for ultrasonic sensors

## 🛠️ Hardware

* 🧠 MCU: STM32F446RE
* 🔌 Board: NUCLEO-F446RE
* 📡 Sensor: HC-SR04 

## 📂 Project Structure

```
 Project/
 ├── Drivers/
 │    └── HCSR04/
 │         ├── HCSR04.hpp
 │         └── HCSR04.cpp
 ├── Utils/
 │    ├── Utils.hpp
 │    └── Utils.cpp
```

## ⚙️ Technologies

* C++17
* STM32 HAL
* Timer Input Capture
* GPIO
* UART Debug Output

## 🎯 Purpose

The goal of this project is to demonstrate embedded C++ driver development and show how to build reusable sensor drivers for STM32 microcontrollers.
