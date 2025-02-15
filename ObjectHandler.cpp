#include <fstream> 
#include <cstring>
#include "ObjectHandler.h"
#include "rawMaterial.h"


using namespace std;

/*
    Gets the path from a simple .obj file and extrats all the
    vertices and faces
*/
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
                    cout << "Warning!!!:: Unknown value in obj:: " << objpart << endl;
                }
                objpart = strtok(NULL, " ");
            }
        }
    }
    in.close();
    return true;
}

/*
    Stores the object in the class in a .obj file in the given path
*/
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

/*
    Checks if the edge exists in the object
*/
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

/*
    Extracts all the edges from the object and stores them
    in a set like list
*/
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

/* 
    Prints the number of:
        -Vertices
        -Faces
        -Edges
    of the currenct loaded object
*/
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

/*
    Prints a simpler summary
*/
void ObjectHandler::pintSimpleSummary(){
    cout<< "~~~ Simple summary" << endl;
    cout << "Vertices: " << vertices.size() << endl;
    cout << "Faces: " << triangles.size() << endl;
    cout << "Edges: " << edges.size() << endl;
    cout << "~~~~~" << endl;

}

/*
    Given an edge it returns a list of faces that are connected
    with this edge. However it creates new faces in order the original object do 
    not get edited
*/
list<Face*> ObjectHandler::getHotArea(Edge *e){
    list<Face*> hotFaces;

    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        if(fit->containsVertice(e->vStart) || fit->containsVertice(e->vEnd))
            hotFaces.push_back(new Face(fit->v1, fit->v2, fit->v3));
    }
    return hotFaces;
}

/*
    Given a vertice it returns a list of faces that are connected with
    that vertice
*/
list<Face*> ObjectHandler::getHotArea(Vertice *v){
    list<Face*> hotFaces;
    list<Face>::iterator fit;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        if(fit->containsVertice(v))
            hotFaces.push_back(new Face(fit->v1, fit->v2, fit->v3));
    }
    return hotFaces;
}

/*
    It returns the hot area of the edge. However the faces now are the one of
    the current object
*/
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

/*
    Clones the current object. However it does not makes new faces so its not trustworthy!
*/
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

/*
    Implements the edge collapse algorith. It gets an edge as input,
    it gets all the peripherials faces, calculates the average point of the edge
    and then sets all the faces that are connected with the edge to point at the new
    average vertice.
*/
Vertice* ObjectHandler::EdgeCollapse(Edge *e){
    //get neigbour faces of the edge (2)
    list<Face*> neighboorFaces = getPeripherialFaces(e);
    
    //calculate the new point
    float nx, ny, nz;
    nx = (e->vStart->x + e->vEnd->x)/2;
    ny = (e->vStart->y + e->vEnd->y)/2;
    nz = (e->vStart->z + e->vEnd->z)/2;
    vertices.insert(make_pair(vertices.size()+1, Vertice(nx, ny, nz)));

    //mark the old points as inactice
    e->vStart->energy = false;
    e->vEnd->energy = false;

    //remover neighbour faces from the triangles list
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

    list<Edge>::iterator eit;
    //remove the edge from the list
    for (eit = edges.begin(); eit != edges.end(); ++eit){
        if(eit->equalEdge(e)){
            edges.erase(eit);
            break;
        }
    }

    //update all the edges
    for (eit = edges.begin(); eit != edges.end(); ++eit){
        if(eit->vStart->equalVertice(e->vStart)){
            eit->vStart = &vertices.find(vertices.size())->second;
        }
        if(eit->vEnd->equalVertice(e->vEnd)){
            eit->vEnd = &vertices.find(vertices.size())->second;
        }
    }

    //replace in each face that contains the removed points the new one
    list<Face>::iterator fit;
    int i = 12;
    for (fit = triangles.begin(); fit != triangles.end(); ++fit){
        if(fit->v1->equalVertice(e->vStart) || fit->v1->equalVertice(e->vEnd)){
            fit->v1 = &vertices.find(vertices.size())->second;
        }
        else if (fit->v2->equalVertice(e->vStart) || fit->v2->equalVertice(e->vEnd)){
            fit->v2 = &vertices.find(vertices.size())->second;
        }
        else if (fit->v3->equalVertice(e->vStart) || fit->v3->equalVertice(e->vEnd)){
            fit->v3 = &vertices.find(vertices.size())->second;
        }
        i++;
    }
    return &vertices.find(vertices.size())->second;
}

/*
    Calculates the Hausdroff Distanse between two list with faces in a 3D space.
    Those lists are the faces that are connected before and after of an edge collapse
*/
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
    // if(hDist == 0){
    //     cout<< hDist <<"!" << F1.size() << "~~" << F2.size() << endl;
    //     exit(1);
    // }
    return hDist;
}


/*
    Gets an edge, finds hot area, collpases is, and counts the worth of the collapse
*/
double ObjectHandler::collapseValue(Edge *e){
    list<Face*> oldSceme = getHotArea(e);
    list<Face*> newSceme;

    float nx, ny, nz;
    nx = (e->vStart->x + e->vEnd->x)/2;
    ny = (e->vStart->y + e->vEnd->y)/2;
    nz = (e->vStart->z + e->vEnd->z)/2;
    Vertice *vn = new Vertice(nx,ny, nz);

    list<Face*>::iterator fit;
    for (fit=oldSceme.begin(); fit!=oldSceme.end(); fit++){
        if((*fit)->containsVertice(e->vStart) && (*fit)->containsVertice(e->vEnd)){
            continue; //ingore them 
        }
            
        Face *nf;
        if((*fit)->v1->equalVertice(e->vStart) || (*fit)->v1->equalVertice(e->vEnd))
            nf = new Face(vn, (*fit)->v2, (*fit)->v3);
        if((*fit)->v2->equalVertice(e->vStart) || (*fit)->v2->equalVertice(e->vEnd))
            nf = new Face((*fit)->v1, vn, (*fit)->v3);
        if((*fit)->v3->equalVertice(e->vStart) || (*fit)->v3->equalVertice(e->vEnd))
            nf = new Face((*fit)->v1, (*fit)->v2, vn);

        newSceme.push_back(nf);
    } 

    double distance = HausdorffDistance(oldSceme, newSceme);
    // cout << "old: " << oldSceme.size() << " new:: " << newSceme.size() << " Distance :: " << distance << endl;
    cleanF(oldSceme);
    cleanF(newSceme);
    delete(vn);
    return distance;
}