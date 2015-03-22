// $Id: catbychar.c,v 1.2 2013-01-29 14:47:43-08 - - $

//
// NAME
//    catbychar - example of simple cat to display files
//
// SYNOPSIS
//    catbychar [filename...]
//
// DESCRIPTION
//    Uses getc (getchar) to read bytes from files and print
//    to stdout.  If no filenames are specified, reads stdin.
//

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"

void catbychar (FILE *input) {
   for (;;) {
      int byte = fgetc (input);
      if (byte == EOF) break;
      putchar (byte);
   }
}

int main (int argc, char **argv) {
   program_name = basename (argv[0]);
   if (argc == 1) {
      catbychar (stdin);
   }else {
      for (int argi = 1; argi < argc; ++argi) {
         char *filename = argv[argi];
         if (strcmp (filename, STDIN_NAME) == 0) {
            catbychar (stdin);
         }else {
            FILE *input = fopen (filename, "r");
            if (input != NULL) {
               catbychar (input);
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

