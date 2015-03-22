#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inssort.h"


void inssort(void *base, size_t nelem, size_t size,
	int(*compare)(const void *, const void *)) {  

   
   for(int sorted = 1; sorted < nelem; ++sorted) {
      int slot = sorted;
      void *copyAdd = (char*)base + sorted * size;
      char *string = malloc(size);

      memcpy(string, copyAdd, size); 

      for(; slot > 0; --slot) {
	 int cmp = compare((char*)base + slot * size , (char*)base + (slot - 1) * size);
 	 if(cmp > 0) break;
	 memcpy((char*)base + slot * size, (char*)base + (slot - 1) * size, size);
      }

      memcpy((char*)base + slot * size, string, size);
      free(string);
    }
   
   
 
}
