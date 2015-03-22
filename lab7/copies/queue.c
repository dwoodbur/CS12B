// $Id: queue.c,v 1.1 2013-02-28 16:26:37-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

#define STUBPRINTF(...) fprintf (stderr, __VA_ARGS__);

static char *queue_tag = "struct queue";
static char *queue_node_tag = "struct queue_node";

typedef struct queue_node queue_node;
struct queue_node {
   char *tag;
   queue_item_t item;
   queue_node *link;
};

struct queue {
   char *tag;
   queue_node *front;
   queue_node *rear;
};

queue *new_queue () {
/**///   STUBPRINTF ("return NULL\n");
   queue *new = malloc(sizeof(struct queue));
   new->front = NULL;
   new->rear = NULL;
   new->tag = queue_tag;  
 
   return new;
}

void free_queue (queue *this) {
   assert (is_queue (this));
   assert (isempty_queue (this));
   memset (this, 0, sizeof (queue));
   free (this);
}

void insert_queue (queue *this, queue_item_t item) {
   assert (is_queue (this));
/**///   STUBPRINTF ("item =\n\t\"%s\"\n", item);
   struct queue_node* newnode = malloc(sizeof(struct queue_node));
   newnode->item = item;
   newnode->link = NULL;  
   if(isempty_queue(this)) {
      this->front = newnode;
      this->rear = this->front;
   }
   else {
      this->rear->link = newnode;
      this->rear = this->rear->link;

   }

}

queue_item_t remove_queue (queue *this) {
   assert (is_queue (this));
   assert (! isempty_queue (this));
/**///   STUBPRINTF ("return NULL\n");
  queue_item_t value = this->front->item;
   struct queue_node* temp = this->front;
   this->front = this->front->link; 
   free(temp);

   return value;
}

bool isempty_queue (queue *this) {
   assert (is_queue (this));
   return this->front == NULL;
}

bool is_queue (queue *this) {
   return this != NULL && this->tag == queue_tag;
}

