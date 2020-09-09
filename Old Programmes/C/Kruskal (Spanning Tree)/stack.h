#ifndef __MACRO_STACK_H
#define __MACRO_STACK_H

#include<stdio.h>

#ifndef MAXSTACK
#define MAXSTACK 100
#endif

#define CREATESTACK(stk) int stk##_top=-1
#define UNDERFLOW(stk) ((stk##_top<0)?1:0)
#define OVERFLOW(stk) ((stk##_top>=MAXSTACK-1)?1:0)
#define PUSH(stk,data) (stk[++stk##_top]=data)
#define POP(stk) (stk[stk##_top--])
#define TOP(stk) (stk##_top)

#endif
