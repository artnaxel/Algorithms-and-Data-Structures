#pragma once

#include <stddef.h>

typedef struct node
{
    void* data;
    int priority;
    struct node* next;
} node;

typedef struct pQueue
{
    node* head;
} pQueue;

// Allocate queue
pQueue* newpQueue();

// Return true if queue is empty
int isEmptyPQueue(pQueue* queue);

// Insert data with priority
void push(pQueue* queue, void* data, int priority);

// Removes highest priority node and returns data
int pop(pQueue* queue);

// Merges priority queue b onto priority queue a
void pQueueJoin(pQueue* a, pQueue* b);

// ------------ EXTRA FUNCTIONS

// Return number of nodes in queue
int pQueueSize(pQueue* queue);

// Free queue and nodes, and execute callback for each node if not NULL
void pQueueFree(pQueue* queue, void (*dataCallback)(void*, int));

// Like pQueueFree, but doesn't free queue itself
void pQueueClear(pQueue* queue, void (*dataCallback)(void*, int));

// Get data at front of queue without removing
void* pQueueRetrieve(pQueue* queue);

// Iterate over priority queue nodes, calling dataCallback for each element
void pQueueIterate(pQueue* queue, void (*dataCallback)(void*, int));
