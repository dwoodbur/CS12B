// $Id: catbyline.c,v 1.2 2013-01-29 14:47:43-08 - - $

//
// NAME
//    catbyline - example of simple cat to display files
//
// SYNOPSIS
//    catbyline [filename...]
//
// DESCRIPTION
//    Uses fgets to read lines from files and prints to stdout.
//    If no filenames are specified, reads stdin.  Does not consider
//    whether input buffer is too short.
//

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"

void catbyline (FILE *input) {
   char buffer[1024];
   for (;;) {
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL) break;
      fputs (buffer, stdout);
   }
}

int main (int argc, char **argv) {
   program_name = basename (argv[0]);
   if (argc == 1) {
      catbyline (stdin);
   }else {
      for (int argi = 1; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbyline (stdin);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
               catbyline (input);
               fclose (input);
            }else {
               exit_status = EXIT_FAILURE;
               fflush (NULL);
               fprintf (stderr, "%s: %s: %s\n", program_name,
                        filename, strerror (errno));
               fflush (NULL);
            }
         }
      }
   }
   return exit_status;
}

