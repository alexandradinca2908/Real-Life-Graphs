/* DINCA Alexandra-Cristina - 311CD*/

#ifndef PRIM_H_
#define PRIM_H_

#include <limits.h>
#include "minheap.h"

int Prim(TGraphL *G, int *visited, int root, int nrLocations)
{
    int distance[G->nn];
	int parent[G->nn];
	int nodes[G->nn];

	MinHeap *Q = newQueue(G->nn);
	MinHeapNode *u = NULL;

	for (int i = 0; i < G->nn; i++) {
		distance[i] = INT_MAX;
		parent[i] = -1;
		nodes[G->nn] = -1;
	}

	distance[root] = 0;
	insert(Q, root, distance[root]);

	int index = 0;
	int ok = 0;

	while (!isEmpty(Q)) {
		u = removeMin(Q);
		visited[u->v] = 1;

		//  TRACKING ALL VISITED NODES
		for (int i = 0; i < index; i++) {
			if (nodes[i] == u->v) {
				ok = 1;
				break;
			}
		}
		if (ok == 0) {
			nodes[index] = u->v; 
			index++;
		}

		ok = 0;		

		ATNode temp = G->adl[u->v];

		while (temp != NULL) {
			if (distance[temp->v] > temp->c && visited[temp->v] == 0) {
				distance[temp->v] = temp->c;
				parent[temp->v] = u->v;
				insert(Q, temp->v, distance[temp->v]);
			}
			temp = temp->next;
		}
		free(u);
	}

	int cost = 0;
	for (int i = 0; i < index; i++) {
		cost += distance[nodes[i]];
	}

	free(Q->pos);
	free(Q->elem);
	free(Q);

	return cost;
}

#endif