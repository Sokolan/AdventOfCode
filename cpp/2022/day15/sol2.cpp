#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <set>
#include <utility>

using namespace std;

typedef pair<int,int> Coordinate;
//[first, second]
typedef pair<int,int> Interval;

class Node{

public:
    Node* m_next;
    Node* m_prev;
    Interval m_interval;
    explicit Node(Interval interval, Node* prev = nullptr) : m_next(nullptr), m_prev(prev) ,m_interval(std::move(interval)){};
    ~Node(){
        if(m_prev != nullptr){
            m_prev->m_next = m_next;
        }
        if(m_next != nullptr){
            m_next->m_prev = m_prev;
        }
    }
    void insertBefore(Node* node){
        m_prev = node->m_prev;
        m_prev->m_next = this;
        m_next = node;
        node->m_prev = this;
    }

    void deleteNodes(Node* node){
        if(!node->m_next) return;
        Node* next = node->m_next;
        delete node;
        deleteNodes(next);
    }
};

class Ball{
    Coordinate m_center;
    Coordinate m_beacon;
    unsigned int m_radius;
public:
    Ball(Coordinate sensor, Coordinate beacon) : m_center(sensor), m_beacon(beacon){
        int x_distance = abs(beacon.first - sensor.first);
        int y_distance = abs(beacon.second - sensor.second);
        m_radius = x_distance + y_distance;
    }

    int getX() const {return m_center.first;}
    int getY() const {return m_center.second;}
    unsigned int getRadius() const {return m_radius;}
    Coordinate getBeacon() const {return m_beacon;}
};

Coordinate lineToCoordinate(string& line){
    Coordinate coordinate;
    line.erase(0, line.find('=') + 1);
    coordinate.first = stoi(line);
    line.erase(0, line.find('=') + 1);
    coordinate.second = stoi(line);
    return coordinate;
}

void initializeBallsFromFile(list<Ball>& balls, ifstream& input_file){
    string line;
    Coordinate sensor;
    Coordinate beacon;
    while(getline(input_file, line)){
        sensor = lineToCoordinate(line);
        beacon = lineToCoordinate(line);
        Ball ball(sensor, beacon);
        balls.push_back(ball);
    }
}


// returns {1,-1} as error
Interval intervalOfBallInY(const Ball& ball, int y){
    Interval interval;
    if(ball.getY() + int(ball.getRadius()) < y || ball.getY() - int(ball.getRadius()) > y){
        return {1,-1};
    }
    unsigned int distance_from_y = abs(y - ball.getY());
    interval.first = ball.getX() - int(ball.getRadius()) + int(distance_from_y);
    interval.second = ball.getX() + (int(ball.getRadius()) - int(distance_from_y));
    return interval;
}

Node* createIntervalsList(list<Ball>& balls, int y){
    Node* dummy = new Node(Node(Interval{INT32_MIN,INT32_MIN}));

    for(auto i : balls){
        Node* curr = new Node(intervalOfBallInY(i, y));
        if(curr->m_interval == Interval{1,-1}){
            delete curr;
            continue;
        }

        Node* it = dummy;

        while(it != nullptr){
            //[it.first, it.second]->nullptr [curr.first, curr.second]
            if(curr->m_interval.first > it->m_interval.second && it->m_next == nullptr){
                it->m_next = curr;
                curr->m_prev = it;
                break;
            }
            //[it.first, it.second] [curr.first, curr.second]
            if(curr->m_interval.first > it->m_interval.second){
                if(curr->m_interval.first == it->m_interval.second + 1){
                    curr->m_interval.first = it->m_interval.first;
                    Node* tmp = it->m_next;
                    delete it;
                    it = tmp;
                    continue;
                }
                it = it->m_next;
                continue;
            }
            //[it.first [curr.first,curr.second] it.second]
            if(curr->m_interval.first >= it->m_interval.first &&
               curr->m_interval.second <= it->m_interval.second){
                delete curr;
                break;
            }
            //[it.first [curr.first - it.second] curr.second]
            if(it->m_interval.first <= curr->m_interval.first &&
               it->m_interval.second <= curr->m_interval.second){
                if(it->m_next == nullptr){
                    it->m_interval.second = curr->m_interval.second;
                    delete curr;
                    break;
                }
                curr->m_interval.first = it->m_interval.first;
                Node* tmp = it;
                it = it->m_next;
                delete tmp;
                continue;
            }
            //[curr.first, [it.first,it.second] curr.second]
            if(curr->m_interval.first <= it->m_interval.first &&
               it->m_interval.second <= curr->m_interval.second){
                if(it->m_next == nullptr){
                    it->m_interval.second = curr->m_interval.second;
                    it->m_interval.first = curr->m_interval.first;
                    delete curr;
                    break;
                }
                Node* tmp = it;
                it = it->m_next;
                delete tmp;
                continue;
            }
            //[curr.first, curr.second] [it.first, it.second]
            if(curr->m_interval.second < it->m_interval.first){
                if(curr->m_interval.second + 1 == it->m_interval.first){
                    it->m_interval.first = curr->m_interval.first;
                    delete curr;
                    break;
                }
                curr->insertBefore(it);
                break;
            }
            //[curr.first, [it.first - curr.second] it.second]
            if(curr->m_interval.first <= it->m_interval.first &&
               curr->m_interval.second <= it->m_interval.second){
                it->m_interval.first = curr->m_interval.first;
                delete curr;
                break;
            }

        }
    }
    Node* ret_val = dummy->m_next;
    delete dummy;
    return ret_val;
}

