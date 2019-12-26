#include <fstream> //to open and read file
#include <iostream>
#include "helper.h"
#include "rawMaterial.h"
#include "ObjectHandler.h"
#include <time.h>

using namespace std;



int main() {
    // string objfile = "obj/simple.obj";
    // string objfile = "obj/medium.obj";
    // string objfile = "obj/teapot.obj";
    // string objfile = "obj/cow-nonormals.obj";
    string objfile = "obj/pumpkin_tall_10k.obj";


    ObjectHandler* oHandler= new ObjectHandler();
    oHandler->loadObject(objfile);
    oHandler->extractEdges();
    cout <<"Preproccess: Done"<< endl;
    oHandler->pintSimpleSummary();

    //pick random edges and collapse
    float compress_value = 0.5;
    int reps = 0;
    srand(time(NULL));
    for(int i=0; i<oHandler->edges.size()*compress_value; i++){
        reps++;
        int randEdge = rand()%( oHandler->edges.size() + 1 );
        if(randEdge >= oHandler->edges.size()){
            cout << "WARNING too large edge: "<< randEdge << " Max: " << oHandler->edges.size() <<endl;
            continue;
        }
        list<Edge>::iterator eit = oHandler->edges.begin();
        advance(eit, randEdge);
        Vertice *v = oHandler->EdgeCollapse(&(*eit));
    }
    cout << "Complete. Reps: " << reps << endl;
    oHandler->storeObject("obj/pumpkin_tall_x5.obj");
    oHandler->pintSimpleSummary();


    delete(oHandler);
    cout << "Bye" << endl;
    return 0;
}





    // advance(eit, 14); //14 from 0 is the wanted one.
    // eit->printEdge();
    
    // list<Face*> HA_before = oHandler->getHotArea(&(*eit));
    // Vertice *v = oHandler->EdgeCollapse(&(*eit));
    // list<Face*> HA_after = oHandler->getHotArea(v);

    // cout << HA_before.size() << " --- " << HA_after.size() << endl;
    // cout << "HD: " << oHandler->HausdorffDistance(HA_before, HA_after) << endl;
    // clean(HA_after);
    // clean(HA_before);