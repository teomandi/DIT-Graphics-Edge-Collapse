#include <fstream> 
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
        // get the name of the file
        if( strcmp(argv[i], "-f") == 0 ){
            objfile = argv[i+1];
            i++;
        }
        // get the compression value
        else if(strcmp(argv[i], "-c") == 0){
            compress_value = atof(argv[i+1]);
            i++;
        }
        // get the output path
        else if( strcmp(argv[i], "-o") == 0 ){
            outfile = argv[i+1];
            i++;
        }
        // collapse randomly edges
        else if( strcmp(argv[i], "-r") == 0 ){
            randomCollapse = true;
            srand(time(NULL));
            cout << "Random collapse activated!" << endl;
        }
        else{
            cout << "Error: Unknown argument: " << argv[i] << endl;
        }
    }

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
            //calculate the best edge to collapse
            for (e = oHandler->edges.begin(); e != oHandler->edges.end(); ++e){ 
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