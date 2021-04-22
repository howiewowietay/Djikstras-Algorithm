#ifndef GRAPH_H
#define GRAPH_H
using namespace std;

//typedef struct TAG_VERTEX {
	int vertex;
	int color;//color of vertex: in {0, 1, 2}//
	int pi;//predecessor of vertex: in {1, 2, ..., n}//

	float d;//current distance from source vertex//
	float key;
	int pos;//position in the heap array
	//char *name; //name of the POI represented by this value//
}VERTEX;


typedef struct TAG_NODE {
	int v;
	int u;
	float w;
	TAG_NODE* next;
}NODE;
typedef NODE* pNODE;


extern VERTEX *V;

pNODE* initialize(int n);


void writePath(int source, int destination, int t, VERTEX* V);
void dijkstra(int n, pNODE *A, int s, int d, int f);



#endif
