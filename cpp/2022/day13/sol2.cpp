#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

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
    void unwrapOnce(unsigned int i){
        sons.front()->parent = parent;
        parent->sons[i] = sons.front();
        delete this;
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
    for(int i = 0 ; i < lt->sons.size() ; ++i){
        //check if right list has Ith element
        if (rt->sons.size() < i + 1) {
            return RES::WRONG_ORDER;
        }

        //check if the 1st item on both lists is a list
        if (rt->sons[i]->val == NOT_LEAF && lt->sons[i]->val == NOT_LEAF) {
            RES res = isOrderRight(lt->sons[i], rt->sons[i]);
            if (res == RES::WRONG_ORDER || res == RES::RIGHT_ORDER) {
                return res;
            }
        }

        //check if the 1st item on both lists is an integer
        if (rt->sons[i]->val != NOT_LEAF && lt->sons[i]->val != NOT_LEAF) {
            //check for order in/correctness
            if (lt->sons[i]->val < rt->sons[i]->val) {
                return RES::RIGHT_ORDER;
            }
            if (lt->sons[i]->val > rt->sons[i]->val) {
                return RES::WRONG_ORDER;
            }
        }

        //check if left 1st item is an integer and right 1st item is a list
        if(rt->sons[i]->val == NOT_LEAF && lt->sons[i]->val != NOT_LEAF){
            //make the leaf into a list and retry
            lt->sons[i] = lt->sons[i]->createParent();
            RES res = isOrderRight(lt, rt);
            lt->sons[i]->unwrapOnce(i);
            if(res == RES::RIGHT_ORDER || res == RES::WRONG_ORDER){
                return res;
            }
        }
        //do same for the mirror case
        if(rt->sons[i]->val != NOT_LEAF && lt->sons[i]->val == NOT_LEAF){
            //make the leaf into a list and retry
            rt->sons[i] = rt->sons[i]->createParent();
            RES res = isOrderRight(lt, rt);
            rt->sons[i]->unwrapOnce(i);
            if(res == RES::RIGHT_ORDER || res == RES::WRONG_ORDER){
                return res;
            }
        }
    }
    //check if right list still has items
    if(rt->sons.size() > lt->sons.size()){
        return RES::RIGHT_ORDER;
    }
    return RES::UNDECIDED;
}

struct TreeComparator{
    bool operator()(Tree* tree1, Tree* tree2){
        return isOrderRight(tree1->getHead(), tree2->getHead()) == RES::RIGHT_ORDER;
    }
};

void handleFile(string& file_name){
    ifstream input_file(file_name);
    string line;

    list<Tree*> tree_list;

    //create the two marks
    string str = "[[2]]";
    Tree* first_mark = new Tree(str);
    str = "[[6]]";
    Tree* second_mark = new Tree(str);
    //add the two marks into the list
    tree_list.push_back(first_mark);
    tree_list.push_back(second_mark);

    //get the rest of the items from input file
    while(getline(input_file, line)){
        Tree* A = new Tree(line);
        tree_list.push_back(A);

        getline(input_file, line);
        Tree* B = new Tree(line);
        tree_list.push_back(B);
        getline(input_file, line);
    }

    tree_list.sort(TreeComparator());
    int index = 1;
    int sum = 1;
    for(auto i : tree_list){
        if(i == first_mark){
            sum *= index;
            cout << "[[2]] position:    " << index << endl;
        }
        if(i == second_mark){
            cout << "[[6]] position:    " << index << endl;
            sum *= index;
        }
        ++index;
    }
    cout << sum << endl;
}

int main() {
    string input("input.txt");
    handleFile(input);
    return 0;
}
