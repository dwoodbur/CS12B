// $Id: bigint.c,v 1.4 2013-02-19 14:46:04-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bigint.h"

static char *bigint_tag = "struct bigint";

struct bigint {
   char *tag;
   bool is_negative;
   size_t length;
   size_t digits;
   char *buffer;
};

static void trim_zeros (bigint *bigint) {
   while (bigint->digits > 0) {
      size_t digitpos = bigint->digits - 1;
      if (bigint->buffer[digitpos] != 0) break;
      --bigint->digits;
   }
}

static bigint *do_add (bigint *left, bigint *right) {
   bigint *result = new_bigint(0);
   result->digits = left->digits+1;
   int carry = 0, sum = 0, maxDigits = 0;
   if(left->digits > right->digits) maxDigits = left->digits;
   else maxDigits = right->digits;
   for(int index = 0; index < maxDigits; index++) {
      sum = left->buffer[index] + right->buffer[index] + carry;
      result->buffer[index] = sum % 10; 
      carry = sum/10;
   }
   return result;
}

static bigint *do_sub (bigint *left, bigint *right) {
   bigint *result = new_bigint(0);
   result->digits = left->digits+1;
   int borrow = 0, diff = 0, sum = 0, maxDigits = 0;
   if(left->digits > right->digits) maxDigits = left->digits;
   else maxDigits = right->digits;
   for(int index = 0; index <= maxDigits ; index++) {
      diff = left->buffer[index] - right->buffer[index] - borrow;
      if(diff < 0) diff += 20; 
      result->buffer[index] = sum % 10;
      borrow = diff / 10;
   }
   return result;
}

bigint *new_bigint (size_t length) {
   bigint *bigint = malloc (sizeof (struct bigint));
   assert (bigint != NULL);
   bigint->tag = bigint_tag;
   bigint->is_negative = false;
   bigint->length = length;
   bigint->digits = 0;
   bigint->buffer = calloc (length, sizeof (char));
   assert (bigint->buffer != NULL);
   return bigint;
}

bigint *new_string_bigint (char *string) {
   assert (string != NULL);
   size_t length = strlen (string);
   assert (length > 0);
   bigint *bigint = new_bigint (length);
   if (*string == '_') {
      bigint->is_negative = true;
      ++string;
      --length;
   }
   int index = 0;
   while (length -- > 0) {
      char digit = string[length] - '0';
      assert (0 <= digit && digit <= 9);
      bigint->buffer[index++] = digit;
   }
   trim_zeros (bigint);
   return bigint;
}


void free_bigint (bigint *bigint) {
   assert (is_bigint (bigint));
   free (bigint->buffer);
   memset (bigint, 0, sizeof (bigint));
   free (bigint);
}

void print_bigint (bigint *bigint, FILE *file) {
   assert (is_bigint (bigint));
   int len = bigint->length;
   fflush(stdout);
   for(int i = 0; i < len; i++) {
      printf("bigint: %d\n", bigint->buffer[i]);
   }
}

bigint *add_bigint (bigint *left, bigint *right) {
   bigint *sum = /*malloc(sizeof(struct bigint))*/ new_bigint(0);


   assert (is_bigint (left));
   assert (is_bigint (right));
  
   if(left->is_negative == right->is_negative) {
      sum = do_add(left, right);
   } 
   else {
      sum = do_sub(left, right);
   }

   return sum;
}

bigint *sub_bigint (bigint *left, bigint *right) {
   bigint *diff =/* malloc(sizeof(struct bigint))*/new_bigint(0);

   assert (is_bigint (left));
   assert (is_bigint (right));
   
   if(left->is_negative != right->is_negative) {
     diff = do_add(left, right); 
   }
   else {
      diff = do_sub(left, right);
   }

   return diff;
}

bigint *mul_bigint (bigint *left, bigint *right) {
   assert (is_bigint (left));
   assert (is_bigint (right));
   bigint *total = new_bigint(0);
   for(size_t i = 0; i < left->digits; ++i) {
      bigint *multi = new_bigint(right->digits + 1 + i);
      char carry = 0;
      for(size_t j = 0; j < right->digits; j++) {
	 char product = left->buffer[i] * right->buffer[j] + carry;
	 multi->buffer[i+j] = product % 10;
	 carry = product/10;
      }
      bigint *oldTotal = total;
      total = add_bigint(total, multi);
   }      
   if(right->is_negative == left->is_negative) total->is_negative = false;
   else total->is_negative = true;
   return total;
}

bool is_bigint (bigint *bigint) {
   
   return bigint != NULL && bigint->tag == bigint_tag;
}

