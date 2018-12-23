# Siid

## Table of contents
- [Description](#description)
- [How to use it](#how_to_use_it)
- [Video](#video)

## Description

This is the software that makes Siid alive. Siis is a plant-like robot that goes around to make friends (or enemies sometimes) expressing its emotions. 

It has been devised as a state machine. So, in every moment, the robot is in a particular state and goes in the next one based on the inputs from the sensors. When a transition is fired some actions and animations are perfomed based on the state  where it is. 

The repository is organized in this way:
- [source code](source/Siid) contains files divided by sensors and functions. The main code is the Siid file. 
- [libraries](libraries) contains all the libraries used in the code
- [testing](kinect2_bridge) contains testing code files for the sensors
- [report](reportr) contains the complete report of the project

## How to use it

This software has been devised to be used with an Arduino-like board. It has been written with the Arduino IDE in a C++-like language. You have just to upload it on the board and turn on the robot. To more detailed information about the software, the electrical circuit and the mechanical parts, please refer to the [report](report).

## Video

Here is a demo of the robot: .


