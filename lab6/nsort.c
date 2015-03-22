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

typedef struct node node;
struct node {
   double item;
   node *link;
};

int exit_status = EXIT_SUCCESS;
char *programName;
_Bool debugFlag = false;

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


void sortList (/*node *head*/FILE *fp) {
   for(;;) {
      double number;
     
     // FILE *fp;
     int sc=fgetc(fp);
       

     // int sc = scanf("%lg\n", &number);

      if (sc == EOF || sc != 1) break;
      if (head == NULL) { 
         node *tmp = malloc (sizeof (struct node));
         assert (tmp != NULL);
         tmp->item = number;
         tmp->link = head;
         head = tmp;
      }
      else {
         node *tmp = malloc (sizeof (struct node));
         assert (tmp != NULL);
         tmp->item = number;
         node *previous = NULL;
         for(node *curr = head; curr != NULL; curr = curr->link) {
            if (number < curr->item && previous == NULL) {
               tmp->link = head;
               head = tmp;
               break;
            }
            else if (number < curr->item) {
               tmp->link = curr;
               previous->link = tmp;
               break;
            }
            else if (number >= curr->item && curr->link == NULL) {
               curr->link = tmp;
               tmp->link = NULL;
               break;
            }
            previous = curr;
         }
      }
   }while(getchar() != '\n');
}


void printList (/*node *head*/) {
   if(debugFlag) {
      for(node *curr = head; curr != NULL; curr = curr->link){
         printf("Node pointer[%p] : item->%g\n", curr, curr->item);
      }
   }
   else{
      for(node *curr = head; curr != NULL; curr = curr->link){
         printf("%24.15g\n", curr->item);
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
            printf("%p -> struct node {item = %.15g. link = %p}\n",
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

