# Robot-Car
This repository is a documentation of my embedded systems project working on building a robot car that is remote controlled and battery powered. The project was completed using C programming language and the Freedom KL25Z. 


## Introduction

-  The robotic are is a remotely controlled robot that can be used for different purposes from making toys and delivery of goods. 

## Custom Modules

- The software was developed in modules which have different functions implemented using custom coded modules:
  1. beep.c
     - This have the code that controls the beeping of the buzzers used to give warnings to the users.
  2. ConfigurePorts.c
     - This is the code for configuring the ports as inputs or outputs.
  3. delay.c
     - A custom delay function for the program
  4. flash.c
     - Code for controlling the LED which fashes when the car is moving 
  5. MeasureDist.c
      - Code for the ultrasound distance sensor used to measure the distance of the robot from near objects to avoid collision. 
  6. myglcd.c
      - Code to control a 2x64 lcd used as a display
  7. servo.c
      - Code to control the servo motors
  8. navigation.c
      - code to control the motors which are used to drive the wheel. The controls include forward, left, reverse, right and speed.
  
## Technologies Used:
1. C

    -  Description: C serves as the primary programming language for the development of the robot software and controlling all peripherals such as motors, buzzers, LED etcz

2. MCUXpresso - The IDE to develop the code and upload onto the MCUXpresso
3. FreeRTOS - The operating system for the project


## Project Files:
The project files for this project are included in the following link [Project](https://drive.google.com/drive/folders/1lORV__-OXdxeLa_KFi6gCx-ukyxQfIWt?usp=sharing) These are the files compiled include the FreeRTOS files, board files and all the utilities files which are generated by the IDE. 

## How to Run:
Compile the source file using a code editor specifically the MCUXpresso for the FRDM board. However this code can be implemented on any development board and only need to adjust on pin description and registers to suite that board. 


## Conclusion

- The project concludes with insights into the predictive capabilities of the neural network models and recommendations for leveraging the results to implement targeted customer retention strategies.

## Contributors:
- Tinashe Blackie Kanukai
