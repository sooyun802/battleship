## Extended Battleship

* The ships are placed according to the input file
* Input file example
	```
	   A B C D E F G H I J 
	   --------------------
	1 |P P   S     B B B B 
	2 |      S             
	3 |      S   D D D P P 
	4 |B B B B             
	5 |                    
	6 |      P P P   S S S 
	7 |          P         
	8 |                    
	9 |                    
	10|        A A A A A A 
	   --------------------
	```
* The computer guesses the bombing coordinates to sink all the player's ships
	* The computer can bomb as much as the given number of bombs
	* If the number of bombs is specified as 0, the computer has unlimited bombs (maximum 100)
* A ship sinks if the computer has hit all the surface coordinates of the ship
* The computer stops bombing when all the ships have sunk
* At the end, the computer reports the score and the number of used bombs
	* score = sum of the size of the ship for each hit

## Computer Intelligence

* The computer gusses the bombing coordinates with the following strategies
	* First, the computer chooses a random coordinate
	* If the computer hits a ship, it bombs neighboring coordinates
	* If the computer hits multiple times horizontally or vertically, it extends coordinates along the direction as long as the size of the target ship

## Execution

Program Environment: Ubuntu 14.04 LTS
```
$ g++ -std=c++11 -o battleship main.cpp
$ ./battleship N	// N = number of bombs
```
