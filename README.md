# Design-E-314
Please see attached report for a detailed discussion about the project.
# Introduction 
The main goal of this project is to act as an arcade style game console with a 8x8 Light Emitting
Diode (LED) Dot Matrix as a screen where two games can be played, namely a maze game and a
tennis game. In the maze game the user can navigate the ball through the maze with the goal of
completing the maze. The aim of the tennis game is to keep bouncing the ball against the back wall
and not let the ball pass the left-most column. The system will be controlled by a STM32F103RB
Microcontroller Unit (MCU), which will take user inputs, do computations etc. and be used to play the
two games. The system should make use of Universal Asynchronous Receiver/Transmitter (UART)
in order to transmit certain message packages that contain information regarding system information
and measurements (for example x and y positions of the ball during a game) to the Test Interface
Connector (TIC) for verification and testing purposes, these UART packages can be seen in table 2.
Input requirements are that a user must be able to control the system with push buttons, Analogto-Digital Converter (ADC) slider and an accelerometer. The system has 4 main states; Menu, Maze
Selection, Maze Game and Tennis Game; and makes use of a finite state machine in order to control
the menu logic for switching between these states. All the requirements and specifications are obtained
from the [1] Project Definition Document (PDD).
This report will include a system diagram with all the components of the system displayed, the various
required hardware elements and how they were setup. This is followed by the software section which
gives a high-level overview of the program, explains the menu control logic, how button debounce was
handled, Inertial Measurement Unit (IMU) interfacing and details which peripherals were used and
how they were setup and initialized.
The report also includes a section on which measurements and tests were done in order to verify that
all the system requirements were met and adhered to as described by the [1] PDD.
Finally the report will contain the findings and conclusions detailing which requirements were met/not
met, identify shortcomings in the design and include some recommendations for future improvements.
In the appendices the complete circuit diagram(see figure 21, appendix A) and pinout for the
STM32F103RB MCU(see table 4, appendix B), along with a photo of the fully built physical project
(see figure 22, appendix C) are included such that any person with some understanding of electrical
circuits can build the circuit themselves.
