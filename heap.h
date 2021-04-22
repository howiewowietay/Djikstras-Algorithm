#ifndef HEAP_H
#define HEAP_H 1
#include <stdio.h>
#include "graph.h"
using namespace std;

typedef VERTEX ELEMENT;
typedef VERTEX* pElement;


//typedef struct TAG_ELEMENT{
    //float key;
    //int vertex;
//}ELEMENT;


typedef struct TAG_HEAP {

	int capacity;   //max size of the heap 
	int size;   //current size of the heap
	pElement* H;   //pointer to pointers to elements

}HEAP;


void writePath(int source, int destination, VERTEX* V, int t, int n);

HEAP* initializeHeap(int n);//Sets the declaration of heapInit

VERTEX* initializeVertex(int n);//vertex

void MovingUp(HEAP* heap, int pos);// function moving up

int heapInsert(HEAP* H, VERTEX* item);//Function that inserts an object of type ELEMENT pointed to by element into the heap pointed to by heap.

int extractMin(HEAP* H);// which deletes the minimum element from the heap pointed to by heap.

int decreaseKey(HEAP* H, int pos, float newKey);//Function that decreases the key of the heap

void minHeapify(HEAP* H, int index);//movingdown

#endif