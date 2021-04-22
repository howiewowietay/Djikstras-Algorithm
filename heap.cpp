#include <iostream>
#include <string>
#include <limits.h>
#include <limits>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"
#include "graph.h"
#include <tgmath.h>
#include <array>
#define heap_cpp
using namespace std;


FILE* ifile, * ofile;

HEAP* initializeHeap(int n)
{
    //Create an object of type HEAP
	HEAP* heap;

	heap = new HEAP; /* Dynamic Memory Allocation*/
	
	//Initalize size and max capacity

	heap->capacity = n;

	heap->size = 0;

	heap->H = new pElement[n + 1]; /* Dynamic Memory Allocation*/

	return heap;

}

VERTEX* initializeVertex(int n)
{
    
	VERTEX* V;
	
	V = new VERTEX[n + 1];
	return V;
}

//Utility function to swap the keys
void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void minHeapify(HEAP* H, int i)//Moving Down 
{
    //Call nodes
	int smallest;
	int left = 2 * i;
	int right = 2 * i + 1;

	if (left <= H->size && H->H[left]->key < H->H[i]->key)
	{
		smallest = left;
	}
	else
	{
	    //Set current smallest index
		smallest = i;
	}

	if (right <= H->size && H->H[right]->key < H->H[smallest]->key)
	{
		smallest = right;
	}

	if (smallest != i)
	{
		int x = H->H[i]->key;
		H->H[i]->key = H->H[smallest]->key;
		H->H[smallest]->key = x;
		swap(H->H[i]->vertex, H->H[smallest]->vertex);
		swap(H->H[i]->key, H->H[smallest]->key);
		swap(H->H[i]->pos, H->H[smallest]->pos);
		//Recursive method to heapify a subtree with the root at given index
		minHeapify(H, smallest);
	}
}

void writePath(int source, int destination, VERTEX* V, int t, int n)
{
	int i = 1;
	int arr[n + 1];
	if (V[t].color == 0)
	{

		if (destination < 1 || destination > n || t == destination)
		{
			printf("No %d-%d path exists.\n", source, t);
			return;
		}
		else
		{
			printf("No %d-%d path has been computed.\n", source, t);
		}
		return;
	}
	else if (V[t].color == 1)
	{
		printf("Path not known to be shortest: <%d", source);
	}
	else if (V[t].color == 2)
	{
		printf("Shortest path: <%d", source);
	}

	int temp = t;

	while (temp != source)
	{
		arr[i] = temp;
		temp = V[temp].pi; 
		i++;
	}
	for (int index = i - 1; index != 0; index--)
	{
		printf(", %d", arr[index]);
	}
	printf(">\n");
	printf("The path weight is: %12.4f\n", V[t].key);
}

int extractMin(HEAP* heap)// Delete Min
{
	if (heap->size < 1)
	{
		cout << "Error: heap empty" << endl;
		return 0;
	}
	int min = heap->H[1]->vertex;
	heap->H[1] = heap->H[heap->size];
	heap->size--;
	minHeapify(heap, 1);
	//printf("Deleted key: %d\n", min);
	return min;
}

//decreases the key of heap->H[index] to value
int decreaseKey(HEAP* heap, int pos, float newKey)
{
	if (pos == 0 || pos>heap->size || newKey >= heap->H[pos]->key)
	{
		return 1;
	}
	heap->H[pos]->key = newKey;
	MovingUp(heap, pos);
	return 0;
}

void MovingUp(HEAP* heap, int pos)
{
	
	int parent;
	pElement temp;
	// printf("BGN MovingUP\n");
	parent = floor(pos / 2);
	if (pos > 1 && heap->H[pos]->key < heap->H[parent]->key)
	{
		temp = heap->H[pos];
		heap->H[pos] = heap->H[parent];
		heap->H[parent] = temp;
		heap->H[pos]->pos = pos;
		heap->H[parent]->pos = parent;
		MovingUp(heap, parent);
	}
	//printf("END MovingUp\n");
}

int heapInsert(HEAP* heap, pElement item)
{
	if (heap->size >= heap->capacity)
	{
		printf("Error in HeapInsert: Heap full...\n");
		return 1;
	}
	//Set size of new heap
	heap->size++;
	heap->H[heap->size] = item;
	heap->H[heap->size]->pos = heap->size; // ADDED
	
	MovingUp(heap, heap->size);
	return 0;

