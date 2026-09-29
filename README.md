# CAN_using_car-dashboard
Designed and implemented a CAN-based car dashboard system using PIC18F4580 microcontrollers, enabling communication between ECUs to monitor and display vehicle parameters such as speed, RPM, and gear position in real time.

This project demonstrates a CAN (Controller Area Network)-based car dashboard system using PIC18F4580 microcontrollers. It enables communication between multiple Electronic Control Units (ECUs) to collect vehicle parameters and display them on a dashboard.

Features

CAN communication between multiple ECUs. Speed and RPM simulation using a potentiometer and ADC. Gear position selection using a digital keypad switch. Real-time vehicle parameter display on a Character LCD (CLCD). Turn indicator control using LEDs. Modular ECU-based architecture.

Hardware and Technologies

Microcontroller: PIC18F4580 Programming Language: Embedded C IDE: MPLAB X IDE Compiler: MPLAB XC8 Communication Protocol: CAN Peripherals: ADC, GPIO, CLCD, Digital Keypad, LEDs

Working Principle

ECU 1 – Speed and Indicator Control Simulates vehicle speed using a potentiometer and ADC. Reads the turn indicator selection using a digital switch. Transmits speed and indicator information through CAN messages.

ECU 2 – RPM and Gear Position Control Simulates engine RPM using a potentiometer and ADC. Reads gear position using a digital switch. Transmits RPM and gear position information through CAN messages.

ECU 3 – Dashboard Display Unit Receives vehicle data from ECU 1 and ECU 2 through CAN communication. Displays speed, RPM, and gear position on a Character LCD (CLCD). Controls turn indicator LEDs based on the received indicator status.
