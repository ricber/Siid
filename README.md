# Siid

## Authors

- Riccardo Bertoglio, Computer Science & Engineering
- Sarah Duval Dachary, Design & Engineering
- Federico Espositi, Automation & Control Engineering
- Marzia Degiorgi, Computer Science & Engineering
- Fabio Spiga Casadio, Product Design
- Martina Lauricella, Automation & Control Engineering
University: Politencico di Milano

## Table of contents
- [Description](#description)
- [How to use it](#how-to-use-it)
- [Video](#video)

## Description

This is the software that makes Siid alive. Siid is a plant-like robot that goes around to make friends (or enemies sometimes) expressing its emotions. 

It has been devised as a state machine. So, in every moment, the robot is in a particular state and goes in the next one based on the inputs from the sensors. When a transition is fired some actions and animations are perfomed depending on the current state. 

The repository is organized in this way:
- [source](source/Siid) contains files divided by sensors and functions. The main code is in the Siid file
- [libraries](libraries) contains all the libraries used in the code
- [testing](testing) contains testing code files for the sensors
- [report](documentation/report.pdf) contains the complete report of the project

## How to use it

This software has been devised to be used with an Arduino-like board. It has been written with the Arduino IDE in a C++-like language. You have just to upload it on the board and turn on the robot. To more detailed information about the software, the electrical circuit and the mechanical parts, please refer to the [report](documentation/report.pdf).

## Video

Here is a demo of the robot: https://youtu.be/yTxBfgGPwvU.


