#include "rawMaterial.h"
#include "helper.h"
#include <math.h>

//~~VERTICES~~
Vertice::Vertice(float xi,float yi,float zi){
    x=xi;
    y=yi;
    z=zi;
    energy = true;
    index = -1;
}

void Vertice::printVertice(){
    cout << index <<" (x,y,z): (" << x <<", " << y << ", " << z << ") ";
}

bool Vertice::equalVertice(Vertice *v){
    return ( v->x==x && v->y == y && v->z == z);
}

double Vertice::distanceVertice(Vertice *v){
    //Eucledean value from (0, 0, 0)
    float d = pow((x-v->x), 2) + pow((y-v->y), 2) + pow((z-v->z), 2);
    return sqrt(d);
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

bool Face::equalFace(Face *f){
    if(v1->equalVertice(f->v1)
    && v2->equalVertice(f->v2)
    && v3->equalVertice(f->v3) )
        return true;
    else
        return false;
}

double Face::maxDistanceFromVertice(Vertice* v){
    //returns the maximun distance from a point
    double dmax = 0;
    double dv1, dv2, dv3;

    dv1 = v1->distanceVertice(v);
    dv2 = v2->distanceVertice(v);
    dv3 = v3->distanceVertice(v);

   return maxDouble(dv1, dv2, dv3);
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

bool Edge::equalEdge(Edge *e){
    if(vStart->equalVertice(e->vStart)
        && vEnd->equalVertice(e->vEnd))
        return true;
    else
        return false;
}

void clean(list<Face*> target){
    list<Face*>::iterator fit;
    for (fit = target.begin(); fit != target.end(); ++fit){
        delete((*fit));
    }
}  
