#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;
static bool diag = false;

void makeMove(pair<int,int>& pos, char direction){
    if(direction == 'U'){
        ++pos.second;
    }
    else if(direction == 'D'){
        --pos.second;
    }
    else if(direction == 'R'){
        ++pos.first;
    }
    else if(direction == 'L'){
        --pos.first;
    }

}

int distancePoints(pair<int,int> a, pair<int,int> b){
    return abs(a.first - b.first) + abs(a.second - b.second);
}

bool checkIfMoveNeeded(pair<int,int>& h_pos, pair<int,int>& t_pos){
    //if H is on T, or H is moving on T just make the move
    //or H makes a move to create diagonal, just move H
    //or new distance is 1  just move H
    if(t_pos == h_pos ||
        abs(h_pos.first - t_pos.first) == 1 && abs(h_pos.second - t_pos.second) == 1 ||
        abs(h_pos.first - t_pos.first) + abs(h_pos.second - t_pos.second) == 1){
        return false;
    }
    return true;
}

void handleMove(pair<int,int>& t_pos, pair<int,int>& h_pos, char direction){

    if(!checkIfMoveNeeded(h_pos, t_pos)){
        return;
    }
    //if their old distance is 1 and new is 2 move T in same direction
    else if(distancePoints(h_pos, t_pos) == 2){
        makeMove(t_pos, direction);
    }

    //otherwise it's a diagonal move
    else if(distancePoints(h_pos, t_pos) == 3){
        makeMove(t_pos, direction);
        if(direction == 'U' || direction == 'D'){
            if(h_pos.first - t_pos.first > 0){
                makeMove(t_pos, 'R');
            }
            else{
                makeMove(t_pos, 'L');
            }
        }
        else{
            if(h_pos.second - t_pos.second > 0){
                makeMove(t_pos, 'U');
            }
            else{
                makeMove(t_pos, 'D');
            }
        }
    }
}

void parseInput(const string& input, char& direction, int& num_of_moves){
    direction = input[0];
    num_of_moves = stoi(input.substr(input.find(' ') + 1));
}

void handleFile(ifstream& input){
    string line;
    int num_of_moves;
    char direction;

    pair<int, int> t_pos, h_pos;
    t_pos = h_pos = pair<int,int>(0,0);

    set<pair<int,int>> tail_visited;
    tail_visited.insert(t_pos);

    while(getline(input, line)){
        parseInput(line, direction, num_of_moves);
        for(int i = 0 ; i < num_of_moves ; ++i){
            makeMove(h_pos, direction);
            handleMove(t_pos, h_pos, direction);
            tail_visited.insert(t_pos);
        }
    }

    cout << tail_visited.size() << endl;
}

int main() {
    ifstream input("input.txt");
    handleFile(input);

    return 0;
}
