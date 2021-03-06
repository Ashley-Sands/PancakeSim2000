# comp140 SDL Game Controller Project
## Sim Pancake 2000

![SPlogo](https://raw.githubusercontent.com/Ashley-Sands/PancakeSim2000/master/PancakeSim/Sprites/SimPancake_2000.png)

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

### Images
![img0](https://github.com/Ashley-Sands/PancakeSim2000/blob/master/readMeImages/IMG_0.jpg?raw=true)
![img1](https://github.com/Ashley-Sands/PancakeSim2000/blob/master/readMeImages/IMG_1.jpg?raw=true)
![img2](https://github.com/Ashley-Sands/PancakeSim2000/blob/master/readMeImages/IMG_2.jpg?raw=true)

### Bill Of Materials (BOM)
```
Light Dependent Resistor (LDR)        3 X £0.38 = £ 1.14
MPU                                   3 X £3.30 = £ 9.90 
MUX mutiplex module                   1 X £3.00 = £ 3.00
Rt Angle Tilt Switch                  1 X £0.62 = £ 0.62
9mm Potentiometers                    3 X £1.85 = £ 5.55
Jump Wire                             2 X £5.85 = £11.70
Piezo Siren: Bracket Mount            1 X £3.96 = £ 3.96
Wood                                  -    -      £15.00
                                      ====================
                                                  £50.17
```                                               

### User Stores

* As a player i can use a frying pan to flip a pancake
* As a player i can controle the cooking temperature using a potentiometer to help pevent burning all the pancakes
* As a player i can see the pan has been lifted of the hob in the game so that the player knows that the pancake is not cooking
* As a player i want to hear a beep when a pancake has been served so
* As a player i want to hear a fire alarm when the frying pan is on fire
* As a player i want to beable to pour a new pancake using a jug
* As a Player i want to beable to change the pan that im am pouring the mixtur into.
* As a player i can use all 3 frying pans so that the game is more challageing
* As a player i want to see a frying pan rotaing in the game when i rotate the realy frying pan so that i know the direction that pancake is going to go in
* As a player i want to see the jug above the pan so that i know what pan i am pouring into
* As a player i want to see the hob fire get larger when i turn up the heat
* As a player i want to see a fire when the pancake has been cooked to long.


### Credits

##### 3rd Party Assets 

Kids face avatars cute funny cartoon character

Author: 3lian.com 

Acquired from: https://all-free-download.com/free-vector/download/kids-face-avatars-cute-funny-cartoon-characters_289810.html

Licence: Free for non commercial use only

### Other
Arduino Code folder : \Arduino_PancakeSim2000\ps2000\
Game Code folder    : \PancakeSim\

Project GitHub Repo : https://github.com/Ashley-Sands/PancakeSim2000


