# Microprocessors for Automation and Robotics

This repository contains six different C projects developed for the PIC16F886 microprocessor. The first four projects were implemented and tested successfully on a little mobile robot which had the PIC embedded. The last two projects are designed specifically for the SimulIDE simulator. Each project focuses on specific functionalities and features of the microcontroller and the robot. Below, you'll find a brief description of each project.

## 1. ADC_L4 - Analog-to-Digital Conversion (ADC) and Proximity Sensing

Project `ADC_L4` revolves around reading data from a proximity sensor and converting the analog signal to a 10-bit digital value. The digital value is then used to calculate the distance in millimeters from the robot to the detected object. The ability to sense proximity is crucial for various autonomous activities and obstacle avoidance.



https://github.com/mateusbsal4/microprocessors/assets/84996618/821625d4-fb8a-42df-9a42-bf39cf93871b



## 2. Serial_L5 - Serial Communication and LCD Display

In `Serial_L5`, the focus is on serial communication between the robot and another device (another robot, in this case). Characters are sent via a serial channel, and the received characters are displayed on the robot's LCD screen. This communication capability enables the robots to exchange information and coordinate their actions in various cooperative scenarios.


## 3. PWM_L6 - Encoders and Pulse Width Modulation (PWM)

`PWM_L6` project involves configuring the PIC16F886 microcontroller in PWM mode to control the motors connected to the robot's two wheels. Additionally, encoders are used to measure the velocity of each wheel anc check if they are compatible with the duty cycle set. A state machine is implemented and stored in the PIC's EEPROM memory.



https://github.com/mateusbsal4/microprocessors/assets/84996618/9623d8ca-0ab5-41f7-90ce-1a9a5ffb041e




## 4. L7 - Line Following and Proximity-based Interaction

Project `L7` focuses on implementing an autonomous line-following behavior for the robot. The robot is designed to follow a line on the ground, and its LED color changes according to its movement. For example, different colors may be displayed when the robot moves forward or turns. The proximity sensor data is utilized to detect the presence of other robots in close proximity, leading to stoppage or reactive behaviors in crowded environments.

https://github.com/mateusbsal4/microprocessors/assets/84996618/e42b346c-6f70-4a63-92f0-f439bccb12e9


## 5. Stepper_ex - Stepper Motor Control in Half Step Mode

In the `Stepper_ex` project, the task is to create a function to move a stepper motor in half step mode using the PIC16F886. The function takes arguments for the number of steps and the step time. Implementing stepper motor control allows precise positioning and movement, which is useful in various applications like robotics and automation.


## 6. display_project - Analog Read Display on Multiplexed 7-Segment Display

The `display_project` demonstrates how to display the analog read of a potentiometer on a multiplexed four-digit 7-segment display using the PIC16F886 and four MOSFETs. This project showcases how to interface and visualize analog data on a common output device like the 7-segment display.


## Project Folder Structure

The repository is organized into eight folders, each representing a specific project:

- `ADC_L4/`: Contains the code and resources for the ADC and proximity sensing project.
- `Serial_L5/`: Holds the code and resources for the serial communication and LCD display project.
- `PWM_L6/`: Includes the code and resources for the PWM motor control and velocity measurement project.
- `L7/`: Encompasses the code and resources for the autonomous line-following and proximity-based interaction project.
- `Stepper_ex/`: Contains the code and resources for the stepper motor control project.
- `display_project/`: Holds the code and resources for the analog read display on the 7-segment display project.
