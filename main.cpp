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
    // cout <<"Preproccess: Done"<< endl;
    oHandler->pintSimpleSummary();

    list<Edge>::iterator eit = oHandler->edges.begin();
    advance(eit, 14); //14 from 0 is the wanted one.
    eit->printEdge();
    
    list<Face*> HA_before = oHandler->getHotArea(&(*eit));
    Vertice *v = oHandler->EdgeCollapse(&(*eit));
    list<Face*> HA_after = oHandler->getHotArea(v);

    cout << HA_before.size() << " --- " << HA_after.size() << endl;
    cout << "HD: " << oHandler->HausdorffDistance(HA_before, HA_after) << endl;




    delete(oHandler);
    cout << "Bye" << endl;
    return 0;
}