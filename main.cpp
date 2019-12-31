#include <fstream> //to open and read file
#include <iostream>
#include "helper.h"
#include "rawMaterial.h"
#include "ObjectHandler.h"
#include <time.h>
#include <string.h>

using namespace std;


int main(int argc, char* argv[]) {
    bool randomCollapse = false;
    string objfile, outfile;
    float compress_value = 0.1;
    for(int i=0; i<argc; i++){
        if( strcmp(argv[i], "-f") == 0 ){
            objfile = argv[i+1];
            i++;
        }
        else if(strcmp(argv[i], "-c") == 0){
            compress_value = atof(argv[i+1]);
            i++;
        }
        else if( strcmp(argv[i], "-o") == 0 ){
            outfile = argv[i+1];
            i++;
        }
        else if( strcmp(argv[i], "-r") == 0 ){
            randomCollapse = true;
            srand(time(NULL));
            cout << "Random collapse activated!" << endl;
        }
        else{
            cout << "Error: Unknown argument: " << argv[i] << endl;
        }
    }

    cout << objfile << endl;

    ObjectHandler* oHandler= new ObjectHandler();
    oHandler->loadObject(objfile);
    oHandler->extractEdges();
    cout <<"Preproccess: Done"<< endl;
    oHandler->pintSimpleSummary();

    int reps = int(compress_value*oHandler->edges.size());
    for(int i=0; i< reps; i++){
        if(!randomCollapse){
            Edge *bestEdge;
            double minDist = 999;
            list<Edge>::iterator e;
            for (e = oHandler->edges.begin(); e != oHandler->edges.end(); ++e){ //calculate the best edge to collapse
                double dist = oHandler->collapseValue(&(*e));
                if (dist < minDist){
                    minDist = dist;
                    bestEdge = &(*e);
                }
            }
            Vertice *v = oHandler->EdgeCollapse(bestEdge);
            cout << "Collpased Dist:: " << minDist << " ITER: " << to_string(i)  <<" from "<< to_string(reps) << endl;
        }
        else{
            int randEdge = rand()%( oHandler->edges.size() + 1 );
            if(randEdge >= oHandler->edges.size()){
                cout << "WARNING too large edge: "<< randEdge << " Max: " << oHandler->edges.size() <<endl;
                continue;
            }
            list<Edge>::iterator eit = oHandler->edges.begin();
            advance(eit, randEdge);
            Vertice *v = oHandler->EdgeCollapse(&(*eit));
            cout << "Collpased Progress:: " << to_string(i)  <<" from "<< to_string(reps) << endl;

        }

        //create more models.
        if(i==int(0.1*oHandler->edges.size())){
            cout << "10%. Storing: " << endl;
             oHandler->storeObject(outfile+"10.obj");
        }
        else if(i==int(0.2*oHandler->edges.size())){
            cout << "20%. Storing: " << endl;
             oHandler->storeObject(outfile+"20.obj");
        }
        else if(i==int(0.3*oHandler->edges.size())){
            cout << "30%. Storing: " << endl;
             oHandler->storeObject(outfile+"30.obj");
        }
        else if(i==int(0.5*oHandler->edges.size())){
            cout << "50%. Storing: " << endl;
             oHandler->storeObject(outfile+"50.obj");
        }
    }
    oHandler->pintSimpleSummary();
    oHandler->storeObject(outfile + ".obj");

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
    // cleanF(HA_after);
    // cleanF(HA_before);


    //pick random edges and collapse
    // float compress_value = 0.5;
    // int reps = 0;
    // srand(time(NULL));
    // for(int i=0; i<oHandler->edges.size()*compress_value; i++){
    //     reps++;
    //     int randEdge = rand()%( oHandler->edges.size() + 1 );
    //     if(randEdge >= oHandler->edges.size()){
    //         cout << "WARNING too large edge: "<< randEdge << " Max: " << oHandler->edges.size() <<endl;
    //         continue;
    //     }
    //     list<Edge>::iterator eit = oHandler->edges.begin();
    //     advance(eit, randEdge);
    //     Vertice *v = oHandler->EdgeCollapse(&(*eit));
    // }
    // cout << "Complete. Reps: " << reps << endl;
    // oHandler->storeObject("obj/pumpkin_tall_x5.obj");
    // oHandler->pintSimpleSummary();