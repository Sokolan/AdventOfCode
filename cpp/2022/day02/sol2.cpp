#include <iostream>
#include <fstream>
#include <string>
#define DRAW 3
#define WIN 6
#define ABC_TO_RES(a) \
	(a-'A')
#define XYZ_TO_RES(a) \
	(a-'X')
#define ABC_TO_XYZ(a) \
	(a-'A'+'X')

using namespace std;

//return match result, -1 if input illegal
int resultCalc(string& input){
	if(input.empty() || input.length() < 3){
		return -1;
	}
	short int playerTwoMove = ABC_TO_RES(input[0]);
	short int playerOneMove = XYZ_TO_RES(input[2]);
	
	//draw
	if(playerOneMove == playerTwoMove){
		return DRAW+(playerOneMove+1);
	}
	
	//win
	if(playerOneMove == ((playerTwoMove + 1) % 3) ){
		return WIN+(playerOneMove+1);
	}
	//if it's not a win or a draw it's a lost round
	return playerOneMove+1;
}

void matchResultToMove(string& input){
	if(input.empty() || input.length() < 3){
		return;
	}
	//X=0 Y=1 W=2; LOSE=0 DRAW=3 WIN=6
	short int matchRes = XYZ_TO_RES(input[2]) * 3;
	short int playerTwoMove = ABC_TO_RES(input[0]);
	
	//draw means make same move as opponent
	if(matchRes == DRAW){	
		input[2] = ABC_TO_XYZ(input[0]);
		return;
	}
	if(matchRes == WIN){
		input[2] = int(ABC_TO_XYZ(input[0]));
		if(playerTwoMove == 2){
			input[2] -= 2;
		}
		else {
			input[2] += 1;
		}
		return;
	}
	
	//if it's not a DRAW or a WIN it's a lose
	input[2] = ABC_TO_XYZ(input[0]);
	if(playerTwoMove == 0){
		input[2] += 2;
	}
	else{
		input[2] -= 1;
	}

}	

int main(int argc, char *argv[]) {
	ifstream input("input_1.txt");
	if(!input.is_open()){
		printf("openning file error");
	}
	int sum = 0;
	string linput;
	while(getline(input, linput)){
		matchResultToMove(linput);
		sum += resultCalc(linput);
		cout << sum << endl;
	}
	cout << sum  << endl;
	input.close();
}
