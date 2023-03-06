#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isInterestingCycle(int cycle){
    if(cycle == 20 || abs(cycle - 20) % 40 == 0){
        return true;
    }
    return false;
}



void handleFile(string& file_name){
    ifstream input(file_name);
    if(!input.is_open()){
        cerr << "bad_file_descriptor" << endl;
    }
    string line;
    int cycle = 0;
    int signal_strength_sum = 0;
    int x = 1;
    while(getline(input, line)){
        ++cycle;
        if(isInterestingCycle(cycle)){
            cout << cycle * x << endl;
            signal_strength_sum += cycle * x;
        }
        if(line == "noop"){
            continue;
        }
        //if it's not noop it's addx

        line = line.substr(line.find(' ') + 1);
        int addx = stoi(line);
        ++cycle;
        if(isInterestingCycle(cycle)){
            cout << cycle * x << endl;

            signal_strength_sum += cycle * x;
        }
        x += addx;
    }
    cout << signal_strength_sum;
}

int main() {
    string file_name = "input.txt";
    handleFile(file_name);
    return 0;
}

