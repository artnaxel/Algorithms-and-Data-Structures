#include <stdlib.h>
#include "pqueue.h"

pQueue* newpQueue()
{
    pQueue* queue = malloc(sizeof(pQueue));
    if (!queue) {
        return NULL;
    }

    queue->head = NULL;
    return queue;
}

int isEmptyPQueue(pQueue* queue)
{
    return queue == NULL || queue->head == NULL;
}

void push(pQueue* queue, void* data, int priority)
{
    if (!queue)
        return;

    node* new = malloc(sizeof(node));
    if (!new)
        return;

    new->data = data;
    new->priority = priority;

    // If head doesn't exist or is lower priority, set new node as head
    if (!queue->head || new->priority > queue->head->priority)
    {
        new->next = queue->head;
        queue->head = new;
        return;
    }

    // Search for location to insert node
    node* iter = queue->head;
    while(iter->next != NULL && priority <= iter->next->priority)
        iter = iter->next;

    new->next = iter->next;
    iter->next = new;
}

// Remove element with highest priority
int pop(pQueue* queue)
{
    // if (!queue || queue->head == NULL)
    //     return NULL;

    int priority =  queue->head->priority;
    node* old = queue->head;

    if (queue->head->next != NULL)
        queue->head = queue->head->next;
    else
        queue->head = NULL;

    free(old);
    return priority;
}

void pQueueJoin(pQueue* a, pQueue* b)
{
    if (!a || !b || !b->head)
        return;

    if (!a->head && b->head)
    {
        a->head = b->head;
    }
    else
    {
        // Change a->head to b->head if b->head has higher priority
        if (b->head->priority > a->head->priority)
        {
            node* node = b->head;
            b->head = b->head->next;

            node->next = a->head;
            a->head = node;
        }

        for(node *itA = a->head, *itB = b->head; itB != NULL; )
        {
            // Find where to insert itB
            while(itA->next != NULL && itA->next->priority >= itB->priority)
                itA = itA->next;

            // If itA ends, attach the rest of itB onto it
            if (itA->next == NULL)
            {
                itA->next = itB;
                break;
            }

            // Save current node and insert it
            node* node = itB;
            itB = itB->next;

            node->next = itA->next;
            itA->next = node;
        }
    }

    b->head = NULL;
}

// ------------ EXTRA FUNCTIONS
int pQueueSize(pQueue* queue)
{
    if (!queue || !queue->head)
        return 0;

    int size = 0;
    for(node* it = queue->head; it != NULL; it = it->next)
        ++size;

    return size;
}

void pQueueFree(pQueue* queue, void (*dataCallback)(void*, int))
{
    if (!queue)
        return;

    pQueueClear(queue, dataCallback);

    free(queue);

}

void pQueueClear(pQueue* queue, void (*dataCallback)(void*, int))
{
    if (!queue || !queue->head)
        return;

    for(node* next = queue->head; next != NULL;)
    {
        if (dataCallback != NULL)
            dataCallback(next->data, next->priority);

        node* prev = next;
        next = next->next;
        free(prev);
    }

    queue->head = NULL;
}

void* pQueueRetrieve(pQueue* queue)
{
    if (!queue || !queue->head)
        return NULL;

    return queue->head;
}

void pQueueIterate(pQueue* queue, void (*dataCallback)(void*, int))
{
    if (!queue || !queue->head || !dataCallback)
        return;

    for(node* next = queue->head; next != NULL; next = next->next)
    {
        dataCallback(next->data, next->priority);
    }
}
