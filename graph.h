/* DINCA Alexandra-Cristina - 311CD*/

#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct TNode{
	int v, c;
	struct TNode *next;
}TNode, *ATNode;

typedef struct{
	int nn;
	ATNode *adl;    // Adjancey list
}TGraphL;

TGraphL* createGraph(int numberOfNodes) {
	TGraphL *newGraph = malloc(sizeof(TGraphL));
	newGraph->nn = numberOfNodes;
	newGraph->adl = malloc(newGraph->nn * sizeof(ATNode));
	for (int i = 0; i < newGraph->nn; i++) {
		newGraph->adl[i] = NULL;
	}
	return newGraph;
}

void addEdgeList(TGraphL* graph, int v1, int v2, int cost) {
	ATNode v1Node = malloc(sizeof(TNode)), v2Node = malloc(sizeof(TNode));
	ATNode temp1, temp2;
	v1Node->v = v1;
    v1Node->c = cost;
	v2Node->v = v2;
    v2Node->c = cost;

	temp1 = graph->adl[v1];
	temp2 = graph->adl[v2];

	graph->adl[v1] = v2Node;
	v2Node->next = temp1;
	graph->adl[v2] = v1Node;
	v1Node->next = temp2;	
}

void destroyGraphAdjList(TGraphL* graph){	
	for (int i = 0; i < graph->nn; i++) {
		ATNode iter = graph->adl[i];
		while (iter != NULL) {
			ATNode temp = iter;
			iter = iter->next;
			free(temp);
		}
	}
	free(graph->adl);
	free(graph);
}

#endif