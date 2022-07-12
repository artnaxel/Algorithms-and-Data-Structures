#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//Function to create an empty queue
Queue* createQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue)); //allocating memory for queue

    if (q == NULL){ //failed to create queue
        return NULL;
    }

    q->front = NULL; //empty queue
    q->rear = NULL;
    q->count = 0; //number of elements in queue
    
    return q;
}

int isEmptyQueue(Queue *q){
    if (q->front == NULL && q->rear == NULL)
        return 1;
    else
        return 0;
}

void enqueue(Queue *q, void *k){
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->field = k;
    temp->next = NULL;

    if(q->rear == NULL){ //if it's the first element in queue
        q->front = q->rear = temp;
        q->count++;
        return;
    }
    
    //Adding the node to the end of queue and changing rear
    q->rear->next = temp;
    q->rear = temp;
    q->count++;
}

void dequeue(Queue *q){
    if(q->count)
    {
        //Storing the previous front
        Node *temp = q->front;

        //Moving front one node ahead
        if(q->count > 1)
        {
            q->front = q->front->next;
        }
        else
        {
            q->front = NULL;
            q->rear = NULL;
        }
        q->count--;
       // free(temp->field);
       free(temp);
    }
}

void *front(Queue *q){
    return q->count ? q->front->field : NULL;
}

void deleteQueue(Queue *q){
    while(q -> count){
        Node *temp = q->front;
        q->front = q->front->next;
       //free(temp->field);
        free(temp);
        q->count--;

    }
    q->front = q->rear = NULL;
}
