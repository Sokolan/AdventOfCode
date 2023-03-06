#include <iostream>
#include <fstream>
#include <string>
#include <set>
#define T 9
#define H 0

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

char decideDirection(pair<int,int> h_pos, pair<int,int> t_pos){
    if(h_pos.first - t_pos.first == 2){
        return 'R';
    }
    else if(h_pos.first - t_pos.first == -2){
        return 'L';
    }
    else if(h_pos.second - t_pos.second == 2){
        return 'U';
    }
    else if(h_pos.second - t_pos.second == -2){
        return 'D';
    }
    return '\0';
}

void handleMove(pair<int,int>& t_pos, pair<int,int>& h_pos, char direction){
    //if their old distance is 1 and new is 2 move T in same direction
    if(distancePoints(h_pos, t_pos) == 2){
        direction = decideDirection(h_pos, t_pos);
        makeMove(t_pos, direction);
    }

    //otherwise it's a diagonal move
    else{
        if(t_pos.first > h_pos.first){
            makeMove(t_pos, 'L');
        }
        else{
            makeMove(t_pos, 'R');
        }
        if(t_pos.second > h_pos.second){
            makeMove(t_pos, 'D');
        }
        else{
            makeMove(t_pos, 'U');
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

    pair<int, int> pos[10];
    for(auto & i : pos){
        i = pair<int,int>(0,0);
    }

    set<pair<int,int>> tail_visited;
    tail_visited.insert(pos[T]);

    while(getline(input, line)){
        parseInput(line, direction, num_of_moves);
        for(int i = 0 ; i < num_of_moves ; ++i){
            makeMove(pos[H], direction);
            if(!checkIfMoveNeeded(pos[0], pos[1])){
                continue;
            }
            for(int j = 0 ; j < T; ++j){
                if(!checkIfMoveNeeded(pos[j], pos[j + 1])){
                    continue;
                }
                handleMove(pos[j+1], pos[j], direction);
            }
            tail_visited.insert(pos[T]);
        }
    }

    cout << tail_visited.size() << endl;
}

int main() {
    ifstream input("input.txt");
    handleFile(input);

    return 0;
}
