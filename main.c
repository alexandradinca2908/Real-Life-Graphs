/* DINCA Alexandra-Cristina - 311CD*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "minheap.h"
#include "graph.h"
#include "bfs.h"
#include "prim.h"
#include "queue.h"
#include "orientedgraph.h"
#include "dijkstra.h"

#define STR_LENGTH 20

int compare(const void *a, const void *b) {
   int c = *(int*)a;
   int d = *(int*)b;
   return (c - d);
}

int allNodesVisited(int *visited, int nrLocations) {
    for (int i = 0; i < nrLocations; i++) {
        if (visited[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int unvisitedNode(int *visited, int nrLocations) {
    for (int i = 0; i < nrLocations; i++) {
        if (visited[i] == 0) {
            return i;
        }
    }
}

int main(int argc, char *argv[]) {
    //  Opening files
    FILE *in = fopen("tema3.in", "rt");
    if (in == NULL) {
        printf("ERROR: Could not open input file");
    }
    FILE *out = fopen("tema3.out", "wt");
    if (out == NULL) {
        printf("ERROR: Could not open output file");
    }

    if (strcmp(argv[1], "1") == 0) {
        //  TASK1

        //  Creating a location matrix
        int nrLocations = 0, nrRoads = 0;
        fscanf(in, "%d %d\n", &nrLocations, &nrRoads);

        char **locations = malloc(nrLocations * sizeof(char *));
        for (int i = 0; i < nrLocations; i++){
            locations[i] = malloc(STR_LENGTH * sizeof(char));
        }
        int addedLocations = 0;

        //  Initializing the graph
        TGraphL *graph = createGraph(nrLocations);

        char string1[21], string2[21];
        int cost = 0;
        int j = 0, k = 0;   //  node indexes

        for (int i = 0; i < nrRoads; i++) {
            fscanf(in, "%s %s %d\n", string1, string2, &cost);
            //  CHECKING FIRST NODE
            for (j = 0; j < addedLocations; j++) {
                if (strcmp(string1, locations[j]) == 0) {
                    break;
                }
            }
            if (j == addedLocations) {
                strcpy(locations[j], string1);
                addedLocations++;
            }
            //  CHECKING SECOND NODE
            for (k = 0; k < addedLocations; k++) {
                if (strcmp(string2, locations[k]) == 0) {
                    break;
                }
            }
            if (k == addedLocations) {
                strcpy(locations[k], string2);
                addedLocations++;
            }
            //  ADDING DATA INTO ADJ LIST
            addEdgeList(graph, j, k, cost);
        }
        //  Calculating the number of areas
        int visited[nrLocations];
        for (int i = 0; i < nrLocations; i++) {
            visited[i] = 0;
        }

        int source = 0, areas = 0;
        while (!allNodesVisited(visited, nrLocations)) {
            source = unvisitedNode(visited, nrLocations);
            bfs(graph, source, visited);
            areas++;
        }
        fprintf(out, "%d\n", areas);

        //  Calculating the minimum cost for a main road
        int *costs = malloc(areas * sizeof(int));
        for (int i = 0; i < nrLocations; i++) {
            visited[i] = 0;
        }
        for (int i = 0; !allNodesVisited(visited, nrLocations); i++) {
            source = unvisitedNode(visited, nrLocations);
            costs[i] = Prim(graph, visited, source, nrLocations);
        }
        
        qsort(costs, areas, sizeof(int), compare);
        for (int i = 0; i < areas; i++) {
            fprintf(out, "%d\n", costs[i]);
        }
        
        //  Free all
        for (int i = 0; i < nrLocations; i++){
            free(locations[i]);
        }
        free(locations);    
        destroyGraphAdjList(graph);
        free(costs);

        //  END OF TASK 1
    } else {
        //  TASK 2

        //  Creating a location matrix
        int nrLocations = 0, nrRoads = 0;
        fscanf(in, "%d %d\n", &nrLocations, &nrRoads);
        char **locations = malloc(nrLocations * sizeof(char *));
        for (int i = 0; i < nrLocations; i++){
            locations[i] = malloc(STR_LENGTH * sizeof(char));
        }
        int addedLocations = 0;

        //  Initializing the graph
        OGraphL *G = createOrientedGraph(nrLocations);

        char string1[21], string2[21];
        int cost = 0;
        int j = 0, k = 0;   //  node indexes    

        for (int i = 0; i < nrRoads; i++) {
            fscanf(in, "%s %s %d\n", string1, string2, &cost);
            //  CHECKING FIRST NODE
            for (j = 0; j < addedLocations; j++) {
                if (strcmp(string1, locations[j]) == 0) {
                    break;
                }
            }
            if (j == addedLocations) {
                strcpy(locations[j], string1);
                addedLocations++;
            }
            //  CHECKING SECOND NODE
            for (k = 0; k < addedLocations; k++) {
                if (strcmp(string2, locations[k]) == 0) {
                    break;
                }
            }
            if (k == addedLocations) {
                strcpy(locations[k], string2);
                addedLocations++;
            }
            //  ADDING DATA INTO ADJ LIST
            insert_edge_list(G, j, k, cost);
        }
        
        //  Getting the depth of each node
        int depth[nrLocations];
        for (int i = 0; i < nrLocations; i++) {
            fscanf(in, "%s ", string1);
            for (j = 0; j < addedLocations; j++) {
                if (strcmp(string1, locations[j]) == 0) {
                    break;
                }
            }
            if (j < nrLocations) {
                fscanf(in, "%d\n", &depth[j]);
            }
        }

        //  Calculating score for each edge
        for (int i = 0; i < nrLocations; i++) {
            AONode temp = G->adl[i];
            while (temp != NULL) {
                temp->score = temp->c * 1.0 / depth[temp->v];
                temp = temp->next;
            }
        }

        //  Reading the treasure weight
        int weight = 0;
        fscanf(in, "%d", &weight);

        //  Getting Island and Ship node values separately
        int island = 0, ship = 0;
        for (int i = 0; i < nrLocations; i++) {
            if (strcmp(locations[i], "Insula") == 0) {
                island = i;
            }
            if (strcmp(locations[i], "Corabie") == 0) {
                ship = i;
            }
        }

        //  Checking ship-island and island-ship paths
        int shipToIsland = -1;
        shipToIsland = dijkstra(G, ship, island);
        if (shipToIsland == INT_MAX) {
            fprintf(out, "Echipajul nu poate ajunge la insula\n");
            //  Free all
            for (int i = 0; i < nrLocations; i++){
                free(locations[i]);
            }
            free(locations);    
            destroyOrientedGraph(G);
            fclose(in);
            fclose(out);
            return 0;
        }

        int islandToShip = -1;
        islandToShip = dijkstra(G, island, ship);
        if (islandToShip == INT_MAX) {
            fprintf(out, "Echipajul nu poate transporta comoara inapoi la corabie\n");
            //  Free all
            for (int i = 0; i < nrLocations; i++){
                free(locations[i]);
            }
            free(locations);    
            destroyOrientedGraph(G);
            fclose(in);
            fclose(out);
            return 0;
        }
        
        //  Calculating best route and returning the maximum allowed weight
        int max1 = dijkstraPath(G, island, ship, locations, depth, out);
        int max2 = dijkstraPath(G, ship, island, locations, depth, out);
        
        if (compare(&max1, &max2) > 0) {
            fprintf(out, "%d\n", max2);
            max1 = max2;
        } else {
            fprintf(out, "%d\n", max1);
        }

        fprintf(out, "%d\n", weight / max1);

        //  Free all
        for (int i = 0; i < nrLocations; i++){
            free(locations[i]);
        }
        free(locations);    
        destroyOrientedGraph(G);

        //  END OF TASK 2
    }

    fclose(in);
    fclose(out);
    
    return 0;
}