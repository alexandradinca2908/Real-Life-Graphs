/* DINCA Alexandra-Cristina - 311CD*/

#ifndef QUEUE_H_
#define QUEUE_H_


// LIST
typedef struct ListNode{
	int key;
	struct ListNode *next;
	struct ListNode *prev;
}ListNode;

typedef struct List{
	ListNode* head;
}List;

typedef List Queue;

List* createList(void){
	List* newList = (List*) malloc(sizeof(List));
	newList->head = (ListNode*) malloc(sizeof(ListNode));
	newList->head->next = newList->head->prev = newList->head;
	return newList;
}
void destroyList(List* list){
	ListNode* it = list->head->next;
	while(it != list->head){
		ListNode* aux = it;
		it = it->next;
		free(aux);
	}
	free(list->head);
	free(list);
}
int isListEmpty(List *list){
	return list->head->next == list->head;
}

// QUEUE
void push(Queue* stack, int key){
	ListNode* newNode = (ListNode*) malloc(sizeof(ListNode));
	newNode->key = key;

	newNode->next = stack->head->next;
	newNode->prev = stack->head;

	stack->head->next->prev = newNode;
	stack->head->next = newNode;
}

Queue* createQueue(void){
	return createList();
}

void destroyQueue(Queue* queue){
	destroyList(queue);
}

void enqueue(Queue* queue, int key){
	push(queue,key);
}

void dequeue(Queue* queue){
	ListNode* aux = queue->head->prev;
	queue->head->prev = queue->head->prev->prev;
	queue->head->prev->next = queue->head;
	free(aux);
}

int isQueueEmpty(Queue *queue){
	return isListEmpty(queue);
}

int front(Queue* queue){
	return queue->head->prev->key;
}

#endif