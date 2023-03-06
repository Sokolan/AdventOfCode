#include <iostream>
#include <fstream>
#include <string>
#include <map>


using namespace std;

string splitToHalf(string& input){
	if(input.length() % 2 != 0){
		return "";
	}
	string output = input.substr((input.length() / 2), input.length());
	return output;
}

void mapInitialize(map<char,short int>& botHalfMap, string& botHalf){
	for(int i = 0 ; i < botHalf.length() ; ++i){
		if(botHalf[i] >= 'a' && botHalf[i] <= 'z'){
			botHalfMap.insert(pair<char, short int>(botHalf[i], (botHalf[i] - 'a' + 1)));
		}
		else{
			botHalfMap.insert(pair<char, short int>(botHalf[i], (botHalf[i] - 'A' + 27)));
		}
	}
}

int calculatePrio(map<char,short int>& topHalfMap, string& topHalf){
	int prioSum = 0;
	for(int i = 0 ; i < topHalf.length() ; ++i){
		map<char, short int>::iterator it = topHalfMap.find(topHalf[i]);
		if(it != topHalfMap.end()){
			prioSum += it->second;
			topHalfMap.erase(it);
			//cout << it->first << " " << it->second << endl;
		}
	}
	return prioSum;
}

int main(int argc, char *argv[]){
	ifstream input("test.txt");
	if(!input.is_open()){
		cout << "bad file path" << endl;
		return 0;
	}
	string str_bot;
	int sum = 0;
	while(getline(input, str_bot)){
		string str_top = splitToHalf(str_bot);
		str_bot.resize(str_bot.length() / 2);
		//cout << str_bot << endl << str_top << endl;
		map<char, short int> botHalfMap;
		mapInitialize(botHalfMap, str_bot);
		sum += calculatePrio(botHalfMap, str_top);
	}
	cout << sum << endl;
	return 0;
}
