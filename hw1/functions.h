#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

/* Linked list to store queue */
typedef struct Node {
    void *field; //value
    struct Node *next; //pointer to the next element
} Node;

/* The *front stores the first node, and the *rear stores the last */
typedef struct Queue{
    int count; //size of queue
    Node *front, *rear;
} Queue;

/* Function to create an empty queue */
Queue* createQueue(); 

/* Function to check if queue is empty */
int isEmpty(Queue *q);

/* Function to add a new element to queue */
void enqueue(Queue *q, void *k);

/* Function to remove an element from queue */
void dequeue(Queue *q);

/* Function to get the data of front element */
void *front(Queue *q);

/* Function to delete the queue */
void deleteQueue(Queue *q);

#endif