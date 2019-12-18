#include <iostream>
#include <fstream> 
#include <cstring>
#include "ObjectHandler.h"


using namespace std;

Vertice::Vertice(int xi,int yi,int zi){
    x=xi;
    y=yi;
    z=zi;
}

ObjectHandler::ObjectHandler(string filename){
    cout << "NEW OBJ PARSER"<<endl;

    ifstream in(filename);
    if(!in) {
        cout << "Cannot open input file.\n";
        status = false;
        return;
    }
    status = true;
    verticesSize = 0;

    char line[255];
    while(in) {
        in.getline(line, 255);  // delim defaults to '\n'
        if(in){
            cout << "-->" << line << endl;
            char* objpart = strtok(line, " ");
            while(objpart){
                if(strcmp(objpart,"v") == 0){
                    double xi, yi, zi;

                    objpart = strtok(NULL, " ");
                    cout << " XXX " << objpart << endl;
                    xi = atof(objpart);

                    objpart = strtok(NULL, " ");
                    yi = atof(objpart);

                    objpart = strtok(NULL, " ");
                    zi = atof(objpart);

                    // Create the vertice and add it to the map
                    verticesSize ++;
                    Vertice* v = new Vertice(xi, yi, zi);
                    vertices.insert(make_pair(verticesSize, v));

                }
                //same for faces.
                else{
                    cout << "" << endl;
                }
                objpart = strtok(NULL, " ");
            }

        }
    }
    in.close();
}

void ObjectHandler::printSummary(){

    map<int, Vertice*>::iterator it;
    cout << "VERTICES: " << endl;

    for ( it = vertices.begin(); it != vertices.end(); it++ )
    {
        cout << it->first << ") " <<" X: " << it->second->x << endl ;
    }
}

