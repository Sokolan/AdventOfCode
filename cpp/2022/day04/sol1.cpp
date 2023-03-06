#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void splitInputIntoTwo(string& elf1, string& elf2, string& input){
	size_t comma = input.find(',');
	elf1 = input.substr(0, comma);
	elf2 = input.substr(comma + 1);
}

void splitRangeToInts(string& range, int& start, int& end){
	//cout << range << endl << range.substr(0, range.find('-')) << endl << range.substr(range.find('-') + 1) << endl; 
	start = stoi(range.substr(0, range.find('-')));
	end = stoi(range.substr(range.find('-') + 1));
}

int main(int argc, char* argv[]){
	ifstream input("test.txt");
	if(!input.is_open()){
		cerr << "file open error" << endl;
	}
	string inputLine;
	
	string elf1;
	string elf2;
	int sum = 0;
	
	while(getline(input, inputLine)){
		splitInputIntoTwo(elf1, elf2, inputLine);
		int elf1Start, elf1End, elf2Start, elf2End;
		splitRangeToInts(elf1, elf1Start, elf1End);
		splitRangeToInts(elf2, elf2Start, elf2End);
		
		if((elf1Start <= elf2Start && elf2End <= elf1End) ||
			(elf2Start <= elf1Start && elf1End <= elf2End)){ 
			cout << "elf 1: " << elf1Start << "  " << elf1End << "  ";
			cout << "elf 2: " << elf2Start << "  " << elf2End << endl;
			++sum;
		}
	}
	cout << sum << endl;

	return 0;
}
