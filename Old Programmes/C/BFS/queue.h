#ifndef __MACRO_QUEUE_H
#define __MACRO_QUEUE_H

#include<stdio.h>

#ifndef MAXQUEUE
#define MAXQUEUE 100
#endif

#define CREATEQUEUE(queue) int queue##_rear=-1,queue##_front=-1
#define EMPTY(queue) ((queue##_front==queue##_rear)?1:0)
#define FULL(queue) ((queue##_rear>=MAXQUEUE-1)?1:0)
#define INSERT(queue,data) (queue[++queue##_rear]=data)
#define DELETE(queue) (queue[++queue##_front])
#define REAR(queue) (queue##_rear)
#define FRONT(queue) (queue##_front)

#endif
