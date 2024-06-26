# Load-Management

This project involves managing loads based on the battery's state of charge (SOC). 
Depending on the state of charge (%SOC) of the battery, certain loads will be
switched off until the battery reaches a predetermined SOC level (30%), after which
all loads will be turned off and the system will shut down.

## Circuit Components
- Arduino Uno R3 with ATmega328p
- 16x2 Alphanumeric LCD Display
- LCD I2C Serial Interface Adapter Module
- 8 Channel 5V Relay Module with Optocoupler
- 20A Range Current Sensor Module ACS712
- LEDs (Green, Red, Blue) (8)
- Resistance (1k ohm) (8)
- Jumper Wires(male to female, male to male, female to female)
- Breadboard (2)
- 3.7 V Lithium Ion battery

## Schematic Diagram
![proteus_ckt](https://github.com/shreya71/Load-Management/assets/91543981/ff7f8640-46f1-4dfb-82a7-2a680a5866e3)
