#include <fstream> 
#include <cstring>
#include "ObjectHandler.h"
#include "rawMaterial.h"


using namespace std;


bool ObjectHandler::loadObject(string filepath){
    cout << "NEW OBJ PARSER"<<endl;
    ifstream in(filepath);
    if(!in) {
        cout << "Cannot open input file.\n";
        return false;
    }

    filename = filepath;
    char line[255];
    while(in) {
        in.getline(line, 255);
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
                    Vertice v(xi, yi, zi);
                    vertices.insert(make_pair(verticesSize, Vertice(xi, yi, zi)));
                }
                else if(strcmp(objpart, "f") == 0){                    
                    int pointer;
                    Vertice *v1, *v2, *v3;

                    objpart = strtok(NULL, " ");
                    pointer = atoi(objpart);
                    v1 = &vertices.find(pointer)->second;

                    objpart = strtok(NULL, " ");
                    pointer = atoi(objpart);
                    v2 = &vertices.find(pointer)->second;

                    objpart = strtok(NULL, " ");
                    pointer = atoi(objpart);
                    v3 = &vertices.find(pointer)->second;
                    v3->printVertice();

                    triangles.push_back(Face(v1, v2, v3));
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

    map<int, Vertice>::iterator vit;
    int current_index = 1;
	for(vit = vertices.begin(); vit != vertices.end(); ++vit){
        if(vit->second.energy){
            string line = "v " 
                + to_string(vit->second.x) 
                + " " + to_string(vit->second.y) 
                + " " + to_string(vit->second.z)
                + "\n";
            outfile << line;
            vit->second.index = current_index;
            current_index++;
        }
	}

    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        string line = "f " 
            + to_string(fit->v1->index)
            + " " +  to_string(fit->v2->index)
            + " " + to_string(fit->v3->index)
            + "\n";
        outfile << line;
    }
	outfile.close();
    return true;
}

bool ObjectHandler::edgeExists(Edge *e){
    //parse all the edges and check if they exists
    list<Edge>::iterator eit;
    for (eit = edges.begin(); eit != edges.end(); ++eit){
        if((eit->vStart->equalVertice(e->vStart) && eit->vEnd->equalVertice(e->vEnd))
            || (eit->vStart->equalVertice(e->vEnd) && eit->vEnd->equalVertice(e->vStart)))
            return false;
    }
    return true;
}

void ObjectHandler::extractEdges(){
    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        Edge e1(fit->v1, fit->v2);
        Edge e2(fit->v2, fit->v3);
        Edge e3(fit->v3, fit->v1);
        if(edgeExists(&e1))
            edges.push_back(e1);
        if(edgeExists(&e2))
            edges.push_back(e2);
        if(edgeExists(&e3))
            edges.push_back(e3);
    }
}

void ObjectHandler::printSummary(){
    cout << "VERTICES: " << vertices.size() << endl;
    map<int, Vertice>::iterator vit;
    for ( vit = vertices.begin(); vit != vertices.end(); vit++ ){
        cout << vit->first << ") ";
        vit->second.printVertice();
        cout << endl;
    }
    cout << "FACES: " << triangles.size() << endl;
    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        cout << "Vertice: "<< endl;
        fit->v1->printVertice();
        cout << endl;
        fit->v2->printVertice();
        cout << endl;
        fit->v3->printVertice();
        cout << endl;
        cout << "----" << endl;
    }
    cout << "EDGES: "<< edges.size() << endl;
    list<Edge>::iterator eit;
    for (eit = edges.begin(); eit != edges.end(); ++eit){
        cout << "Start: ";
        eit->vStart->printVertice();
        cout << endl << "End: ";
        eit->vEnd->printVertice();
        cout << endl << "----" << endl;
    }
}