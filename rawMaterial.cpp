#include "rawMaterial.h"

//~~VERTICES~~
Vertice::Vertice(float xi,float yi,float zi){
    x=xi;
    y=yi;
    z=zi;
    energy = true;
    index = -1;
}

void Vertice::printVertice(){
    cout <<"(x,y,z): (" << x <<", " << y << ", " << z << ") ";
}

bool Vertice::equalVertice(Vertice *v){
    return ( v->x==x && v->y == y && v->z == z);
}


//~~FACES~~
Face::Face(Vertice *p1, Vertice *p2, Vertice *p3){
    v1 = p1;
    v2 = p2;
    v3 = p3;
}

bool Face::containsVertice(Vertice *v){
    if(v1->equalVertice(v)
     || v2->equalVertice(v)
     || v3->equalVertice(v)
    )
        return true;
    else
        return false;
}


//~~EDGES~~
Edge::Edge(Vertice *x, Vertice *y){
    //start is small | end is big
    vStart = x;
    vEnd = y;

}

void Edge::printEdge(){
//    cout << "not implemented yet." << endl;
    vStart->printVertice();
    cout << "----";
    vEnd->printVertice();
}
