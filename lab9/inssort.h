#ifndef __INTX_H__
#define __INTX_H__

#include <stdbool.h>
#include <stdlib.h>

void inssort (void *base, size_t nelem, size_t size,
              int (*compar) (const void *, const void *));


#endif

