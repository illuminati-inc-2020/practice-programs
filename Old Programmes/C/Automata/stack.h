#ifndef __MACRO_STACK_H
#define __MACRO_STACK_H

#include<stdio.h>

#ifndef MAXSTACK
#define MAXSTACK 100
#endif

#define CREATESTACK(stk) int stk##_top=-1
#define STACKUNDERFLOW(stk) ((stk##_top<0)?1:0)
#define STACKOVERFLOW(stk) ((stk##_top>=MAXSTACK)?1:0)
#define PUSH(stk,data) (stk[++stk##_top]=(STACKOVERFLOW(stk))?0:data)
#define POP(stk) ((STACKUNDERFLOW(stk))?0:stk[stk##_top--])



#endif
