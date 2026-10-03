# Rocket Ascent Simulator (RAS)

A series of classes, heavily inspired to the Python 
library rocketPy, that allow a simple rocket launch
simulation. 

It contains classes for the rocket itself, the motor,
the environment, and a series of data handling classes
mostly meant to read drag and thrust curves from 
various file types or inputs methods.



> **Note:** Developed as a personal project to learn C++
> and basic OOP principles (start of development 28/09/26,
> currently WIP)

---

## Features

* **ISA Model:** a simple class that can derive pressure, 
temperature, density and sound speed at any altitude within
the bounds defined by the International Standard Atmosphere 
model
* **Data Interpolation:** DataCurve, a class built to parse 
.csv files similarly to the drag curve files in RocketPy, 
with linear interpolation and configurable behavior for out 
of bounds values