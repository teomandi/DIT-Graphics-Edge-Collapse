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
    int index = 1;
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
                    vertices.insert(make_pair(index, Vertice(xi, yi, zi)));
                    index ++;
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
    cout <<"-----"<<endl;
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

            vit->second.printVertice();
            cout <<"?" <<endl;
        }
	}
    cout << "~~~~" << endl;
    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        string line = "f " 
            + to_string(fit->v1->index)
            + " " +  to_string(fit->v2->index)
            + " " + to_string(fit->v3->index)
            + "\n";
        outfile << line;
        
        fit->v1->printVertice();
        cout << " ?? " <<to_string(fit->v1->energy) <<endl;
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

void ObjectHandler::pintSimpleSummary(){
    cout<< "~~~ Siple summary" << endl;
    cout << "Vertices: " << vertices.size() << endl;
    cout << "Faces: " << triangles.size() << endl;
    cout << "Edges: " << edges.size() << endl;
    cout << "~~~~~" << endl;

}


list<Face*> ObjectHandler::getHotArea(Edge *e){
    list<Face*> hotFaces;

    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        if(fit->containsVertice(e->vStart) || fit->containsVertice(e->vEnd))
            hotFaces.push_back(new Face(fit->v1, fit->v2, fit->v3));
    }
    //**
    return hotFaces;
}

list<Face*> ObjectHandler::getHotArea(Vertice *v){
    list<Face*> hotFaces;
    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        if(fit->containsVertice(v))
            hotFaces.push_back(new Face(fit->v1, fit->v2, fit->v3));
    }
    return hotFaces;
}


list <Face*> ObjectHandler::getPeripherialFaces(Edge *e){
    list<Face*> peripherial;
    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        if(fit->containsVertice(e->vStart) && fit->containsVertice(e->vEnd))
            peripherial.push_back(&(*fit));
    }
    if(peripherial.size() > 2)
        cout << "Something gone wrong. Size: " << peripherial.size() << endl;

    return peripherial;
}

//not correct cause it copys the pointers so there are no new. 
//can be fixed with for loops
ObjectHandler* ObjectHandler::cloneObjHandler(ObjectHandler *oh){
    ObjectHandler *newOH = new ObjectHandler();
    
    newOH->triangles.assign(oh->triangles.begin(), oh->triangles.end());
    newOH->edges.assign(oh->edges.begin(), oh->edges.end());
    newOH->vertices.insert(oh->vertices.begin(), oh->vertices.end());

    cout<<"Vert: " << newOH->vertices.size() << " - " << oh->vertices.size() << endl;
    cout<<"Faces: " << newOH->triangles.size() << " - " << oh->triangles.size() << endl;
    cout<<"Edges: " << newOH->edges.size() << " - " << oh->edges.size() << endl;

    newOH->vertices.find(1)->second.index = 99;
    cout << newOH->vertices.find(1)->second.index <<endl;
    cout << oh->vertices.find(1)->second.index <<endl;


    return newOH;
    
}

Vertice* ObjectHandler::EdgeCollapse(Edge *e){
    //get neigbour faces of the edge (2)
    list<Face*> neighboorFaces = getPeripherialFaces(e);
    
    //calculate the new point
    float nx, ny, nz;
    nx = (e->vStart->x + e->vEnd->x)/2;
    ny = (e->vStart->y + e->vEnd->y)/2;
    nz = (e->vStart->z + e->vEnd->z)/2;


    vertices.insert(make_pair(vertices.size()+1, Vertice(nx, ny, nz)));
    vertices.find(vertices.size())->second.printVertice();

    //mark the old points as inactice
    e->vStart->energy = false;
    e->vEnd->energy = false;

    //remover neighbour faces from the triangles list
    cout << endl;
    list<Face*>::iterator pf_fit;
    for (pf_fit = neighboorFaces.begin(); pf_fit != neighboorFaces.end(); ++pf_fit){
        list<Face>::iterator fit;
        for (fit = triangles.begin(); fit != triangles.end(); ++fit){
            if( fit->equalFace(*pf_fit)){
                break;
            }
        }
        triangles.erase(fit);
    }

    //remove the edge from the list
    list<Edge>::iterator eit;
    for (eit = edges.begin(); eit != edges.end(); ++eit){
        if(eit->equalEdge(e)){
            edges.erase(eit);
            break;
        }
    }

    //replace in each face that contains the removed points the new one
    list<Face>::iterator fit;
    int i = 12;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        if(fit->v1->equalVertice(e->vStart) || fit->v1->equalVertice(e->vEnd)){
            fit->v1 = &vertices.find(vertices.size())->second;
            cout << "1found triangle " << i << endl;
            fit->v1->printVertice();
            cout << endl;
        }
        else if (fit->v2->equalVertice(e->vStart) || fit->v2->equalVertice(e->vEnd)){
            fit->v2 = &vertices.find(vertices.size())->second;
            cout << "2found triangle " << i << endl;
        }
        else if (fit->v3->equalVertice(e->vStart) || fit->v3->equalVertice(e->vEnd)){
            fit->v3 = &vertices.find(vertices.size())->second;
            cout << "3found triangle " << i << endl;
        }
        i++;
    }
    return &vertices.find(vertices.size())->second;
}


double ObjectHandler::HausdorffDistance(list<Face*> F1, list<Face*> F2){
    double hDist = 0;
    list<Face*>::iterator f1_it;
    for (f1_it = F1.begin(); f1_it != F1.end(); ++f1_it){
        list<Face*>::iterator f2_it;
        double localMax=0;
        for (f2_it = F2.begin(); f2_it != F2.end(); ++f2_it){
            double d1, d2, d3, dmax;
            d1  = (*f2_it)->maxDistanceFromVertice((*f1_it)->v1);
            d2  = (*f2_it)->maxDistanceFromVertice((*f1_it)->v2);
            d3  = (*f2_it)->maxDistanceFromVertice((*f1_it)->v3);
            
            dmax = maxDouble(d1, d2, d3);
            if (localMax < dmax)
                localMax = dmax;
        }
        if (hDist < localMax)
            hDist = localMax;
    }
    return hDist;
}





    // cout << triangles.size() << " ~~~> " <<  hotFaces.size() << endl;
    // list<Face*>::iterator it;
    // for (it = hotFaces.begin(); it != hotFaces.end(); ++it){
    //     cout << "Vertice: "<< endl;
    //     (*it)->v1->printVertice();
    //     cout << endl;
    //     (*it)->v2->printVertice();
    //     cout << endl;
    //     (*it)->v3->printVertice();
    //     cout << endl;
    //     cout << "----" << endl;
    // }