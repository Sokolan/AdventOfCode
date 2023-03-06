#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define AT_MOST 100000
#define TOTAL_SIZE 70000000
#define UPDATE_SIZE 30000000

using namespace std;

class File {
	const string name;
	long int size;
public:
	File(string  name, const long int size) : name(std::move(name)), size(size){};
	long int getSize() const {return size;};
};

class Dir{
	const string name;
	Dir* parent;
	vector<Dir*> subDirs;
	vector<File> files;
	long int size;

public:
	Dir(string  name, Dir* parent) : name(std::move(name)), parent(parent), size(0){};

	void addSubDir(Dir* dir){subDirs.push_back(dir);}
	void addFile(File& file){files.push_back(file);}

	Dir* getParent(){return parent;}
    vector<Dir*>& getSubDirs(){return subDirs;};

    Dir* getDir(const string& dirName){
        for(auto i : subDirs){
            if(i->name == dirName){
                return i;
            }
        }
        return nullptr;
    }

    long int getDirSize() const{return size;};

	long int calcDirSize(){
		for(const auto& i : files){
			size += i.getSize();
		}
		for(auto i : subDirs){
			size += i->calcDirSize();
		}
		return size;
	}
};

class Shell{
    string buff;
    Dir* homeDir;
	Dir* currDir;
    ifstream inputFile;
	void cdCommand(const string& newDir) {
        if (newDir == "/") {
            currDir = homeDir;
        }
        else if (newDir == "..") {
            currDir = currDir->getParent();
        }
        else{
            currDir = currDir->getDir(newDir);
        }
    }
    void lsCommand(){
        if(buff.substr(0, 3) == "dir"){
            Dir* dir = new Dir(buff.substr(buff.find(' ') + 1), currDir);
            currDir->addSubDir(dir);
        }
        else{
            File file(buff.substr(buff.find(' ')+1), stoi(buff.substr(0, buff.find(' '))));
            currDir->addFile(file);
        }
    }

    void parseCommand(){
        if(buff.empty()){
            return;
        }

        if(buff == "$ ls"){
            return;
        }

        if(buff[0] != '$'){
            lsCommand();
            return;
        }

        if(buff.substr(0, 4) == "$ cd"){
            cdCommand(buff.substr(buff.find_last_of(' ') + 1));
            return;
        }
    }

    void deleteDirTree(Dir* dir){
        for(auto i : dir->getSubDirs()){
            deleteDirTree(i);
        }
        delete dir;
    }

	public:
	explicit Shell(const string& fname) : homeDir(new Dir("/", nullptr)), currDir(homeDir),
        inputFile(ifstream(fname)) {
        if(!inputFile.is_open()){
            cerr << "file open error" << endl;
        }
    };
    ~Shell(){
        deleteDirTree(homeDir);
    }

    void readFile(){
        while(getline(inputFile, buff)){
            parseCommand();
        }
    }

    Dir* getHomeDir() {return homeDir;};
    void calculateSizes(){homeDir->calcDirSize();};

    long int sumOfDirsUnder1K(Dir* dirRoot){

        long int sum = 0;
        for(auto i : dirRoot->getSubDirs()){
            sum += sumOfDirsUnder1K(i);
        }
        if(dirRoot->getDirSize() <= AT_MOST){
            sum += dirRoot->getDirSize();
        }
        return sum;
    }

    void minDirAboveSize(long int threshold, long int& min, Dir* dir){
        if(dir->getDirSize() < min && dir->getDirSize() >= threshold){
            min = dir->getDirSize();
        }
        for(auto i : dir->getSubDirs()){
            minDirAboveSize(threshold, min, i);
        }
    }

};


int main(){
    string input = "test.txt";
    Shell shell(input);
    shell.readFile();
    shell.calculateSizes();
    cout << shell.getHomeDir()->getDirSize() << endl;
    long int threshold = UPDATE_SIZE - (TOTAL_SIZE - shell.getHomeDir()->getDirSize());
    long int min = shell.getHomeDir()->getDirSize();
    shell.minDirAboveSize(threshold, min, shell.getHomeDir());
    cout << min << endl;
    return 0;
}
