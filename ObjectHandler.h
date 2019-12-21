#include <iostream>
#include <list> 
#include <set>
#include <map>
#include "rawMaterial.h"

using namespace std;

#ifndef OBJHANDLER
#define OBJHANDLER

class ObjectHandler{
        list<Face> triangles;
        list<Edge> edges;
        map<int, Vertice> vertices;
    
    public:
        string filename;
        
        bool loadObject(string filename);
        bool storeObject(string filepath);
        void printSummary();

        void extractEdges();
        bool edgeExists(Edge *e);
};



#endif