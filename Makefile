all: Main.o Edge.o Vertex.o 
		g++ -g -Wall Main.o Edge.o Vertex.o -o dijkstra

Edge.o: Edge.h Edge.cpp
		g++ -g -Wall -c Edge.cpp

Vertex.o: Vertex.h Vertex.cpp	
		g++ -g -Wall -c Vertex.cpp

Main.o: Main.cpp
		g++ -g -Wall -c Main.cpp

clean:
	rm *~ *.o int -v
