#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inssort.h"

int compare (const void *this, const void *that) {
   const double *thisdoub = (const double*) this;
   const double *thatdoub = (const double*) that;
   return *thisdoub - *thatdoub;
}

int main (void) {
   double array[1000];
   int index = 0;
   
   for(;;) {
      double num;
      int sc = scanf("%lf", &num);
      if(sc == EOF || sc != 1) break;

      array[index] = num;
      index++;
   }

   inssort(array, index, sizeof(array[0]), compare);

   for(int c = 0; c < index; c++) {
      printf("%20.15g\n", array[c]);

   }  
   

   return 0;
}
