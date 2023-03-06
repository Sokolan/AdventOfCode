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

int main() {
    string input("input.txt");
    list<Ball> balls;
    handleFile(input, balls);
    int y = 2000000;
    unsigned int cannot_contain_beacon = findNoBeaconPositions(balls, y);
    cout << cannot_contain_beacon << endl;
    return 0;
}
