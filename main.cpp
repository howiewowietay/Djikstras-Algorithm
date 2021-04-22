#include "graph.h"
#include "heap.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace std;

VERTEX* V;

int main(int argc, char* argv[])
{
    FILE* ifile;
    
    pNODE* A;
    pNODE node;

    char word[256];
    char word2[256];
    int n, m, directed_graph, i;
    int s, s_new, t, t_new, source, source_new, destination, destination_new;
    int u, v, edge_id, flag, flag_new;
    float w;

    int v_scanf, v_fscanf;
    int r_value;

    if (argc != 3)
    {
        printf("Command Format: %s <graph_file> <direction>\n", argv[0]);
        exit(1);
    }
    if (0 == strcmp(argv[2], "directed\0"))
    {
        directed_graph = 1;
    }
    if (0 == strcmp(argv[2], "undirected\0"))
    {
        directed_graph = 0;
    }

    //open network file for reading

    ifile = fopen(argv[1], "r");
    if (!ifile)
    {
        printf("Error: cannot open file for reading.\n");
    }

    //read in n=|V| and m = |E|
    v_fscanf = fscanf(ifile, "%d%d", &n, &m);
    if (v_fscanf < 2)
    {
        exit(1);
    }

     // allocate memory for adjacency lists
    A = new pNODE[n + 1];
    if (!A)
    {
        printf("Error: calloc failure.\n");
        exit(1);
    }

    // read in the edges and construct adjacency lists
    for (i = 1; i <= m; i++)
    {
        v_fscanf = fscanf(ifile, "%d%d%d%f", &edge_id, &u, &v, &w);
        if (v_fscanf < 4)
        {
            printf("Error: fscanf returns %d.\n", v_fscanf);
            exit(1);
        }
        node = new NODE;
        if (!node)
        {
            printf("Error: malloc failure.\n");
            exit(1);
        }
        //node->u = u;
        node->v = v;
        node->w = w;
        node->next = A[u];
        A[u] = node;

        if (!directed_graph) 
        {
            //BGN For undirected graphs
            node = new NODE;
            if (!node)
            {
                printf("Error: malloc failure.\n");
                exit(1);
            }
            node->u = v;
            node->v = u;
            node->w = w;
            node->next = A[v];
            A[v] = node;
            //end for undirectedGraphs
        }
    }

    /*
   // BGN check the adjacency lists
   for (i = 1; i <= n; i++)
   {
      printf("Node &d:", i);
   }
   printf("\n");
   
   // END check the adjacency lists
   */

    fclose(ifile);

    source = 0;
    destination = 0;

    //BGN query part...

    while (1)
    {
        r_value = nextCommand(word);
        if (!r_value)
        {
            //printf("ErrorGLX: EOF\n");
            continue;
        }

        if (0 == strcmp(word, "stop"))
        {
            //Stop
            printf("Query: %s\n", word);
            break;
        }

        if (0 == strcmp(word, "find"))
        {
            //Find
            v_scanf = scanf("%d%d%d", &source_new, &destination_new, &flag_new);
            if (v_scanf != 3)
            {
                // printf("ErrorGLX3: wrong return value for scanf\n");
                continue;
            }
            else
            {
                printf("Query: %s %d %d %d\n", word, source_new, destination_new, flag_new);
                if (source_new < 1 || source_new > n || flag_new < 0 || flag_new > 1)
                {
                    printf("Error: invalid find query\n");
                }
                else
                {
                    source = source_new;
                    destination = destination_new;
                    flag = flag_new;
                    V = initializeVertex(n);
                    if (!V)
                    {
                        printf("Error: calloc failure.\n");
                        exit(1);
                    }
                    dijkstra(n, A, source, destination, flag);
                }
            }
        }
        else if (0 == strcmp(word, "write"))
        {
            r_value = nextCommand(word2);
            if (!r_value)
            {
                //printf("ErrorGLX4: EOF\n");
                continue;
            }
            if (0 == strcmp(word2, "path"))
            {
                v_scanf = scanf("%d%d", &s_new, &t_new);
                if (v_scanf != 2)
                {
                    // printf("ErrorcwGLX5: wrong return value for scanf\n");
                    continue;
                }
                else
                {
                    printf("Query: %s %s %d %d\n", word, word2, s_new, t_new);
                    if (source == 0)
                    {
                        printf("Error: no path computation done\n");
                    }
                    else if (s_new != source || t_new == s_new || t_new < 1 || t_new > n)
                    {
                        printf("Error: invalid source destination pair\n");
                    }
                    else
                    {
                        s = s_new;
                        t = t_new;
                        writePath(s, destination, V, t, n);
                        //printPath(n, source, destination, s, t);
                    }
                }
            }
        }
        else
        {
            //printf("ErrorGLX: Bad input\n");
            continue;
        }
    } //end while
    delete(A);
    delete(V);
}
