#include <fstream> //to open and read file
#include <iostream>


using namespace std;

/*
    Reads the lines of a file
*/ 
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

/*
    Gets the maximun double number between 3 numbers
*/
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

      
