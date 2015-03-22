// $Id: list3.c,v 1.4 2013-02-14 09:03:37-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node {
   char *word;
   node *link;
};

int main (int argc, char **argv) {
   node *head = NULL;
   for (int argi = 0; argi < argc; ++argi) {
      node *node = malloc (sizeof (struct node));
      assert (node != NULL);
      node->word = argv[argi];
      node->link = head;
      head = node;
   }
   node *curr = head;
   while(curr->link != NULL){
      printf ("%p->node {word=%p->[%s], link = %p}\n",
              curr, curr->word, curr->word, curr->link);
   curr = curr->link;
   }
   printf("%p->node {word=%p->[%s]}\n", curr, curr->word, curr->word);    

   return 9;
}
