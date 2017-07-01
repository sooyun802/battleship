#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class ship {
public:
	string type;
	int size;
	bool hit;
};

class AircraftCarrier : public ship {
public:
	AircraftCarrier();
};
AircraftCarrier::AircraftCarrier() {
	size=6;
	type="carrier";
	hit=false;
}

class Battleship : public ship {
public:
	Battleship();
};
Battleship::Battleship() {
	size=4;
	type="battlehip";
	hit=false;
}

class Submarine : public ship {
public:
	Submarine();
};
Submarine::Submarine() {
	size=3;
	type="submarine";
	hit=false;
}

class Destroyer : public ship {
public:
	Destroyer();
};
Destroyer::Destroyer() {
	size=3;
	type="destroyer";
	hit=false;
}

class PatrolBoat : public ship {
public:
	PatrolBoat();
};
PatrolBoat::PatrolBoat() {
	size=2;
	type="patrol";
	hit=false;
}

class Empty : public ship {
public:
	Empty();
};
Empty::Empty() {
	size=0;
	type="void";
	hit=false;
}

class Game {
private:
	map<char, vector<ship*>> board;
	int score;
public:
	Game();
	~Game();
	void addShip(int direction, int type);
	ship *get_ship(int row, int col);
	void bomb(char x, int y);
	void play_game(int bomb_num);
	void show_hits();
	void show_result();
};
Game::Game() {
	srand(time(NULL));
	score=0;
	ship *fill;
	for(int i=0;i<10;i++) {
		vector<ship*> tmp;
		for(int j=0;j<10;j++) {
			fill=new Empty();
			tmp.push_back(fill);
		}
		board['A'+i]=tmp;
	}
	int direction=rand()%2;
	addShip(direction, 0);
	for(int i=0;i<2;i++) {
		direction=rand()%2;
		addShip(direction, 1);
	}
	for(int i=0;i<2;i++) {
		direction=rand()%2;
		addShip(direction, 2);
	}
	direction=rand()%2;
	addShip(direction, 3);
	for(int i=0;i<4;i++) {
		direction=rand()%2;
		addShip(direction, 4);
	}
}
Game::~Game() {
	for(int i=0;i<10;i++) {
		for(int j=0;j<10;j++) {
			delete board.find(i+'A')->second.at(j);
		}
	}
}
void Game::addShip(int direction, int type) {
	char row;
	int col, ch=0;
	ship *add;
	switch(type) {
		case 0:
			add=new AircraftCarrier();
			break;
		case 1:
			add=new Battleship();
			break;
		case 2:
			add=new Submarine();
			break;
		case 3:
			add=new Destroyer();
			break;
		case 4:
			add=new PatrolBoat();
			break;
	}
	switch(direction) {
		case 0:
			row=rand()%(11-add->size)+'A';
			col=rand()%10;
			while(1) {
				for(int i=0;i<add->size;i++) {
					if(board.find(row+i)->second.at(col)->type!="void") {
						ch=-1;
						break;
					}
					else ch=0;
				}
				if(ch==-1) {
					row=rand()%(11-add->size)+'A';
					col=rand()%10;
				}
				else break;
			}
			delete board.find(row)->second.at(col);
			board.find(row)->second.at(col)=NULL;
			board.find(row)->second.at(col)=add;
			for(int i=1;i<add->size;i++) {
				switch(type) {
					case 0:
						add=new AircraftCarrier();
						break;
					case 1:
						add=new Battleship();
						break;
					case 2:
						add=new Submarine();
						break;
					case 3:
						add=new Destroyer();
						break;
					case 4:
						add=new PatrolBoat();
						break;
				}
				delete board.find(row+i)->second.at(col);
				board.find(row+i)->second.at(col)=NULL;
				board.find(row+i)->second.at(col)=add;
			}
			break;
		case 1:
			row=rand()%10+'A';
			col=rand()%(11-add->size);
			while(1) {
				for(int i=0;i<add->size;i++) {
					if(board.find(row)->second.at(col+i)->type!="void") {
						ch=-1;
						break;
					}
					else ch=0;
				}
				if(ch==-1) {
					row=rand()%10+'A';
					col=rand()%(11-add->size);
				}
				else break;
			}
			delete board.find(row)->second.at(col);
			board.find(row)->second.at(col)=NULL;
			board.find(row)->second.at(col)=add;
			for(int i=1;i<add->size;i++) {
				switch(type) {
					case 0:
						add=new AircraftCarrier();
						break;
					case 1:
						add=new Battleship();
						break;
					case 2:
						add=new Submarine();
						break;
					case 3:
						add=new Destroyer();
						break;
					case 4:
						add=new PatrolBoat();
						break;
				}
				delete board.find(row)->second.at(col+i);
				board.find(row)->second.at(col+i)=NULL;
				board.find(row)->second.at(col+i)=add;
			}
			break;
	}
}
ship *Game::get_ship(int row, int col) {
	return board.find(row+'A')->second.at(col);
}
void Game::bomb(char x, int y) {
	if(board.find(x)->second.at(y-1)->hit==true) {
		cout << "You've already hit here!" << endl;
		return;
	}
	if(board.find(x)->second.at(y-1)->type!="void") cout << "hit" << endl;
	else cout << "miss" << endl;
	if(board.find(x)->second.at(y-1)->hit==false) score+=board.find(x)->second.at(y-1)->size;
	board.find(x)->second.at(y-1)->hit=true;
	show_result();
}
void Game::play_game(int bomb_num) {
	char row;
	int col;
	for(int i=0;i<bomb_num;i++) {
		cin >> row >> col;
		if((row>='A' && row<='J') && (col>=1 && col<=10)) bomb(row, col);
		else cout << "WRONG INPUT" << endl;
		cout << endl;
	}
}
void Game::show_hits() {
	cout << "   A B C D E F G H I J" << endl << "   -------------------" << endl;
	for(int i=0;i<10;i++) {
		if(i!=9) cout << i+1 << " |";
		else cout << i+1 << "|";
		for(int j=0;j<10;j++) {
			if(board.find(j+'A')->second.at(i)->hit==true) cout << "X ";
			else cout << "  ";
		}	cout << endl;
	}
	cout << "   -------------------" << endl;
}
void Game::show_result() {
	cout << "   A B C D E F G H I J" << endl << "   -------------------" << endl;
	for(int i=0;i<10;i++) {
		if(i!=9) cout << i+1 << " |";
		else cout << i+1 << "|";
		for(int j=0;j<10;j++) {
			if(board.find(j+'A')->second.at(i)->hit==true) {
				if(board.find(j+'A')->second.at(i)->type=="void") cout << "O ";
				else if(board.find(j+'A')->second.at(i)->type=="carrier") cout << "Xa";
				else if(board.find(j+'A')->second.at(i)->type=="battlehip") cout << "Xb";
				else if(board.find(j+'A')->second.at(i)->type=="submarine") cout << "Xs";
				else if(board.find(j+'A')->second.at(i)->type=="destroyer") cout << "Xd";
				else if(board.find(j+'A')->second.at(i)->type=="patrol") cout << "Xp";
			}
			else {
				if(board.find(j+'A')->second.at(i)->type=="void") cout << "  ";
				else if(board.find(j+'A')->second.at(i)->type=="carrier") cout << "A ";
				else if(board.find(j+'A')->second.at(i)->type=="battlehip") cout << "B ";
				else if(board.find(j+'A')->second.at(i)->type=="submarine") cout << "S ";
				else if(board.find(j+'A')->second.at(i)->type=="destroyer") cout << "D ";
				else if(board.find(j+'A')->second.at(i)->type=="patrol") cout << "P ";
			}
		}	cout << endl;
	}
	cout << "   -------------------" << endl;
	cout << "Score = " << score << endl;
}

int main(int argc, char** argv) {
	int bomb_num, score=0;
	bomb_num=atoi(argv[1]);
	Game *game=new Game();
	game->play_game(bomb_num);
	delete game;
}