// $Id: stack.c,v 1.5 2013-02-19 14:46:04-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

typedef struct stack_node stack_node;

static char *stack_tag = "struct stack";
static char *stack_node_tag = "struct stack_node";

struct stack {
   char *tag;
   size_t length;
   stack_node *top;
};

struct stack_node {
   char *tag;
   stack_item item;
   stack_node *link;
};

stack *new_stack (void) {
   stack *stack = malloc (sizeof (struct stack));
   assert (stack != NULL);
   stack->tag = stack_tag;
   stack->length = 0;
   stack->top = NULL;
   return stack;
}

void free_stack (stack *stack) {
   assert (is_stack (stack));
   assert (is_empty_stack (stack));
   memset (stack, 0, sizeof stack);
   free (stack);
}


void push_stack (stack *stack, stack_item item) {
   assert (is_stack (stack));
   stack_node *curr = malloc(sizeof(struct stack_node));
   curr->tag = stack_node_tag;
   curr->item = item;
   curr->link = stack->top;
   stack->top = curr;
   ++stack->length;
}

stack_item pop_stack (stack *stack) {
   assert (is_stack (stack));
   assert (! is_empty_stack (stack));

   stack_item oldtopitem = stack->top->item;
   stack_node *tmp = stack->top;
   stack->top = stack->top->link; 
   --stack->length;
   return oldtopitem;
}

stack_item peek_stack (stack *stack, int index) {
   assert (is_stack (stack));
   assert (index >= 0);
   assert (index < length_stack (stack));

   stack_node *curr = stack->top;
   for(int i = 0; i != index ; i++) {
      curr = curr->link;

   }
   if(index != 0) return curr->link->item;
   return curr->item;
}

bool is_empty_stack (stack *stack) {
   assert (is_stack (stack));
   return length_stack (stack) == 0;
}

int length_stack (stack *stack) {
   assert (is_stack (stack));
   return stack->length;
}

bool is_stack (stack *stack) {
   return stack != NULL && stack->tag == stack_tag;
}

