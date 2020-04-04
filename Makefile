all:
	g++ -g main.cpp helper.cpp rawMaterial.cpp ObjectHandler.cpp -o edgeCollapse
clean:
	rm *.o