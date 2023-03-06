#include <iostream>
#include <fstream>
#include <string>
#include <map>
#define abcABC 52

using namespace std;

void fillArr(short int arr[], string& str, short int num){
	for(int i = 0 ; i < str.length() ; ++i){
		if(str[i] >= 'a' && str[i] <= 'z'){
			if(arr[str[i]-'a'] == num - 1){
				arr[str[i]-'a'] = num;
			}
		}
		else{
			if(arr[str[i]-'A' + 26] == num - 1){
				arr[str[i]-'A' + 26] = num;
			}
		}
	}
}

short int findComm(short int arr[]){
	for(int i = 0 ; i < abcABC ; ++i){
		if(arr[i] == 3){
			//cout << i << endl;
			return i + 1;
		}
	}
	return 0;
}			

void resetArr(short int arr[]){
	for(int i = 0 ; i < abcABC ; ++i){
		arr[i] = 0;
	}
}
		

int main(int argc, char *argv[]){
	ifstream input("test.txt");
	if(!input.is_open()){
		cout << "bad file path" << endl;
		return 0;
	}
	string str;
	int sum = 0;
	short int lineNum = 1;
	short int hist[abcABC] = {0};
	while(getline(input, str)){
		fillArr(hist, str, lineNum);
		if(lineNum % 3 == 0){
			sum += findComm(hist);
			lineNum = 1;
			resetArr(hist);
			continue;
		}
		++lineNum;
	}
	cout << sum << endl;
	return 0;
}
