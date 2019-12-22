#include <fstream> //to open and read file
#include <iostream>
#include "helper.h"
#include "rawMaterial.h"
#include "ObjectHandler.h"

using namespace std;



int main() {
    // string objfile = "obj/simple.obj";
    // string objfile = "obj/medium.obj";
    string objfile = "obj/teapot.obj";


    ObjectHandler* oHandler= new ObjectHandler();
    oHandler->loadObject(objfile);
    oHandler->extractEdges();
    // cout <<"Preproccess: Done"<< endl;
    oHandler->pintSimpleSummary();

    //pick random edges and collapse
    float compress_value = 0.01;
    int reps = 0;

    for(int i=0; i<oHandler->edges.size()*compress_value; i++){
        reps++;
        int randEdge = rand()%( oHandler->edges.size() + 1 );
        cout << "E: "<< randEdge << endl;
        
        list<Edge>::iterator eit = oHandler->edges.begin();
        advance(eit, randEdge);
        cout << "????" << endl;

        Vertice *v = oHandler->EdgeCollapse(&(*eit));
        cout << oHandler->edges.size() << endl;

    }
    cout << "DONEEE" << endl;
    cout << "reps: " << reps << endl; 
    oHandler->storeObject("obj/teapot_01.obj");


    // advance(eit, 14); //14 from 0 is the wanted one.
    // eit->printEdge();
    
    // list<Face*> HA_before = oHandler->getHotArea(&(*eit));
    // Vertice *v = oHandler->EdgeCollapse(&(*eit));
    // list<Face*> HA_after = oHandler->getHotArea(v);

    // cout << HA_before.size() << " --- " << HA_after.size() << endl;
    // cout << "HD: " << oHandler->HausdorffDistance(HA_before, HA_after) << endl;
    // clean(HA_after);
    // clean(HA_before);



    delete(oHandler);
    cout << "Bye" << endl;
    return 0;
}