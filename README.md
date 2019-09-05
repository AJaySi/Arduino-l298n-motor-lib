# Arduino-l298n-motor-lib

Arduino and L298N DC motor controller

L298N is used to control DC motors with arduino. 
The L298N is a dual H-Bridge motor driver which controls speed and direction of 
two DC motors (5 and 35V, with a peak current up to 2A) at the same time. 

This is done by controlling the amount of input voltage, proportional to speed desired.
L298 Motor driver IC and can drive different inductive loads like DC Motors, Stepper Motors, Relay, etc

* Features of L298N
1. It can control 2 DC motor's speed and direction.
1. Very accessible, inexpensive and well documented module.
1. Controls any motor operating in 5-35V and upto 2A ratings.
1. With 25W rated power, the L298N can handle up to 3 amperes at 35 Volts DC.
1. Onboard 5V regulator can power the motors.
1. Drive different inductive loads like DC Motors, Stepper Motors, Relay, etc.
1. L298N Motor Driver IC is a dual(2 motors) full bridge driver IC. 
1. *The voltage drop of the L298N motor driver is about 2V. Thus, a 12V DC motor will spin below its maximum speed.*

---------------
## 1). PWM based Speed control of DC motor

PWM, or pulse width modulation technique allows to adjust the voltage value going to the electronic device,
by turning power on and off, at a fast rate. 

The average voltage is proportional to the width of the pulses known as Duty Cycle.
Duty Cycle of a PWM Signal is the ratio of the ON/HIGH time duration to the total time of the signal.
Thus, L298N controls the speed of an DC motor with varying voltage(PWM) over a period of time.

---------------
## 2). H-bridge DC motor control

For controlling the motor rotation direction, the current to motor is inversed.
This process is achived by using a H-bridge circuit.

The L298N is a dual H-Bridge motor driver which controls speed and direction of 
two DC motors (5 and 35V, with a peak current up to 2A) at the same time. 

---------------

## Connection Arduino and L298N

Connection : https://www.youtube.com/watch?v=OkHR1BZCcqA
Power supply: Use a jumper for 5v regulator, when the supply voltage is upto 12V.
Remove the jumper, if motors require more than 12V supply.

Logic Control inputs: Enable A and Enable B (ENA/ENB) are used to control the motor speed.
Note: If a jumper is placed on Enable A/B, then motor runs at full speed with no PWM.

Input 1 and Input 2 (IN1 & IN2) pins control the motor rotation direction for motor A, and the inputs 3 and 4 (IN3 & IN4) for the motor B. 
Using these pins we actually control the switches of the H-Bridge inside the L298N IC. 

| IN1  | IN2  | RESULT   |
--------------------------
| LOW  | LOW  | STOP     |
--------------------------
| HIGH | HIGH | STOP     |
--------------------------
| LOW  | HIGH | FORWARD  |
--------------------------
| HIGH | LOW  | BACKWARD |
--------------------------

* The same applies for the inputs 3 and 4 and the motor B.
* Keeping the jumper on ENA/ENB pins implies that these pins will be HIGH.
* Motor enable pins must connect to PWM enabled pin. Ex: Pin 10 and 5, are PWM pins.
(PWM pins are denoted by the tilde ("~") next to the pin number)

----------------

## Referances:
https://tronixlabs.com.au/news/tutorial-l298n-dual-motor-controller-module-2a-and-arduino/
https://dronebotworkshop.com/dc-motors-l298n-h-bridge/
https://github.com/AndreaLombardo/L298N
http://www.handsontec.com/dataspecs/L298N%20Motor%20Driver.pdf

