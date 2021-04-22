EXEC = dijkstra
CC = g++
CFLAGS = -c -Wall

$(EXEC) :main.o util.o graph.o heap.o 
	$(CC) -o $(EXEC) main.o util.o graph.o heap.o

main.o :main.cpp
	$(CC) $(CFLAGS) main.cpp
	
util.o  :util.h util.cpp
	$(CC) $(CFLAGS) util.cpp

heap.o :heap.h heap.cpp
	$(CC) $(CFLAGS) heap.cpp

graph.o :graph.h graph.cpp
	$(CC) $(CFLAGS) graph.cpp
		
clean:
	rm *.o

