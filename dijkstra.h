/* DINCA Alexandra-Cristina - 311CD*/

#ifndef DIJKSTRA_H_
#define DIJKSTRA_H_

#include "minheap.h"
#include "queue.h"
#include "orientedgraph.h"

int dijkstra(OGraphL *G, int s, int dest)
{
    int visited[G->nn];
    int distance[G->nn];
	for (int i = 0; i < G->nn; i++) {
		visited[i] = 0;
        distance[i] = INT_MAX;
	}
	visited[s] = 1;
	distance[s] = 0;

	MinHeap *Q = newQueue(G->nn);
	MinHeapNode *u = NULL;
	insert(Q, s, 0);

	AONode temp = G->adl[s];

	while (!isEmpty(Q)) {
		u = removeMin(Q);
		visited[u->v] = 1;
		temp = G->adl[u->v];
		while (temp != NULL) {
			if (!visited[temp->v] && distance[temp->v] > (distance[u->v] + temp->c)) {
				distance[temp->v] = distance[u->v] + temp->c;
				insert(Q, temp->v, temp->c);
			}
			temp = temp->next;
		}
        free(u);
	}

    free(Q->pos);
	free(Q->elem);
	free(Q);

	return distance[dest];
}

int dijkstraPath(OGraphL *G, int s, int dest, char **locations, int *depth, FILE *out) {
	//  Declaring necessary data
    int visited[G->nn];
    int distance[G->nn];
    int parent[G->nn];
    float score[G->nn];
	for (int i = 0; i < G->nn; i++) {
		visited[i] = 0;
        distance[i] = INT_MAX;
        score[i] = INT_MAX;
        parent[i] = -1;
	}
	visited[s] = 1;
	distance[s] = 0;
    score[s] = 0;

	MinHeapScore *Q = newScoreQueue(G->nn);
	MinHeapScoreNode *u = NULL;
	insertByScore(Q, s, 0);

	AONode temp = G->adl[s];

	//  Going through the graph, starting with root
	while (!isEmptyByScore(Q)) {
		u = removeMinByScore(Q);
		visited[u->v] = 1;
		temp = G->adl[u->v];
		while (temp != NULL) {
			if (!visited[temp->v] && score[temp->v] > (score[u->v] + temp->score)) {
                score[temp->v] = score[u->v] + temp->score;
				distance[temp->v] = distance[u->v] + temp->c;
                parent[temp->v] = u->v;
				insertByScore(Q, temp->v, temp->score);
				for (int i = 0; i < Q->size; i++) {
					printf("%f ", Q->elem[i]->d);
				}
				printf("\n");
			}
			temp = temp->next;
		}
        free(u);
	}

    //  BUILDING THE PATH
    List *path = createList();
    int node = dest;

    while (node != -1) {
        push(path, node);
        node = parent[node];
    }

    ListNode *iter = path->head->next;

    //  PRINTING THE ISLAND-SHIP DETAILS
	if (strcmp(locations[s], "Insula") == 0) {
		//  Path
		while (iter != path->head) {
			int index = iter->key;
			fprintf(out, "%s", locations[index]);
			if (iter->next != path->head) {
				fprintf(out, " ");
			}
			iter = iter->next;
		}
		//  Path distance
		fprintf(out, "\n%d\n", distance[dest]);
	}
    

    //  CALCULATING BOAT WEIGHT
    iter = path->head->next;
	int min = INT_MAX;

	while (iter->next->next != path->head) {
		temp = G->adl[iter->key];
		while (temp != NULL && temp->v != iter->next->key) {
			temp = temp->next;
		}
		
		if (depth[temp->v] < min) {
			min = depth[temp->v];
		}
		iter = iter->next;
	}

    destroyList(path);

    free(Q->pos);
	free(Q->elem);
	free(Q);

	return min;
}

#endif