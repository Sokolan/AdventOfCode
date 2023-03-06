#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#define NOT_LEAF (-1)

using namespace std;

enum RES{
    RIGHT_ORDER,
    WRONG_ORDER,
    UNDECIDED
};
class Node{
public:
    Node* parent;
    vector<Node*> sons;
    int val;
    explicit Node(Node* parent_in = nullptr, int val_in = NOT_LEAF) : parent(parent_in), val(val_in){};
    Node* createParent(){
        Node* new_node = new Node(parent);
        parent = new_node;
        new_node->sons.push_back(this);
        return new_node;
    }
};

class Tree{
    Node* head;
    void deleteTree(Node* node){
        for(auto i : node->sons){
            deleteTree(i);
        }
        delete node;
    }

public:
    explicit Tree(string& line){
        head = new Node;
        Node* curr = head;
        while(!line.empty()){
            if(line[0] == '['){
                curr->sons.push_back(new Node(curr));
                curr = curr->sons.back();
                line = line.substr(1);
            }
            else if(line[0] == ']'){
                curr = curr->parent;
                line = line.substr(1);
            }
            else if(line[0] == ','){
                line = line.substr(1);
            }
            else{
                string::size_type sz;
                curr->sons.push_back(new Node(curr, stoi(line, &sz)));
                line = line.substr(sz);
            }
        }
    }
    ~Tree(){
        deleteTree(head);
    }
    Node* getHead(){return head;};
};


RES isOrderRight(Node* lt, Node* rt){
    //check if Left list is not empty
    while(!lt->sons.empty()) {
        //check if right list is not empty
        if (rt->sons.empty()) {
            return RES::WRONG_ORDER;
        }

        //check if the 1st item on both lists is a list
        if (rt->sons.front()->val == NOT_LEAF && lt->sons.front()->val == NOT_LEAF) {
            RES res = isOrderRight(lt->sons.front(), rt->sons.front());
            if (res == RES::WRONG_ORDER || res == RES::RIGHT_ORDER) {
                return res;
            }
        }

        //check if the 1st item on both lists is an integer
        if (rt->sons.front()->val != NOT_LEAF && lt->sons.front()->val != NOT_LEAF) {
            //check for order in/correctness
            if (lt->sons.front()->val < rt->sons.front()->val) {
                return RES::RIGHT_ORDER;
            }
            if (lt->sons.front()->val > rt->sons.front()->val) {
                return RES::WRONG_ORDER;
            }
        }

        //check if left 1st item is an integer and right 1st item is a list
        if(rt->sons.front()->val == NOT_LEAF && lt->sons.front()->val != NOT_LEAF){
            //make the leaf into a list and retry
            lt->sons.front() = lt->sons.front()->createParent();
             RES res = isOrderRight(lt, rt);
             if(res == RES::RIGHT_ORDER || res == RES::WRONG_ORDER){
                 return res;
             }
        }
        //do same for the mirror case
        if(rt->sons.front()->val != NOT_LEAF && lt->sons.front()->val == NOT_LEAF){
            //make the leaf into a list and retry
            rt->sons.front() = rt->sons.front()->createParent();
            RES res = isOrderRight(lt, rt);
            if(res == RES::RIGHT_ORDER || res == RES::WRONG_ORDER){
                return res;
            }
        }


        lt->sons.erase(lt->sons.begin());
        rt->sons.erase(rt->sons.begin());
    }
    //check if right list still has items
    if(!rt->sons.empty()){
        return RES::RIGHT_ORDER;
    }
    return RES::UNDECIDED;
}



void handleFile(string& file_name){
    ifstream input_file(file_name);
    string line;
    int i = 1;
    int sum = 0;
    while(getline(input_file, line)){
        Tree A(line);
        getline(input_file, line);

        Tree B(line);
        getline(input_file, line);

        if(isOrderRight(A.getHead()->sons.front(), B.getHead()->sons.front()) == RES::RIGHT_ORDER){
            sum += i;
        }
        ++i;


    }
    cout << sum << endl;

}

int main() {
    string input("input.txt");
    handleFile(input);
    return 0;
}

