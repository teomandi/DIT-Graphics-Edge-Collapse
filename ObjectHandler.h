#include <iostream>
#include <list> 
#include <set>
#include <map>
#include "rawMaterial.h"
#include "helper.h"


using namespace std;

#ifndef OBJHANDLER
#define OBJHANDLER

class ObjectHandler{
        list<Face> triangles;
    
    public:
        string filename;
        list<Edge> edges;
        map<int, Vertice> vertices;

        
        bool loadObject(string filename);
        bool storeObject(string filepath);
        bool edgeExists(Edge *e);

        void printSummary();
        void pintSimpleSummary();
        void extractEdges();
        
        list<Face*> getHotArea(Edge *e);
        list<Face*> getHotArea(Vertice *v);
        list<Face*> getPeripherialFaces(Edge *e);
        
        Vertice* EdgeCollapse(Edge *e);
        ObjectHandler* cloneObjHandler(ObjectHandler *oh);

        double HausdorffDistance(list<Face*> F1, list<Face*> F2);
};



#endif