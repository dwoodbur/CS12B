// $Id: environ.c,v 1.1 2013-02-14 09:19:16-08 - - $

#include <assert.h>
#include <stdio.h>


int main (int argc, char **argv) {
   extern char **environ;
   for(char curr = *environ; curr != NULL; *environ++){
      printf("%c", curr);
   } 


   return 0;
}
