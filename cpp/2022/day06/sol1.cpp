#include <fstream>
#include <iostream>
#include <string>
#define abc 'z'-'a'+1
#define MARKERNUM 13

using namespace std;

int main(int argc, char* argv[]){
	char buff;
	
	ifstream input("test.txt");
	if(!input.is_open()){
		cerr << "failed to open file" << endl;
		return -1;
	}
	
	string lastThree;
	short int skipNeed = 0;
	int loc = 1;
	for(int i = 0 ; i < MARKERNUM ; ++i){
		input.get(buff);
		int dupLoc = lastThree.find_last_of(buff);
		if(dupLoc != string::npos){
			skipNeed = dupLoc + 1;
		}
		lastThree += buff;
		++loc;
	}
	while(input.get(buff)){
		int dupLoc = lastThree.find_last_of(buff);
		if(dupLoc != string::npos){
			if(skipNeed < dupLoc + 1){
				skipNeed = dupLoc + 1;
			}
		}
		if(skipNeed == 0){
			cout << loc << endl;
			break;
		}
		
		++loc;
		lastThree += buff;
		lastThree = lastThree.substr(1);
		--skipNeed;
	}
	
	
		
	
	return 0;
}
