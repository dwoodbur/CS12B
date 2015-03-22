// $Id: futuretimes.c,v 1.16 2013-02-26 19:04:24-08 - - $

#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <limits.h>

void getFileInfo(char *filename) {
   struct stat filestat;
   char outstr[200];
   time_t t, rawtime;
   struct tm *tmp;

   t = time(NULL);
   tmp = localtime(&t);

   if(tmp == NULL) {
      perror("localtime");
      exit(EXIT_FAILURE);
   }
   if(strftime(outstr, sizeof(outstr), "%x", tmp) == 0) {
      fprintf(stderr, "strftime returned 0");
      exit(EXIT_FAILURE);
   }

   int isThereError = lstat(filename, &filestat);
   if(isThereError == -1) {
      printf("l8stat: %s: %s\n", filename, strerror(errno));
      return 1;
   }
   
   printf("%o", filestat.st_mode);
   printf(" %9ld", filestat.st_size);
   time(&rawtime);
   int timeDiff = difftime(filestat.st_mtime, rawtime);

   struct tm *timeinfo = localtime (&filestat.st_mtime);
   char buffer[80];
   if(timeDiff < 15552000) strftime(buffer, 80, " %b %e %R", timeinfo); 
   else strftime(buffer, 80, " %b %e %Y", timeinfo);

   printf("%s", buffer);
   printf(" %s\n", filename); 
}

int main (int argc, char **argv) {
   char *filename = argv[1];
   
   if(argc == 1) {
      getFileInfo(".");
   }
   else {
      for(int i=1; i < argc; i++) {
	 getFileInfo(argv[i]);
      }
   }



   return 0;
}

