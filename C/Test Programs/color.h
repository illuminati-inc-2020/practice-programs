#ifndef __COLOR_H
#define __COLOR_H

#include <stdio.h>

#ifdef COLOR_ENABLE
enum {RED=0,GRN,YLO,BLU,CYN,PNK,WHT};
#define col(n) printf("\e[%d;1m",n+31);
#else
#define col(n)
#warning "color.h : Define COLOR_ENABLE to enable color"
#endif

#endif


