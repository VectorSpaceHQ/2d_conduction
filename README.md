# Overview
This is a real-time solver for 2D transient heat conduction with isothermal boundary conditions in less than 1 Kb of program space. It is intended to be visualized on an LED board with an equivalent number of LEDs in the x and y directory. It was developed by Vector Space as an entry for the 2017, 1Kb Hackaday Challenge.

# Method
Solve for normalized Temp 0-1
convert to color using 3 functions. These are polynomial fits of the coolwarm data

red = -484*T^3 + 207*T^2 + 292*T + 58
green = -76*T^3 - 577*T^2 + 598*T + 68
blue = 612*T^3 - 1345*T^2 + 586*T + 184

# Code Reduction Ideas
* Use __attribute__((OS_main)) on main
* Use interrupt vector location in program memory
* Hand optimise into assembly

