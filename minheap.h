/* DINCA Alexandra-Cristina - 311CD*/

#ifndef HEAP_H_
#define HEAP_H_

#include <stdlib.h>
#include <math.h>

typedef struct MinHeapNode
{
    int v;
    int d;
} MinHeapNode;


typedef struct MinHeap
{
    int size;
    int capacity;
    int *pos;
    MinHeapNode **elem;
} MinHeap;

typedef struct MinHeapScoreNode
{
    int v;
    float d;
} MinHeapScoreNode;


typedef struct MinHeapScore
{
    int size;
    int capacity;
    int *pos;
    MinHeapScoreNode **elem;
} MinHeapScore;

MinHeapNode* newNode(int v, int d)
{
    MinHeapNode* n =(MinHeapNode*) malloc(sizeof(MinHeapNode));
    n->v = v;
    n->d = d;
    return n;
}

MinHeapScoreNode* newScoreNode(int v, float s)
{
    MinHeapScoreNode* n =(MinHeapScoreNode*) malloc(sizeof(MinHeapScoreNode));
    n->v = v;
    n->d = s;
    return n;
}

MinHeap* newQueue(int capacity)
{
    MinHeap* h =(MinHeap*) malloc(sizeof(MinHeap));
    h->pos = (int *)malloc(capacity * sizeof(int));
    h->size = 0;
    h->capacity = capacity;
    h->elem =(MinHeapNode**) malloc(capacity * sizeof(MinHeapNode*));
    return h;
}

MinHeapScore* newScoreQueue(int capacity)
{
    MinHeapScore* h =(MinHeapScore*) malloc(sizeof(MinHeapScore));
    h->pos = (int *)malloc(capacity * sizeof(int));
    h->size = 0;
    h->capacity = capacity;
    h->elem =(MinHeapScoreNode**) malloc(capacity * sizeof(MinHeapScoreNode*));
    return h;
}

void swap(MinHeapNode** a, MinHeapNode** b)
{
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void swapByScore(MinHeapScoreNode** a, MinHeapScoreNode** b)
{
    MinHeapScoreNode* t = *a;
    *a = *b;
    *b = t;
}

void SiftDown(MinHeap* h, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < h->size && h->elem[left]->d < h->elem[smallest]->d)
      smallest = left;

    if (right < h->size && h->elem[right]->d < h->elem[smallest]->d )
      smallest = right;

    if (smallest != idx)
    {
        MinHeapNode *a = h->elem[smallest];
        MinHeapNode *b = h->elem[idx];
        h->pos[a->v] = idx;
        h->pos[b->v] = smallest;
        swap(&h->elem[smallest], &h->elem[idx]);
        SiftDown(h, smallest);
    }
}

void SiftDownByScore(MinHeapScore* h, int idx)
{
    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < h->size && h->elem[left]->d < h->elem[smallest]->d)
      smallest = left;

    if (right < h->size && h->elem[right]->d < h->elem[smallest]->d )
      smallest = right;

    if (smallest != idx)
    {
        MinHeapScoreNode *a = h->elem[smallest];
        MinHeapScoreNode *b = h->elem[idx];
        h->pos[a->v] = idx;
        h->pos[b->v] = smallest;
        swapByScore(&h->elem[smallest], &h->elem[idx]);
        SiftDownByScore(h, smallest);
    }
}

int isEmpty(MinHeap* h)
{
    return h->size == 0;
}

int isEmptyByScore(MinHeapScore* h)
{
    return h->size == 0;
}

MinHeapNode* removeMin(MinHeap* h)
{
    if (isEmpty(h))
        return NULL;
    MinHeapNode* min = h->elem[0];
    MinHeapNode* last = h->elem[h->size - 1];
    h->elem[0] = last;
    h->pos[min->v] = h->size-1;
    h->pos[last->v] = 0;
    h->size--;
    SiftDown(h, 0);
    return min;
}

MinHeapScoreNode* removeMinByScore(MinHeapScore* h)
{
    if (isEmptyByScore(h))
        return NULL;
    MinHeapScoreNode* min = h->elem[0];
    MinHeapScoreNode* last = h->elem[h->size - 1];
    h->elem[0] = last;
    h->pos[min->v] = h->size-1;
    h->pos[last->v] = 0;
    h->size--;
    SiftDownByScore(h, 0);
    return min;
}

void SiftUp(MinHeap* h, int v, int d)
{
    int i = h->pos[v];
    h->elem[i]->d = d;
    while (i && h->elem[i]->d < h->elem[(i - 1) / 2]->d)
    {   
        h->pos[h->elem[i]->v] = (i-1)/2;
        h->pos[h->elem[(i - 1) / 2]->v] = i;
        swap(&h->elem[i],  &h->elem[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    if (i && (i - 1) / 2 == (i - 2) / 2) {
        if (h->elem[i]->d < h->elem[(i - 1) / 2]->d) {
            h->pos[h->elem[i]->v] = i - 1;
            h->pos[h->elem[i - 1]->v] = i;
            swap(&h->elem[i],  &h->elem[i - 1]);
        }
    }
}

void SiftUpByScore(MinHeapScore* h, int v, float s)
{
    int i = h->pos[v];
    h->elem[i]->d = s;
    while (i && h->elem[i]->d < h->elem[(i - 1) / 2]->d)
    {   
        h->pos[h->elem[i]->v] = (i-1)/2;
        h->pos[h->elem[(i - 1) / 2]->v] = i;
        swapByScore(&h->elem[i],  &h->elem[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
    if (i && (i - 1) / 2 == (i - 2) / 2) {
        if (h->elem[i]->d < h->elem[(i - 1) / 2]->d) {
            h->pos[h->elem[i]->v] = i - 1;
            h->pos[h->elem[i - 1]->v] = i;
            swapByScore(&h->elem[i],  &h->elem[i - 1]);
        }
    }
}

int isInMinHeap(MinHeap *h, int v)
{
   if (h->pos[v] < h->size)
     return 1;
   return 0;
}

void insert(MinHeap *Q, int v, int d) {
    if (Q->size == Q->capacity) {
        Q->capacity *= 2;
        Q->elem = (MinHeapNode**) realloc(Q->elem, Q->capacity * sizeof(MinHeapNode*));
        Q->pos = (int *) realloc(Q->pos, Q->capacity * sizeof(int));
    }

    Q->elem[Q->size] = newNode(v, d);
    Q->pos[v] = Q->size;
    Q->size++;
    SiftUp(Q, v, d);
}

void insertByScore(MinHeapScore *Q, int v, float s) {
    if (Q->size == Q->capacity) {
        Q->capacity *= 2;
        Q->elem = (MinHeapScoreNode**) realloc(Q->elem, Q->capacity * sizeof(MinHeapScoreNode*));
        Q->pos = (int *) realloc(Q->pos, Q->capacity * sizeof(int));
    }

    Q->elem[Q->size] = newScoreNode(v, s);
    Q->pos[v] = Q->size;
    Q->size++;
    SiftUpByScore(Q, v, s);
}

#endif