unsigned int calculateNoBeaconFromList(const Node* node){
    int sum = 0;
    while(node != nullptr){
        //we add +1 because [a,b] is of length b-a but 'a' is also a point to count
        sum += node->m_interval.second - node->m_interval.first + 1;
        node = node->m_next;
    }
    return sum;
}

bool beaconInIntervals(const Node* head, Coordinate beacon){
    while(head != nullptr){
        if(head->m_interval.first <= beacon.second && beacon.second <= head->m_interval.second){
            return true;
        }
        head = head->m_next;
    }
    return false;
}

unsigned int findNoBeaconPositions(list<Ball>& balls, int y){
    Node* head = createIntervalsList(balls, y);
    unsigned int sum = calculateNoBeaconFromList(head);
    set<Coordinate> beacons_in_y;
    for(auto i : balls){
        if(i.getBeacon().second == y && beaconInIntervals(head, i.getBeacon())){
            beacons_in_y.insert(i.getBeacon());
        }
    }
    head->deleteNodes(head);
    return sum - beacons_in_y.size();
}

void handleFile(string& file_name, list<Ball>& balls){
    ifstream input_file(file_name);
    initializeBallsFromFile(balls, input_file);
}

bool checkIfIntervalCovered(Node* intervals_it, Interval interval){
    while(intervals_it != nullptr){
        //[it.first [interval.first, interval.second] it.second]
        if(intervals_it->m_interval.first <= interval.first &&
            interval.second <= intervals_it->m_interval.second){
            return true;
        }
        intervals_it = intervals_it->m_next;
    }
    return false;
}

int findNotCoveredX(Node* it, Interval interval){
    while(it != nullptr){
        //[it.first [interval.first - it.second] interval.second]
        if(it->m_interval.first <= interval.first &&
            it->m_interval.second <= interval.second){
            interval.first = it->m_interval.second + 1;
        }
        //[interval.first [it.first - interval.second] it.second]
        if(interval.first <= it->m_interval.first &&
            interval.second <= it->m_interval.second){
            interval.second = it->m_interval.first - 1;
        }
        it = it->m_next;
    }
    if(interval.first - interval.second != 0){
        return -1;
    }
    return interval.first;
}

//returns {-1,-1} as error
Coordinate findTuningFrequencyCoordinate(list<Ball>& balls, Coordinate min, Coordinate max){
    bool found = false;
    long long int x_coordinate;
    long long int y_coordinate;
    for(int y = min.second ; y <= max.second ; ++y){
        Node* node = createIntervalsList(balls, y);
        if(checkIfIntervalCovered(node, Interval{min.first, max.second})){
            node->deleteNodes(node);
            continue;
        }
        if(found){
            return Coordinate{-1,-1};
        }
        found = true;
        y_coordinate = y;
        x_coordinate = findNotCoveredX(node, Interval{min.first, max.first});
        node->deleteNodes(node);
    }
    return Coordinate{x_coordinate,y_coordinate};
}

long long int tuningFrequency(list<Ball>& balls, Coordinate min, Coordinate max){
    Coordinate coordinate = findTuningFrequencyCoordinate(balls, min, max);
    long long res = (long long int)(coordinate.first) * 4000000;
    res += coordinate.second;
    return res;
}

int main() {
    string input("input.txt");
    list<Ball> balls;
    handleFile(input, balls);
    //part 1:
//    int y = 2000000;
//    unsigned int cannot_contain_beacon = findNoBeaconPositions(balls, y);
//    cout << "part 1: " << cannot_contain_beacon << endl;
    //part 2:
    cout << "part 2: " << tuningFrequency(balls, Coordinate{0,0}, Coordinate{4000000,4000000}) << endl;
    return 0;
}