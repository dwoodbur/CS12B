// $Id: hashset.c,v 1.2 2012-11-27 18:50:54-08 - - $

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debugf.h"
#include "hashset.h"
#include "strhash.h"

#define HASH_NEW_SIZE 15

struct hashset {
   size_t length;
   int load;
   char **array;
};

hashset_ref new_hashset (void) {
   hashset_ref new = malloc (sizeof (struct hashset));
   assert (new != NULL);
   new->length = HASH_NEW_SIZE;
   new->load = 0;
   new->array = malloc (new->length * sizeof (char*));
   assert (new->array != NULL);
   for (size_t index = 0; index < new->length; ++index) {
      new->array[index] = NULL;
   }
   //DEBUGF ('h', "%p -> struct hashset {length = %d, array=%p}\n",
     //           new, new->length, new->array);
   return new;
}

void free_hashset (hashset_ref hashset) {
   //DEBUGF ('h', "free (%p), free (%p)\n", hashset->array, hashset);
   memset (hashset->array, 0, hashset->length * sizeof (char*));
   free (hashset->array);
   memset (hashset, 0, sizeof (struct hashset));
   free (hashset);
}

void put_hashset (hashset_ref hashset, char *item) {
   //STUBPRINTF ("hashset=%p, item=%s\n", hashset, item);
   hashcode_t new = strhash(item) % hashset->length;
   if(has_hashset(hashset, item)) return;
   if((unsigned int)hashset->load * 4 > hashset->length) {
      size_t newLength = hashset->length * 2 + 1;
      char **newArray = malloc(newLength * sizeof(char *));
      assert(newArray != NULL);
      for(size_t index = 0; index < hashset->length; index++) {
         if(hashset->array[index] != NULL) {
            hashcode_t newcode = strhash(hashset->array[index]) % newLength;
	    newArray[newcode] = hashset->array[index];
	 }
      }
      free(hashset->array);
      hashset->array = newArray;
      hashset->length = newLength;
   }
   if(!has_hashset(hashset, item)) {
      while(hashset->array[new] != NULL) {
         if(new == hashset->length - 1) new = 0;
         else {
	    new = (new+1) % hashset->length;
	 }
      }
      hashset->array[new] = item;
      ++hashset->load;
   }
}

bool has_hashset (hashset_ref hashset, char *item) {
   //STUBPRINTF ("hashset=%p, item=%s\n", hashset, item);
   hashcode_t hash = strhash(item);
   size_t index = hash % hashset->length;
   while(hashset->array[index] != NULL) {
      if(strcmp(hashset->array[index], item) == 0) return true;
      index = (index + 1) % hashset->length;
   }
   return false;
}

