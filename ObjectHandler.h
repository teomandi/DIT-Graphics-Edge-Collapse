#include <iostream>
#include <list> 
#include <map> 

using namespace std;

#ifndef OBJHANDLER
#define OBJHANDLER

class Vertice{
    public:
        double x;
        double y;
        double z;

        Vertice(int xi, int yi, int zi);
};

class Edge{
    public:
        Vertice v_start;
        Vertice v_end;
};

class Face{
    public:
        Vertice v1;
        Vertice v2;
        Vertice v3;
};

class ObjectHandler{
        list<Face> triangles;
        map<int, Vertice*> vertices;
    
    public:
        int test;
        bool status;

        int verticesSize;
        int facesSize;


        ObjectHandler(string filename);
        void printSummary();
};



#endif