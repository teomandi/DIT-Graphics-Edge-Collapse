#include <iostream>
#include <list> 
#include <map> 
#include <set>

using namespace std;

#ifndef OBJHANDLER
#define OBJHANDLER

class Vertice{
    public:
        float x;
        float y;
        float z;

        Vertice(float xi, float yi, float zi);
        void printVertice();
};

class Edge{
    public:
        int vStart;
        int vEnd;
        Edge(int x, int y);
        void printEdge();
};

class Face{
    public:
        int v1;
        int v2;
        int v3;
        Face(int p1, int p2, int p3);
};

class ObjectHandler{
        list<Face> triangles;
        map<int, Vertice*> vertices;
        set<Edge> edges;
    
    public:
        string filename;
        int verticesSize;
        int facesSize;

        bool loadObject(string filename);
        bool storeObject(string filepath);
        void printSummary();

        void extractEdges();
};



#endif