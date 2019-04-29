# comp140 SDL Game Controller Project
## Sim Pancake 2000

![SPlogo](PancakeSim\Sprites\SimPancake_2000.png)

### About
Sim Pancake 2000 is a game created using SDL for a university project.

The game uses a custom controller of 3 frying pans, a jug and whisk, built using the Arduino Uno 
The project use 3 MXU6050's for the frying pans, 3 potentiometers to control the tempture, 3 Light Dependent Resistor (LDR) 
to see if the pan in on the hob.

### The Game Concept
For my Arduino project I have created a pancake cooking/flipping simulator. The player will be in control of 3 frying pans and 3 hobs and a jug. The frying pans will be use to flip the pancakes, the hobs to control the cooking temperature and the jug to pour the mixture.

The aim is to pour the mixture into the frying pans using the jug. The player will then have to cook and flip as many pancakes as they can without burning or even worse setting fire to any. The more velocity the user applies to the pan the higher the pancake will go and cause it to do more flips. When the player runs out of pancake mixture, they will have to make a new one and repeat.

If the player runs out of money and is unable to create a new mixture it will trigger game over or if any catch fire it will be instant game over. The player will earns money by throwing pancakes at the faces that pop up on the left and right of the screen. 

The player also has control of the cooking temperature, using the hobs.

### The Controller Concept
SimPancake consist of frying pans for flipping the pancakes abd a jug for the mix. There is also be hobs to control the cooking temperature and there is a fire alarm for the case of the user setting fire to a pancake.

For the design of the controller there will be a compact cooking top to house the frying pans and jug. On the front of the cooking top will be potentiometers for the nobs to control the cooking temperature. The frying pan will use a accelerometer/gyroscope to detect if the user is flipping the pancake and a light dependent resistor to detect if the frying pan is on the cooking top. I will also use accelerometer/gyroscope to track the movement and pour for the jug. The whisk will also house an accelerometer to detect if the player is whisking. For the fire alarm I will use a siren (with a 1k resistor to prevent it from being deafening)


### Bill Of Materials (BOM)
```
Light Dependent Resistor (LDR)        3 X £0.38 = £ 1.14
MPU                                   3 X £3.30 = £ 9.90 
MUX mutiplex module                   1 X £3.00 = £ 3.00
Rt Angle Tilt Switch                  1 X £0.62 = £ 0.62
9mm Potentiometers                    3 X £1.85 = £ 5.55
Jump Wire                             2 X £5.85 = £11.70
Wood                                  -    -      £15.00
                                      ====================
                                                  £46.21
```                                               




### Credits

##### 3rd Party Assets 

Kids face avatars cute funny cartoon character

Author: 3lian.com 

Acquired from: https://all-free-download.com/free-vector/download/kids-face-avatars-cute-funny-cartoon-characters_289810.html

Licence: Free for non commercial use only
