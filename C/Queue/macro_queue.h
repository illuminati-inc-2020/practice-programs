#ifndef __MACRO_QUEUE_H
#define __MACRO_QUEUE_H

#include<stdio.h>

#ifndef MAXQUEUE
#define MAXQUEUE 100
#endif

#define CREATEQUEUE(queue) int queue##_rear=-1,queue##_front=-1
#define EMPTY(queue) ((queue##_front==queue##_rear)?1:0)
#define FULL(queue) ((queue##_rear>=MAXQUEUE-1)?1:0)
#define ENQUEUE(queue,data) (queue[++queue##_rear]=data)
#define DEQUEUE(queue) (queue[++queue##_front])



#endif
