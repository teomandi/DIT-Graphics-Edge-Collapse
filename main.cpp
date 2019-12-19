#include <fstream> //to open and read file
#include <iostream>
#include "helper.h"
#include "ObjectHandler.h"

using namespace std;



int main() {
    string objfile = "obj/myObj.obj";
    // string objfile = "obj/teapot.obj";

    ObjectHandler* oHandler= new ObjectHandler();
    oHandler->loadObject(objfile);
    oHandler->extractEdges();
    oHandler->printSummary();
    // oHandler->storeObject("obj/new.obj");

    return 0;
}