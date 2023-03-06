#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#define ROUNDS 10000
#define PRIMES 8
using namespace std;

vector<int> primes_arr = {2,3,5,7,11,13,17,19};

class Monkey{
    vector<vector<int>> items;
    //variables for operation:
    int operation_val;
    char arith;
    //variables for test:
    int divisible_by;
    int throw_to_true;
    int throw_to_false;

    vector<int>& operation(vector<int>& item) const{
        if(arith == '+'){
            for(int i = 0 ; i < PRIMES ; ++i){
                item[i] += operation_val;
                item[i] %= primes_arr[i];
            }
            return item;
        }
        else if(arith == '*'){
            for(int i = 0 ; i < PRIMES ; ++i){
                item[i] *= operation_val;
                item[i] %= primes_arr[i];
            }
            return item;
        }
        else if(arith == '^'){
            for(int i = 0 ; i < PRIMES ; ++i){
                item[i] *= item[i];
                item[i] %= primes_arr[i];
            }
            return item;
        }
        return item;
    }

    static void makeModuloArr(int num, vector<int>& arr){
        for(int i = 0 ; i < PRIMES ; ++i){
            arr.push_back(num % primes_arr[i]);
        }
    }

    bool test(vector<int> item) const{
        return (item[divisible_by] == 0);
    }
public:
    Monkey(string& line, ifstream& file){
        getline(file,line);
        //Stating items
        line = line.substr(line.find(':') + 2);
        while(!line.empty()){
            //initialize item in items
            vector<int> arr;
            int num = stoi(line.substr(0, line.find(',')));
            makeModuloArr(num, arr);
            items.push_back(arr);
            //get next item
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
        //save the index of prime and not the prime itself
        for(int i = 0 ; i < PRIMES ; ++i){
            if(divisible_by == primes_arr[i]){
                divisible_by = i;
                break;
            }
        }

        //throw_to_true
        getline(file,line);
        throw_to_true = stoi(line.substr(line.find_last_of(' ') + 1));

        //throw_to_false
        getline(file,line);
        throw_to_false = stoi(line.substr(line.find_last_of(' ') + 1));

    };

    void addItem(const vector<int>& item){items.push_back(item);}
    bool hasItems() {return !items.empty();}

    void play(int& throw_to, vector<int>& item){
        //play and increase worry level
        item = operation(*items.begin());
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
    vector<int> curr_item;
    for(int i = 0 ; i < monkeys.size() ; ++i){
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
        cout << i << "  " <<hist[i] << endl;
    }

    max.sort();
    long long int monkey_business = 1;
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

