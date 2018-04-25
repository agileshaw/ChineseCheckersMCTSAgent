
#ifndef _NODEH_
#define _NODEH_

typedef struct Node {
	void* data;
	struct Node* next;
}Node;

struct Queue {
	Node* first;
	Node* last;
	int count;
};

/*
 * Purpose: create a new empty Queue struct
 * Parameters: none
 * Return value: a pointer of a Queue struct
 */
struct Queue* createQueue();

/*
 * Purpose: add a new Node in the rear of a Queue struct
 * Parameters: queue - a pointer referencing to a Queue struct pointer
 				new - a void type of data
 * Return value: none
 */
void enqueue(struct Queue** queue, void* new);

/*
 * Purpose: detach and return the first Node in a Queue struct
 * Parameters: queue - a pointer referencing a Queue struct
 * Return value: return a void type of data pointer
 */
void* dequeue(struct Queue* queue);

/*
 * Purpose: free the memory allocated in a Node struct
 * Parameters: 
 * Return: 
 */
void destroyNode(struct Queue* queue);

/*
 * Purpose: destroy the Queue struct and free free the memory allocated inside
 * Parameters: queue - a pointer referencing a Queue struct
 * Return value: none
 */
void destroyQueue(struct Queue* queue);

#endif