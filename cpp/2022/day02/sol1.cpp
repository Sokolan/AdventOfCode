#include <iostream>
#include <fstream>
#include <string>
#define DRAW 3
#define WIN 6
#define ABC_TO_RES(a) \
	(a-'A')
#define XYZ_TO_RES(a) \
	(a-'X')

using namespace std;

//return match result, -1 if input illegal
int resultCalc(string& input){
	if(input.empty() || input.length() < 3){
		//cout << input.length() << endl;
		return -1;
	}
	short int playerTwoMove = ABC_TO_RES(input[0]);
	short int playerOneMove = XYZ_TO_RES(input[2]);
	cout << playerOneMove << "  " << playerTwoMove << endl;
	//draw
	if(playerOneMove == playerTwoMove){
		return DRAW+(playerOneMove+1);
	}
	
	//win
	if(playerOneMove == ((playerTwoMove + 1) % 3) ){
		return WIN+(playerOneMove+1);
	}
	//if it's not a win or a draw it's a lost round
	//printf("l %d %d \n", playerOneMove, playerTwoMove);
	return playerOneMove+1;
	cout << input << endl;
}

int main(int argc, char *argv[]) {
	ifstream input("input_1.txt");
	if(!input.is_open()){
		printf("openning file error");
	}
	int sum = 0;
	string linput;
	while(getline(input, linput)){
		sum += resultCalc(linput);
		//cout << resultCalc(linput) << endl;
	}
	cout << sum  << endl;
	input.close();
}
