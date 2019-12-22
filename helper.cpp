#include <fstream> //to open and read file
#include <iostream>
#include <math.h>

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

double maxDouble(double d1, double d2, double d3){
     if( d1 > d2 ){
        if(d1 > d3)
            return d1;
        else
            return d3; 
    }
    else{
        if(d2 > d3)
            return d2;
        else
            return d3;
    }
}

void clean(list<Face*> target){
    list<Face*>::iterator fit;
    for (fit = target.begin(); fit != target.end(); ++fit){
        delete((*fit)->v1);
        delete((*fit)->v2);
        delete((*fit)->v3);
    }
}        
