#include <stdio.h>
#include "functions.h"
/*

Aleksandra Kondratjeva

*/
int main(){
    int a = 20, b = 40, c = 90;

    Queue *q = createQueue();

    enqueue(q, &a);
    enqueue(q, &b);
    enqueue(q, &c);

    //Displaying the front element
    printf("The front element is: %d\n ", *(int*)front(q));
    printf("The rear element is: %d \n", *(int*)q->rear->field);
    printf("The number of elements is: %d\n", q->count);

    if(!isEmpty(q)){
        printf("The queue isn't empty.\n\n");
    }

    dequeue(q);
    
    //After dequeue
    printf("The front element is: %d\n ", *(int*)front(q));
    printf("The rear element is: %d \n", *(int*)q->rear->field);
    printf("The number of elements is: %d\n\n", q->count);

    //Deleting the queue
    deleteQueue(q);

    //After deleting
    if(isEmpty(q)){
        printf("The queue is empty.\n\n");
    }
    return 0;
}