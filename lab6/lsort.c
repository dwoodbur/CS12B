// $Id: lsort.c,v 1.1 2011-04-29 19:46:42-07 - - $

#include <assert.h>
#include <libgen.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>

#define OPTION "d"
typedef char *cstring;
typedef struct node node;
struct node {
   cstring item;
   node *link;
};

int exit_status = EXIT_SUCCESS;
char *programName;
_Bool debugFlag = false;
char buffer[72];

node *head = NULL;

void optionsCheck (int num, char** str) {
   for(;;) {
      int opts = getopt(num, str, OPTION);
         if (opts == EOF) break;
         switch (opts) {
            case 'd':
               debugFlag = true;
               break;
            default:
               printf("%s: -%c: invalid option\n", programName, opts);
               abort();
         }
   }
}


void sortList (/*node *head*/) {
   for(int linenr = 1; ;linenr++) {
    //  node *tmp = malloc (sizeof(struct node));
      char *gotline = fgets(buffer, sizeof buffer, stdin);
      if(gotline == NULL) break;
      char *nlpos = strchr(buffer, '\n');
      if(nlpos != NULL) {
         *nlpos = '\0';
      }
      else {
         fprintf(stderr, "%s: %d: unterminated line: %s\n",
               programName, linenr, buffer);  
      }
      if (head == NULL) { 
         node *tmp = malloc (sizeof (struct node));
         assert (tmp != NULL);
   /**/      tmp->item = strdup(buffer);
         tmp->link = head;
         head = tmp;
      }
      else {
         node *tmp = malloc (sizeof (struct node));
         assert (tmp != NULL);
    /**/     tmp->item = strdup(buffer);
         node *previous = NULL;
         for(node *curr = head; curr != NULL; curr = curr->link) {
            if (strcmp(tmp->item, curr->item) < 0 && previous == NULL) {
               tmp->link = head;
               head = tmp;
               break;
            }
            else if (strcmp(tmp->item, curr->item) < 0) {
               tmp->link = curr;
               previous->link = tmp;
               break;
            }
            else if (strcmp(tmp->item, curr->item) >= 0 && curr->link == NULL) {
               curr->link = tmp;
               tmp->link = NULL;
               break;
            }free(previous);
            previous = curr;
         }
      }
   }while(getchar() != '\n');
}

void printList (/*node *head*/) {
   if(debugFlag) {
      for(node *curr = head; curr != NULL; curr = curr->link){
         printf("Node pointer[%p] : item->%s\n", curr, curr->item);
      }
   }
   else{
      for(node *curr = head; curr != NULL; curr = curr->link){
         printf("%24.15s\n", curr->item);
      }
   }
}

void destroyNodes (/*node *head*/){
   while(head != NULL){
      node *old = head;
      head = head->link;
      free(old);
   
   }
}

int main (int argc, char** argv) {
   programName = basename(argv[0]);/**/
   if(argc > 2) {
      printf("Too Many Arguments");
      exit_status = EXIT_FAILURE;
   }
   else {
      if(argc == 2) {
         optionsCheck(argc, argv);
      }
      if(strcmp(argv[0], "-d") != 0){
         sortList(/*head*/);
         printList(/*head*/);
         destroyNodes(/*head*/);
      }
      else {
         printf("%s: head= %p\n", argv[0], head);
         while(head != NULL) {
            node *old = head;
	    head = head->link;
	    printf("%s: %p->node {\n"
	           "    string = %p->\"%s\",\n"
	 	   "    link= %p}\n",
		   programName, old, old->item, old->item, old->link);
         }
      }
   }
   return(exit_status);
}

