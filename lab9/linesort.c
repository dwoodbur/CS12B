#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "inssort.h"

int compare (const void *this, const void *that) {
   char **thisstr = (char**) this;
   char **thatstr = (char**) that;
   return strcmp (*thisstr, *thatstr);
}

int main (void) {
   char buffer[1000];
   char *array[1000];
   size_t index = 0;
   
   for(;;) {
      char *sc = fgets(buffer, sizeof(buffer), stdin);
      if(sc == NULL) break;

      char *sym = strchr(buffer, '\n');
      if(sym != NULL) *sym = '\0';		

      array[index] = strdup(buffer);
      index++;
   }
   
   inssort(array, index, sizeof(array[0]), compare);
 
   for(int c = 0; c < index; c++) {
      printf("%s\n", array[c]);

   }  
   

   return 0;
}
