#include <iostream>
#include <limits.h>
#include <limits>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "graph.h"
#include <string>
#include <tgmath.h>
using namespace std;


/*
extern VERTEX *V;

void printPath(int n, int source, int destination, int s, int t)
{
    PATH *pPATH;
    PATH *pNode;
    int u, v;
    
    if (V[t].color == 0)
    {
        if (destination < 1 || destination > n || t == destination)
        {
            printf("No %d-%d path exists.\n", s, t);
            return;
        }else
        {
            printf("No %d-%d path has been computed.\n", s, t);
            return;
        }
    }
        else if (V[t].color == 1)
        {
            printf("Path not known to be shortest: <%d", s);
        }
        else if (V[t].color == 2)
        {
            printf("Shortest path: <%d", s);
        }
        
        
        //push onto stack
        pNode = (PATH *) malloc(sizeof(PATH));
        pNode->vertex = t;
        pNode->next = NULL;
        pPATH = pNode;
        v = pNode->vertex;
        while (V[v].pi){
            u = V[v].pi;
            pNode = (PATH *) malloc(sizeof(PATH));
            pNode->vertex = u; pNode->next = pPATH;
            pPATH = pNode;
            v = pNode->vertex;
        }
        
        pNode = pPATH;
        pPATH = pPATH->next;
        free(pNode);
        
        while (pPATH)
        {
            pNode = pPATH;
            printf(", %d", pNode->vertex);
            pPATH = pPATH->next;
            free(pNode);
        }
        printf(">\n");
        printf("the path weight is: %12.4f\n", V[t].key);
    }
*/

//dijstras
void dijkstra(int n, pNODE* A, int s, int d, int f)
{
/*
    pNODE node;
    HEAP *heap;
    ELEMENT *element;
    
    int u, v, i;
    float w;
    
    int pos;
    int count_Heapify;
    
    for (i=1; i<=n; i++)
    {
        V[i].color = 0;
        V[i].pi = 0;
    }
    V[s].dist = 0;
    V[s].color = 1;
    
    heap = heapInit(n);
    element = (ELEMENT *) malloc(sizeof(ELEMENT));
    element->vertex = s;
    element->key = 0;
    HeapInsert(heap, element); */


	HEAP* heap;
	int u, v;
	float w;
	ELEMENT* Vertex;

	ELEMENT* SRCel;

	for (int i = 1; i <= n; i++)
	{
		V[i].color = 0; //color white
		V[i].pi = 0;
		V[i].key = std::numeric_limits<double>::infinity();
	}

	V[s].color = 1; //color grey
	V[s].pos = 1;
	V[s].key = 0;

	heap = initializeHeap(n);

	SRCel = new ELEMENT; 
	SRCel->vertex = s;
	SRCel->key = V[s].key;

	heapInsert(heap, SRCel); 

	if (f == 1)
	{
		printf("Insert vertex %d, key=%12.4f\n", s, SRCel->key);
	}


	while (heap->size > 0)
	{
        //element = DeleteMin(heap, &flag, &count_Heapify);
		u = extractMin(heap);
		if (f == 1)
		{
		    //print deletion informaiton
			printf("Delete vertex %d, key=%12.4f\n", u, V[u].key);
		}
        //u = element->vertex;
        //V[u].color = 2;
        //if (element->vertex == t)
        
		V[u].color = 2; //color black

		if (u == d)
		{
			return;
		}

		pNODE node = NULL;
		node = A[u];

		while (node)
		{
			v = node->v;
			w = node->w;

			if (V[v].color == 0)
			{

				V[v].color = 1; //color gray
				//printf("V[%d].color to 1\n", v);
				V[v].pi = u;
				V[v].key = V[u].key + w;

				Vertex = new VERTEX();
				Vertex->vertex = v;
				Vertex->key = V[v].key;
				heapInsert(heap, Vertex);

				if (f == 1)
				{

					printf("Insert vertex %d, key=%12.4f\n", v, V[v].key);
				}
			}
			//relax
			else if (V[v].key > V[u].key + w)
			{
				float pastKey = V[v].key;
				V[v].key = V[u].key + w;
				V[v].pi = u;

				decreaseKey(heap, V[v].pos, V[v].key);

				if (f == 1)
				{
					printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", v, pastKey, V[v].key);
				}
			}
			node = node->next; //increment
		}
	}
	delete heap->H;
	delete heap;
	return;
}