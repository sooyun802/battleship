## Battleship

* 10X10 grid
* Each player secretly places their own ships
* Players take turns choosing a coordinate to bomb
	* Opponent players tells either "hit" or "miss"
	* When hit, opponent also tells the type of the ship hit
* Battleships
	* Aircraft Carrier: size 6, # of ships 1
	* Battleships: size 4, # of ships 2
	* Submarine: size 3, # of ships 2
	* Destroyer: size 3, # of ships 1
	* Patrol Boat: size 2, # of ships 4

## Battle Opponent: Computer

* The computer positions ships and you bomb them with a given number of bombs
* Randomly initialize battleships on board
	* Coordinates are A ~ J and 1 ~ 10 (e.g., A10, C5)
	* Ships must be placed either horizontally or vertically without overlaps
* Player sets bombing targets and computer tells either "hit" or "miss"
	* Mark a hit with 'X' and a miss with 'O'
		* For a hit, also specify the type of ship
		* e.g., Xp (hit on a patrol boat), Xa (hit on a aircraft carrier)
	* Display the board after every bombing with marks
	* Player will be given *N* bombs
	* Player inputs target coordinates *N* times interactively, reviewing the results
* Showing of final results and score
	* The score equals the sum of the size of ships that have been hit
	* Disclose the board with ships
		* Mark ships with the first character of its type
		* e.g., Aircraft Carrier -> 'A'

## Data Structures

* Board
	* Use `std::map<char, std::vector<ship*>>` for a board
	* Use `std::vector<ship*>` for columns
* Ships are defined with inheritance

## Execution

Program Environment: Ubuntu 14.04 LTS
```
$ g++ -std=c++11 -o battleship main.cpp
$ ./battleship N	// N = number of bombs
```
