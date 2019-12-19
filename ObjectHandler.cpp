#include <fstream> 
#include <cstring>
#include "ObjectHandler.h"


using namespace std;

Vertice::Vertice(float xi,float yi,float zi){
    x=xi;
    y=yi;
    z=zi;
}

void Vertice::printVertice(){
    cout <<"(x,y,z): (" << x <<", " << y << ", " << z << ") ";
}

Face::Face(int p1, int p2, int p3){
    v1 = p1;
    v2 = p2;
    v3 = p3;
}

Edge::Edge(int x, int y){
    //start is small | end is big
    if(x > y){
        vStart = y;
        vEnd = x;
    }else{
        vStart = x;
        vEnd = y;
    }
}

void Edge::printEdge(){
    cout << vStart << "--->---" << vEnd << endl;
}

bool ObjectHandler::loadObject(string filepath){
    filename = filepath;
    cout << "NEW OBJ PARSER"<<endl;

    ifstream in(filepath);
    if(!in) {
        cout << "Cannot open input file.\n";
        return false;
    }
    verticesSize = 0;
    facesSize = 0;

    char line[255];
    while(in) {
        in.getline(line, 255);  // delim defaults to '\n'
        if(in){
            char* objpart = strtok(line, " ");
            while(objpart){
                if(strcmp(objpart,"v") == 0){
                    // Create the vertice and add it to the map
                    float xi, yi, zi;
                    objpart = strtok(NULL, " ");
                    xi = atof(objpart);
                    objpart = strtok(NULL, " ");
                    yi = atof(objpart);
                    objpart = strtok(NULL, " ");
                    zi = atof(objpart);

                    verticesSize ++;
                    vertices.insert(make_pair(verticesSize, new Vertice(xi, yi, zi)));
                }
                else if(strcmp(objpart, "f") == 0){
                    int  p1, p2, p3;

                    objpart = strtok(NULL, " ");
                    p1 = atoi(objpart);
                    objpart = strtok(NULL, " ");
                    p2 = atoi(objpart);
                    objpart = strtok(NULL, " ");
                    p3 = atoi(objpart);
                    
                    facesSize ++;
                    triangles.push_back(Face(p1, p2, p3));
                }
                else{
                    cout << "Warning:: Unknown value in obj.";
                }
                objpart = strtok(NULL, " ");
            }
        }
    }
    in.close();
    return true;
}

bool ObjectHandler::storeObject(string filepath){
    ofstream outfile;
  	outfile.open(filepath);

    map<int, Vertice*>::iterator vit;
	for(vit = vertices.begin(); vit != vertices.end(); ++vit){
        string line = "v " 
            + to_string(vit->second->x) 
            + " " + to_string(vit->second->y) 
            + " " + to_string(vit->second->z)
            + "\n";
		outfile << line;
	}

    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        string line = "f " 
            + to_string(fit->v1)
            + " " +  to_string(fit->v2)
            + " " + to_string(fit->v3)
            + "\n";
        outfile << line;
    }
	outfile.close();
    return true;
}

void ObjectHandler::extractEdges(){
    list<Face>::iterator eit;
    for (eit = triangles.begin(); eit != triangles.end(); ++eit){
        cout << "???" << endl;
        Edge *e1, *e2, *e3;
        e1 = new Edge(eit->v1, eit->v2);
        e2 = new Edge(eit->v2, eit->v3);
        e3 = new Edge(eit->v3, eit->v1);

        set<Edge>::iterator eit2;
        eit2 = edges.find(*e2);
        e2->printEdge();
        if(eit2 != edges.end()){
            cout<<"founddd" << endl; 
        }else{
            cout<<"noootfounddd" << endl; 

        }

        edges.insert(*e1);
        edges.insert(*e2);
        edges.insert(*e3);
    }

}

void ObjectHandler::printSummary(){
    cout << "VERTICES: " << verticesSize << endl;
    map<int, Vertice*>::iterator vit;
    for ( vit = vertices.begin(); vit != vertices.end(); vit++ ){
        cout << vit->first << ") ";
        vit->second->printVertice();
        cout << endl;
    }
    cout << "FACES: " << facesSize << endl;
    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        cout << "Vertice: "<< endl;
        cout << fit->v1; 
        vertices.find(fit->v1)->second->printVertice();
        cout << endl;
        cout << fit->v2; 
        vertices.find(fit->v2)->second->printVertice();
        cout << endl;
        cout << fit->v3; 
        vertices.find(fit->v3)->second->printVertice();
        cout << endl;
    }
    cout << "EDGES: "<< endl;
    set<Edge>::iterator eit;
    for (eit = edges.begin(); eit != edges.end(); ++eit){
        cout << eit->vStart << "--->---" << eit->vEnd << endl;
        
    }
}