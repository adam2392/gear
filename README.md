# gear
By: Adam Li, Nate Tran, George Levay
### Languages: C, C++, Objective-C, XCode, Swift

# Background
This was developed as the Intel Cornell Cup 2016 competition project from Johns Hopkins University, Game Enabling Augmented Reality (GEAR). The project essentially created a electro-mechanical device that was worn by the feet, analgous to a shoe, that could be programmed to control various parts of the computer keyboard for use in gaming. The design was centered around controlling games that had singular functionality, like wasd keyboard commands.

# Subprojects
The overall project comprised of 3 parts:

## 1. Controller
This repo stores iterations of the microcontroller code used for the design of the GEAR product. It uses a microcontroller to interface with electronices built into the shoe and also with the computer.

## 2. Computer Controller (prototype controlcomputer-backend)
This repo contained code to communicate with the controller and then send commands to the computer to carry out. It was the hub on the side of the computer's software that would need to be run.

## 3. GUI
This would be a gui made in QT that would interface with the computer controller, that would then set various paramters on the controller. This would allow users to enable some sort of feedback into the system, controlling parameters such as sensitivity of the electronics to movement.

# Outcome
We won first place in the Intel Cornell Cup and had a patent on the overall design. 
