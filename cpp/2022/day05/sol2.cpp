#include <fstream>
#include <iostream>
#include <string>
#include <list>
#define HEIGHT 8
#define LENGTH 9

using namespace std;

void fillLists(list<char> lists[9], ifstream& input){
	string inputLine;
	for(int i = 0 ; i < HEIGHT ; ++i){
		getline(input, inputLine);
		for(int j = 0 ; j < LENGTH ; ++j){
			if(inputLine[j*4+1] >= 'A' && inputLine[j*4+1] <= 'Z'){
				lists[j].push_back(inputLine[j*4+1]);
			}
		}
	}
} 

void moveCrates(list<char> lists[9], string& input){
	cout << input << endl;
	input.erase(0, 5);
	
	input.erase(input.find("f"), 5);
	input.erase(input.find("t"), 3);

	int numOfMoves = stoi(input.substr(0, input.find(" ")));
	input.erase(0, input.find(" ") + 1);

	int moveFrom = stoi(input.substr(0, input.find(" ")));
	input.erase(0, input.find(" ") + 1);

	int moveTo = stoi(input.substr(0, input.find(" ")));
	
	list<char> tmp;

	for(int i = 0 ; i < numOfMoves ; ++i){
		tmp.push_front(lists[moveFrom - 1].front());
		lists[moveFrom - 1].pop_front();
	}
	
	for(int i = 0 ; i < numOfMoves ; ++i){
		lists[moveTo - 1].push_front(tmp.front());
		tmp.pop_front();
	}
	//cout << "check" << endl;
}

int main(int argc, char* argv[]){
	ifstream input("test.txt");
	list<char> lists[9];
	string inputLine;
	
	fillLists(lists, input);
	//skip next 2 lines as they mean nothing
	getline(input, inputLine);
	getline(input, inputLine);
	
	for(int j = 0 ; j < LENGTH ; ++j){
		for(auto i : lists[j]){
			cout << i << endl;
		}
		cout << endl;
	}
	
	
	//next line will be the moving orders
	while(getline(input, inputLine)){
		moveCrates(lists, inputLine);
		/*for(int j = 0 ; j < LENGTH ; ++j){
		for(auto i : lists[j]){
			cout << i << endl;
		}
		cout << endl;*/
	}
	for(int i = 0 ; i < LENGTH ; ++i){
		cout << lists[i].front();
	}
	cout << endl;
	
	
	
	return 0;
}
