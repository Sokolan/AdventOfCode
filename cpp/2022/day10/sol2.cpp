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

void handleNewCycleCRT(const int cycle, unsigned int& CRT_pos, int x){
    static string out;
    if(cycle % 40 == 0){
        cout << out << endl;
        out.clear();
        CRT_pos = 1;
    }

    if(CRT_pos <= (x + 2) && CRT_pos >= x){
        out += '#';
    }
    else{
        out += '.';
    }
    ++CRT_pos;
}

void handleFile(string& file_name){
    ifstream input(file_name);
    if(!input.is_open()){
        cerr << "bad_file_descriptor" << endl;
    }

    string line;
    int cycle = 0;
    int x = 1;
    unsigned int CRT_pos = 1;
    string output;
    while(getline(input, line)){
        handleNewCycleCRT(cycle, CRT_pos, x);
        ++cycle;

        if(line == "noop"){
            continue;
        }
        //if it's not noop it's addx
        line = line.substr(line.find(' ') + 1);
        int addx = stoi(line);
        handleNewCycleCRT(cycle, CRT_pos, x);
        ++cycle;

        x += addx;
    }
    handleNewCycleCRT(cycle, CRT_pos, x);

}

int main() {
    string file_name = "input.txt";
    handleFile(file_name);
    return 0;
}
