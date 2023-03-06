#include <iostream>
#include <fstream>
#include <vector>
#define VISITED '0'
#define ONE_STEP_COST 1

//for printing function:
#define ROW 41
#define COL 173

using namespace std;
//typedefs
typedef vector<vector<int>> dArr;
typedef pair<int,int> point;

const static point bad_point{-1,-1};

//initializes heightmap to input file data
void initializeHeightMap(dArr& heightmap, ifstream& input_file){
    string line;
    int i = 0;
    while(getline(input_file, line)){
        heightmap.emplace_back();
        for(auto j : line){
            heightmap[i].push_back(j);
        }
        ++i;
    }
}

point findPoint(dArr& heightmap, char p){
    for(int i = 0; i < heightmap.size() ; ++i){
        for(int j = 0 ; j < heightmap[i].size() ; ++j){
            if(heightmap[i][j] == p){
                return point{i,j};
            }
        }
    }
    return point{bad_point};
}

//-1 will represent infinity
void initializeShortestPath(dArr& shortest_distance, unsigned int y, unsigned int x){
    for(int i = 0 ; i < y ; ++i){
        shortest_distance.emplace_back();
        for(int j = 0 ; j < x ; ++j){
            shortest_distance[i].push_back(-1);
        }
    }
}

void checkIfNeighborAndUpdateDistance(dArr& heightmap, dArr& shortest_distance, point p, point neighbor){
    if((heightmap[neighbor.first][neighbor.second]) - heightmap[p.first][p.second]  <= 1 &&
        heightmap[neighbor.first][neighbor.second] != VISITED){
        if(shortest_distance[neighbor.first][neighbor.second] < shortest_distance[p.first][p.second] + ONE_STEP_COST){
            shortest_distance[neighbor.first][neighbor.second] = shortest_distance[p.first][p.second] + ONE_STEP_COST;
        }
    }
}

//check if inside boundaries of cubical arr
bool checkBoundaries(point p, unsigned int boundary_x, unsigned int boundary_y){
    if(p.first < 0 || p.first >= boundary_y){
        return false;
    }
    if(p.second < 0 || p.second >= boundary_x){
        return false;
    }
    return true;
}

void calcNeighborsDistance(dArr& heightmap, dArr& shortest_distance, const point& p){
    int y = p.second;
    int x = p.first;
    unsigned int boundary_y = heightmap.size();
    unsigned int boundary_x = heightmap[0].size();
    //check up
    y -= 1;
    if(checkBoundaries(point(x,y), boundary_x, boundary_y)){
        checkIfNeighborAndUpdateDistance(heightmap, shortest_distance, p, point(x,y));
    }
    //check down
    y += 2;
    if(checkBoundaries(point(x,y), boundary_x, boundary_y)){
        checkIfNeighborAndUpdateDistance(heightmap, shortest_distance, p, point(x,y));
    }
    y -= 1;
    //check left
    x -= 1;
    if(checkBoundaries(point(x,y), boundary_x, boundary_y)){
        checkIfNeighborAndUpdateDistance(heightmap, shortest_distance, p, point(x,y));
    }
    //check right
    x += 2;
    if(checkBoundaries(point(x,y), boundary_x, boundary_y)){
        checkIfNeighborAndUpdateDistance(heightmap, shortest_distance, p, point(x,y));
    }
}

point findMinDistance(dArr& heightmap, dArr& shortest_distance){
    int min = -1;
    point p_min{bad_point};
    for(int i = 0 ; i < heightmap.size() ; ++i){
        for(int j = 0 ; j < heightmap[i].size() ; ++j){
            if(heightmap[i][j] == VISITED) {
                continue;
            }
            if((shortest_distance[i][j] < min || min == -1) && shortest_distance[i][j] != -1){
                min = shortest_distance[i][j];
                p_min = point{i,j};
            }
        }
    }
    return p_min;
}

void printShortest(dArr& shortest_distance){
    for(int i = 0 ; i < ROW ; ++i){
        for(int j = 0 ; j < COL ; ++j){
            cout << (shortest_distance[i][j]) << "    ";
        }
        cout << endl;
    }
    cout << endl;
}

int findShortestPath(dArr& heightmap){
    point start(findPoint(heightmap, 'S'));
    if(start == bad_point){
        cout << "NO START POINT" << endl;
        return -1;
    }
    point end(findPoint(heightmap, 'E'));
    if(end == bad_point){
        cout << "NO END POINT" << endl;
        return -1;
    }
    heightmap[end.first][end.second] = 'z';
    //mark S as visited
    heightmap[start.first][start.second] = 'a';

    //assuming heightmap is cubical
    dArr shortest_distance;
    initializeShortestPath(shortest_distance, heightmap.size(), heightmap[0].size());

    //mark distance from start as 0
    shortest_distance[start.first][start.second] = 0;
    //check neighbors of start point
    calcNeighborsDistance(heightmap, shortest_distance, start);
    heightmap[start.first][start.second] = VISITED;

    for(int i = 1 ; i < heightmap.size()*heightmap[0].size() ; ++i){
        point p = findMinDistance(heightmap, shortest_distance);
        if(p == bad_point){
            break;
        }
        calcNeighborsDistance(heightmap, shortest_distance, p);
        heightmap[p.first][p.second] = VISITED;
    }
//    printShortest(heightmap);
//    printShortest(shortest_distance);
    return shortest_distance[end.first][end.second];
}

void handleFile(string& file_path){
    ifstream input_file(file_path);
    if(!input_file.is_open()){
        cerr << "FILE ERROR" << endl;
        return;
    }
    dArr heightmap;
    initializeHeightMap(heightmap, input_file);
    cout << findShortestPath(heightmap) << endl;

}

int main() {
    string file_path("input.txt");
    handleFile(file_path);
    return 0;
}

