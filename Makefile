all:
	g++ -g main.cpp helper.cpp rawMaterial.cpp ObjectHandler.cpp 	
clean:
	rm *.o