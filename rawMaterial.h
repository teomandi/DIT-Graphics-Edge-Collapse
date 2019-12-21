#include <iostream>
#include <list> 

using namespace std;


#ifndef RAWMATERIAL
#define RAWMATERIAL

class Vertice{
    public:
        float x;
        float y;
        float z;
        
        bool energy;
        int index;
        
        Vertice(float xi, float yi, float zi);
        void printVertice();
        bool equalVertice(Vertice *v);
};

class Edge{
    public:
        Vertice *vStart;
        Vertice *vEnd;
        Edge(Vertice *x, Vertice *y);
        void printEdge();
};

class Face{
    public:
        Vertice *v1;
        Vertice *v2;
        Vertice *v3;

        Face(Vertice *p1, Vertice *p2, Vertice *p3);
};


#endif