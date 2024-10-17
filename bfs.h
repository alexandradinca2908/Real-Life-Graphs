/* DINCA Alexandra-Cristina - 311CD*/

#ifndef BFS_H_
#define BFS_H_

#include "graph.h"
#include "queue.h"

void bfs(TGraphL* graph, int s, int *visited) {
	Queue *q = createQueue();
	enqueue(q, s);
	visited[s] = 1;

	ATNode temp;
	int current = 0;
	while (!isQueueEmpty(q)) {
		current = front(q);
		dequeue(q);
		temp = graph->adl[current];
		while (temp != NULL) {
			if (visited[temp->v] == 0) {
				enqueue(q, temp->v);
				visited[temp->v] = 1;
			}
			temp = temp->next;
		}
	}

	destroyQueue(q);
}

#endif