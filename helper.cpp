#include <fstream> //to open and read file
#include <iostream>

#include "ObjectHandler.h"


using namespace std;

int readFile(string path){
    cout << "NEW HELPER"<<endl;
    ifstream in(path);
    if(!in) {
        cout << "Cannot open input file.\n";
        return 1;
    }
    char str[255];
    while(in) {
        in.getline(str, 255);  // delim defaults to '\n'
        if(in) cout << str << endl;
    }
    in.close();
    return 0;
}

