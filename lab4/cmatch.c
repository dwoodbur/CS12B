// $Id: cmatch.c,v 1.2 2013-01-29 14:47:43-08 - - $

//
// NAME
//    cmatch.c - example of simple cat to display files
//
// SYNOPSIS
//    cmatch.c [filename...]
//
// DESCRIPTION
//    Uses fgets to read lines from files and prints to stdout.
//    If no filenames are specified, reads stdin.  Does not consider
//    whether input buffer is too short.
//

#define _GNU_SOURCE

#include <errno.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

char *program_name = NULL;
int exit_status = EXIT_SUCCESS;
#define STDIN_NAME "-"

struct options {
   bool ignore_case;
   bool filenames_only;
   bool number_lines;
};

void scan_options (int argc, char **argv, struct options *opts) {
   opts->ignore_case = false;
   opts->filenames_only = false;
   opts->number_lines = false;
   opterr = false;
   for (;;) {
      int opt = getopt (argc, argv, "iln");
      if (opt == EOF) break;
      switch (opt) {
	 case 'i':
	    opts->ignore_case = true;
	    break;
	 case 'l':
	    opts->filenames_only = true;
	    break;
	 case 'n':
	    opts->number_lines = true;
	    break;
	 default:
	    exit_status = EXIT_FAILURE;
	    fflush (NULL);
	    fprintf (stderr, "%s: -%c: invalid option\n",
				program_name, optopt);
	    break;
      }
   }		    
}


void catbyline (FILE *input, bool number, bool case_check, char *key) {
   char buffer[1024];
   bool line_match = false;
   for (int line = 1;; line++) {
      line_match = false;
      char *buf = fgets (buffer, sizeof buffer, input);
      if (buf == NULL) break;
      
      if(case_check == false) { 
         if(strcasestr(buf,key) != NULL) { 
            line_match = true;
         }
      }
      else {
         if(strstr(buf, key) != NULL) {
            line_match = true;
         }
      }
      if(number == true && line_match == true) printf("%d:", line);
      if(line_match == true) fputs (buffer, stdout);
   }
}

int main (int argc, char **argv) {
   struct options opts;
   int modifiers = 0;
   char *key;
   program_name = basename (argv[0]);
   scan_options (argc, argv, &opts);
   if (argc == 1) {printf("argc == 1\n");
      catbyline (stdin, false, opts.ignore_case, NULL);
   }else {
      int arg_start;
      for(arg_start=1;;arg_start++){ 
         if(strcasestr(argv[arg_start], "-") != NULL) modifiers++;
         else break;
      }
      if(argc - modifiers > 2){
         key = argv[arg_start];
         arg_start++;
      }
      else if(argc - modifiers == 2){
	 key = argv[arg_start];
         catbyline (stdin, false, opts.ignore_case, key);
         return exit_status;
      }	
      for (int argi = arg_start; argi < argc; ++argi) {
         char *filename = argv[argi];
         if(opts.filenames_only == true) printf("%s\n", filename);
         else {
           if(opts.filenames_only == false) { 
	    FILE *input = fopen (filename, "r");
            if (input != NULL) {printf("REAL DEAL\n");
	       catbyline (input, opts.number_lines, opts.ignore_case, key);
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
   }
   return exit_status;
}

