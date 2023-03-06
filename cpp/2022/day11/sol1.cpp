#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#define ROUNDS 20

using namespace std;

class Monkey{
    //with int and long int results in integer overflow
    vector<long long int> items;
    //variables for operation:
    int operation_val;
    char arith;
    //variables for test:
    int divisible_by;
    int throw_to_true;
    int throw_to_false;

    long long int operation(long long int item) const{
        if(arith == '+'){
            return item + operation_val;
        }
        else if(arith == '*'){
            return item * operation_val;
        }
        else if(arith == '^'){
            return item * item;
        }
        return 0;
    }

    bool test(long long int item) const{
        return (item % divisible_by == 0);
    }
public:
    Monkey(string& line, ifstream& file){
        getline(file,line);
        //Stating items
        line = line.substr(line.find(':') + 2);
        while(!line.empty()){
            items.push_back(stoi(line.substr(0, line.find(','))));
            if(line.find(',') != string::npos){
                line.erase(0, line.find(',') + 2);
            }
            else{
                break;
            }
        }

        //Operation:
        getline(file,line);
        if(line.find('+') != string::npos){
            arith = '+';
            operation_val = stoi(line.substr(line.find('+') + 2));
        }
        if(line.find_last_of("old") == line.length() - 1){
            arith = '^';
            operation_val = 0;
        }
        else if(line.find('*') != string::npos){
            arith = '*';
            operation_val = stoi(line.substr(line.find('*') + 2));
        }


        //Test
        getline(file, line);
        divisible_by = stoi(line.substr(line.find_last_of(' ') + 1));

        //throw_to_true
        getline(file,line);
        throw_to_true = stoi(line.substr(line.find_last_of(' ') + 1));

        //throw_to_false
        getline(file,line);
        throw_to_false = stoi(line.substr(line.find_last_of(' ') + 1));

    };

    void addItem(long long int item){items.push_back(item);}
    bool hasItems() {return !items.empty();}

    void play(int& throw_to, long long int& item){
        //play and increase worry level
        item = operation(*items.begin());
        //monkey gets bored and worry level is divided by 3
        item /= 3;
        //item removed and monkey checks where to throw it
        items.erase(items.begin());
        if(test(item)){
            throw_to = throw_to_true;
        }
        else{
            throw_to = throw_to_false;
        }
    }
};

void playRound(vector<Monkey>& monkeys, int hist[]){
    int throw_to;
    long long int curr_item;
    for(long long int i = 0 ; i < monkeys.size() ; ++i){
        while(monkeys[i].hasItems()){
            monkeys[i].play(throw_to, curr_item);
            monkeys[throw_to].addItem(curr_item);

            ++hist[i];
        }
    }

}


void handleFile(const string& input){
    ifstream file(input);
    string line;
    vector<Monkey> monkeys;
    int num_of_monkeys = 0;
    while(getline(file, line)){
        Monkey monkey(line, file);
        monkeys.push_back(monkey);
        ++num_of_monkeys;
        getline(file, line);
    }

    int hist[num_of_monkeys];
    for(int i = 0 ; i < num_of_monkeys ; ++i){
        hist[i] = 0;
    }

    for(int i = 0 ; i < ROUNDS ; ++i){
        playRound(monkeys, hist);
    }

    list<int> max;
    for(int i = 0 ; i < monkeys.size() ; ++i){
        max.push_back(hist[i]);
        //to see how many items each monkey touched
//        cout << i << "  " <<hist[i] << endl;
    }

    max.sort();
    int monkey_business = 1;
    monkey_business *= max.back();
    max.pop_back();
    monkey_business *= max.back();
    cout << monkey_business << endl;
}

int main() {
    string file_name = "input.txt";
    handleFile(file_name);

    return 0;
}

