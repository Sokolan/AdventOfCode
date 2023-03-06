#include <iostream>
#include <fstream>
#include <vector>
using namespace std;


//general
void initializeVector(vector<vector<int>>& forest, ifstream& input){
    string line;
    for(int i = 0 ; getline(input, line) ; ++i){
        forest.emplace_back();
        for(int j = 0 ; j < line.length() ; ++j){
            //numbers are in range of 0-9
            forest[i].push_back(line[j] - '0');
        }
    }
}

//part 1
bool checkIfVisible(vector<vector<int>>& forest, int row, int col){
    /*
     * we will check if visible from top, if not if visible from bot,
     * .. left, .. right and only if it's not visible from all directions
     * returns false
     */
    //if it's outer layer return true
    if(row == 0 || row == forest.size() - 1){
        return true;
    }
    if(col == 0 || col == forest[row].size() - 1){
        return true;
    }

    //visible from top
    for(int i = 0 ; i < row ; ++i){
        if(forest[i][col] >= forest[row][col]){
            break;
        }
        if(i == row - 1){
            return true;
        }
    }

    //visible from bot
    for(int i = row + 1 ; i < forest.size() ; ++i){
        if(forest[i][col] >= forest[row][col]){
            break;
        }
        if(i == forest.size() - 1){
            return true;
        }
    }

    //visible from left
    for(int i = 0 ; i < col ; ++i){
        if(forest[row][i] >= forest[row][col]){
            break;
        }
        if(i == col -1){
            return true;
        }
    }

    //visible from right
    for(int i = col + 1 ; i < forest[row].size() ; ++i){
        if(forest[row][i] >= forest[row][col]){
            break;
        }
        if(i == forest[row].size() -1){
            return true;
        }
    }

    //if not visible from all directions return false
    return false;
}

int countVisible(vector<vector<int>>& forest){
    int visible = 0;
    for(int row = 0 ; row < forest.size() ; ++row){
        for(int col = 0 ; col < forest[row].size() ; ++col){
            visible += checkIfVisible(forest, row, col);
        }
    }
    return visible;
}

//part2
int calcScore(vector<vector<int>>& forest, int row, int col){
    //if it's outer layer return 0
    if(row == 0 || row == forest.size() - 1){
        return 0;
    }
    if(col == 0 || col == forest[row].size() - 1){
        return 0;
    }
    int score = 1;
    int tmp_score = 0;
    //visible from top
    for(int i = row - 1 ; i >= 0 ; --i){
        if(forest[i][col] >= forest[row][col]){
            ++tmp_score;
            break;
        }
        ++tmp_score;
    }
    score *= tmp_score;
    tmp_score = 0;

    //visible from bot
    for(int i = row + 1 ; i < forest.size() ; ++i){
        if(forest[i][col] >= forest[row][col]){
            ++tmp_score;
            break;
        }
        ++tmp_score;
    }
    score *= tmp_score;
    tmp_score = 0;

    //visible from left
    for(int i = col - 1 ; i >= 0 ; --i){
        if(forest[row][i] >= forest[row][col]){
            ++tmp_score;
            break;
        }
        ++tmp_score;
    }
    score *= tmp_score;
    tmp_score = 0;

    //visible from right
    for(int i = col + 1 ; i < forest[row].size() ; ++i){
        if(forest[row][i] >= forest[row][col]){
            ++tmp_score;
            break;
        }
        ++tmp_score;
    }
    return (score * tmp_score);
}

int findMaxScore(vector<vector<int>>& forest){
    int max = 0;
    for(int row = 0 ; row < forest.size() ; ++row){
        for(int col = 0 ; col < forest[row].size() ; ++col){
            int tmp = calcScore(forest, row, col);
            if(tmp > max){
                max = tmp;
            }
        }
    }
    return max;
}

int main() {
    ifstream input("test.txt");
    vector<vector<int>> forest;
    initializeVector(forest, input);
    cout << findMaxScore(forest) << endl;
    return 0;
}
