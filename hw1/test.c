#include <assert.h>
#include "functions.h"
//
int main(){
    float a = 20.3, b = 40.2, c = 90.1;

    Queue *q = createQueue();

    enqueue(q, &a);
    enqueue(q, &b);
    enqueue(q, &c);

    assert((*(float*)front(q)) == a);

    assert(isEmpty(q) == 0);
    
    assert(*(float*)q->rear->field == c);
    assert(q->count == 3);

    dequeue(q);
    assert((*(float*)front(q)) == b);
    assert(q->count == 2);

    deleteQueue(q);
    //assert(q == NULL);
    assert(isEmpty(q) == 1);

    return 0;
}