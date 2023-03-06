#include <iostream>
#include <fstream>
#include <string>
#include <map>

#define SAND_START_POINT 500
using namespace std;

enum MATERIAL{
    ROCK,
    SAND
};

//implementation with Set is more efficient but with map
//it was easier to print and visualize the results.
typedef map<pair<unsigned int,unsigned int>, MATERIAL> Scan;
typedef pair<unsigned int, unsigned int> Point;

//those 2 points will be used for determining if sand is out of
//boundaries
Point minmax_vertical;
Point minmax_horizontal;

void updateMinMax(Point point){
    if(point.first > minmax_horizontal.second){
        minmax_horizontal.second = point.first;
    }
    else if(point.first < minmax_horizontal.first){
        minmax_horizontal.first = point.first;
    }
    if(point.second > minmax_vertical.second){
        minmax_vertical.second = point.second;
    }
    else if(point.second < minmax_vertical.first){
        minmax_vertical.first = point.second;
    }
}

void addLineToScan(Scan& scan, Point point_from, Point point_to){
    //if a,b->c,d and a < c direction is right if not going left
    bool right_left = (point_from.first <= point_to.first);
    for(unsigned int i = 1 ; i <= abs(int(point_from.first) - int(point_to.first)) ; ++i){
        if(right_left){
            scan.insert({Point{Point{point_from.first + i, point_from.second}}, ROCK});
        }
        else{
            scan.insert({Point{Point{point_from.first - i, point_from.second}}, ROCK});
        }
    }
    bool up_down = (point_from.second <= point_to.second);
    for(unsigned int i = 1 ; i <= abs(int(point_from.second) - int(point_to.second)) ; ++i){
        if(up_down){
            scan.insert({Point{Point{point_from.first, point_from.second + i}}, ROCK});
        }
        else{
            scan.insert({Point{Point{point_from.first, point_from.second - i}}, ROCK});
        }
    }
    updateMinMax(point_to);
    scan.insert({Point{point_to}, ROCK});
}

Point createPair(string& path){
    Point res;
    string::size_type sz;
    res.first = stoi(path, &sz);
    path.erase(0, sz + 1);
    res.second = stoi(path, &sz);
    path.erase(0, sz + 1);
    return res;
}

void addRocksPathToMap(Scan& scan, string& path){
    Point line_start;
    Point line_end;

    line_start = createPair(path);
    scan.insert({Point{line_start}, ROCK});
    string::size_type sz = path.find('>');
    path.erase(0, sz + 2);

    while(!path.empty()){
        line_end = createPair(path);
        addLineToScan(scan, line_start, line_end);
        sz = path.find('>');
        if(sz == string::npos){
            break;
        }
        path.erase(0, sz + 2);
        line_start = line_end;
    }


}

bool trickleSand(Scan& scan){
    //check if entrance of sand is blocked
    if(scan.find(Point{SAND_START_POINT, 0}) != scan.end()){
        return false;
    }

    int x = SAND_START_POINT;
    int y = 0;

    while(y <= minmax_vertical.second){

        //check if sand can go down
        if(scan.find(Point{x, y + 1}) == scan.end()){
            ++y;
            continue;
        }
        //if can't go one down check if left->down is free
        else if(scan.find(Point{x - 1, y + 1}) == scan.end()){
            --x;
            ++y;
            continue;
        }
        //if can't do last move check if right->down is free{
        else if(scan.find(Point{x + 1, y + 1}) == scan.end()){
            ++x;
            ++y;
            continue;
        }


        //if down, left->down, right->down blocked, then the current
        //<x,y> is the new sand point
        scan.insert({Point{x,y}, SAND});
        if(x > minmax_horizontal.second) minmax_horizontal.second = x;
        if(x < minmax_horizontal.first) minmax_horizontal.first = x;
        return true;
    }
    //our grain of sand is currently 1 unit of distance away from the floor
    //so we will create a flor below it and add the grain of sand
    scan.insert({Point{x,y+1}, ROCK});
    scan.insert({Point{x,y}, SAND});
    return true;
//    //if we're here it means that we couldn't add a sand point inside the
//    //limits of the scan, that means our sand is falling to the void

}

void printScan(Scan& scan){
    for(int j = minmax_vertical.first ; j <= minmax_vertical.second + 2 ; ++j){
        for(int i = minmax_horizontal.first; i <= minmax_horizontal.second ; ++i){
            if(j == minmax_vertical.second + 2){
                cout << "#";
            }
            if(scan.count(Point{i,j}) == 0){
                cout << ".";
            }
            if(scan.find(Point{i,j})->second == ROCK){
                cout << "#";
            }
            else{
                cout << "o";
            }
        }
        cout << endl;
    }
}

void handleFile(string& file_name){
    ifstream input_file(file_name);
    if(!input_file.is_open()){
        cerr << "file opening error" << endl;
        return;
    }
    Scan scan;
    string line;

    //build the rock walls and set premises for later use
    minmax_vertical.first = minmax_vertical.second = 0;
    minmax_horizontal.first = minmax_horizontal.second = SAND_START_POINT;
    while(getline(input_file, line)){
        addRocksPathToMap(scan, line);
    }
    //tickle sand until it starts falling to the void
    //or it blocks the entrance
    int grains_of_sand = 0;
    while(trickleSand(scan)){
        ++grains_of_sand;
//        printScan(scan);
    }
    cout << endl;
}

int main() {
    string path("input.txt");
    handleFile(path);

    return 0;
}

