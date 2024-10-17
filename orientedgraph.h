/* DINCA Alexandra-Cristina - 311CD*/

#ifndef ORIENTED_GRAPH_H_
#define ORIENTED_GRAPH_H_

typedef struct ONode{
	int v, c;
    float score;
	struct ONode *next;
}ONode, *AONode;

typedef struct{
	int nn;
	AONode *adl;    // Adjancey list
}OGraphL;

OGraphL* createOrientedGraph(int numberOfNodes) {
	OGraphL *newGraph = malloc(sizeof(OGraphL));
	newGraph->nn = numberOfNodes;
	newGraph->adl = malloc(newGraph->nn * sizeof(AONode));
	for (int i = 0; i < newGraph->nn; i++) {
		newGraph->adl[i] = NULL;
	}
	return newGraph;
}

void insert_edge_list(OGraphL *G, int v1, int v2, int c)
{
    ONode *temp;
    temp = malloc(sizeof(ONode));
    temp->v = v2;
    temp->c = c;
    temp->next = G->adl[v1];
    G->adl[v1] = temp;
}

void destroyOrientedGraph(OGraphL* graph){	
	for (int i = 0; i < graph->nn; i++) {
		AONode iter = graph->adl[i];
		while (iter != NULL) {
			AONode temp = iter;
			iter = iter->next;
			free(temp);
		}
	}
	free(graph->adl);
	free(graph);
}

#endif