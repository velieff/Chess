#include <iostream>
#include <string>
#include "chess.h"

using namespace std;

int main()
{
	Board board;
	string str;
	bool newgame = true;
	cout << "Enter any key to continue" << endl;
	cin >> str;

	while(newgame){
		board.setBoard();
		while (board.playGame());
		cout << "Do you want to play again? (y for yes, anything else for no) ";
		cin >> str;
		if (str != "y")
			newgame = false;
	}
	
	return 0;
}
