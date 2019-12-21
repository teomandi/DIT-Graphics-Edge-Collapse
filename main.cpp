#include <fstream> //to open and read file
#include <iostream>
#include "helper.h"
#include "rawMaterial.h"
#include "ObjectHandler.h"

using namespace std;



int main() {
    // string objfile = "obj/simple.obj";
    // string objfile = "obj/teapot.obj";
    string objfile = "obj/medium.obj";


    ObjectHandler* oHandler= new ObjectHandler();
    oHandler->loadObject(objfile);
    oHandler->extractEdges();
    cout <<"Preproccess: Done"<< endl;
    list<Edge>::iterator eit;
    int i =0;
    for (eit = oHandler->edges.begin(); eit != oHandler->edges.end(); ++eit){
        i++;
        if (i == 15){
            eit->printEdge();
            list<Face*> hotArea = oHandler->getHotArea(&(*eit));
            cout << endl;
            break;
        }

    }



    // oHandler->printSummary();
    // oHandler->storeObject("obj/new.obj");
    cout << "Bye" << endl;
    return 0;
}