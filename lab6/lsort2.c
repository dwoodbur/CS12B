// $Id: nsort.c,v 1.1 2011-04-29 19:46:42-07 - - $

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


void sortList (/*node *head*/ cstring programName) {
   for(int linenr = 0;;linenr++) {
      cstring gotline = fgets(buffer, sizeof buffer, stdin);
      if(gotline == NULL) break;
      
      cstring nlpos = strchr(buffer, '\n');
      if(nlpos != NULL) {
	 *nlpos = '\0';
      }
      else {
	 fprintf(stderr, "%s: %d: unterminated line: %s\n",
	       programName, linenr, buffer); 	 
      }

      node *tmp = malloc(sizeof(struct node));
      assert(tmp != NULL);
      tmp->item = strdup(buffer);
      assert(tmp->item != NULL);
      tmp->link = head;
      head = tmp;
   }	

   node *tmp = malloc (sizeof (struct node));
   cstring line = NULL;
   if(head == NULL){
      assert(tmp != NULL);
      tmp->item = line;
      tmp->link = head;
      head = tmp;
   }
   else{
      assert(tmp != NULL);
      tmp->item = line;
      node *previous = NULL;
      for(node *curr = head; curr != NULL; curr = curr->link) {
         if(strcmp(tmp->item, curr->item) < 0 && previous == NULL) {
   	    tmp->link = head;
	    head = tmp;
	    break;
         }
	 else if(strcmp(tmp->item, curr->item) < 0) {
	    tmp->link = curr;
	    previous->link = tmp;
	    break;
         }
	 else if(strcmp(tmp->item, curr->item) > 0 && curr->link == NULL) {
	    curr->link = tmp;
	    tmp->link = NULL;
	    break;
	 }
	 previous = curr; 
      }
   }
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
   programName = basename(argv[0]);
   if(argc > 2) {
      printf("Too Many Arguments");
      exit_status = EXIT_FAILURE;
   }
   else {
      if(argc == 2) {
         optionsCheck(argc, argv);
      }
     
      if(strcmp(argv[0], "-d") == 0) {
         printf("&head= %p\n", &head);
         printf("head= %p\n", head);
         for(node *curr = head; curr != NULL; curr = curr->link) {
            printf("%p -> struct node {item = %.15s. link = %p}\n",
                 curr, curr->item, curr->link);
         }
      printf("NULL= %p\n", NULL);
      }
      else {
         sortList(/*head*/programName);
         printList(/*head*/);
         destroyNodes(/*head*/);
      }
   }
   return(exit_status);
}

