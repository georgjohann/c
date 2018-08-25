#include <stdlib.h>
#include <stdbool.h>

// Search trie / prefix tree string instance

struct trie {
   bool         empty_str;
   struct node* initial;
};

struct node {
   char         value;
   bool         end;

   struct node* sib;
   struct node* child;
};

typedef struct trie* trie_p;

struct trie* new(void) {
   struct trie* ptr = malloc(sizeof (struct trie));
   ptr -> empty_str = false;
   ptr -> initial = NULL;
   return ptr;
}

void delete(struct trie* ptr) {
   _delete_rec(ptr -> initial);
   free(ptr);
}

void _delete_rec(struct node* node_ptr) {
   if (node_ptr) {
      _delete_rec(node_ptr -> sib);
      _delete_rec(node_ptr -> child);

      free(node_ptr);
   }
}

void insert(struct trie* ptr, char* str_ptr) {
   struct node* node_ptr;

   if (! *str_ptr) {
      ptr -> empty_str = true;
      return;
   }

   if (! (node_ptr = ptr -> initial)) {
      ptr -> initial = malloc(sizeof (struct node));
      node_ptr = ptr -> initial;

      goto NEW_SUFFIX;
   }

   for (;;) {
      if (node_ptr -> value == *str_ptr) {
         if (! *(++str_ptr)) {
            node_ptr -> end = true;
            return;
         }

         if (! node_ptr -> child) {
            node_ptr -> child = malloc(sizeof (struct node));
            node_ptr = node_ptr -> child;

            break;
         }

         node_ptr = node_ptr -> child;
      }
      else {
         if (! node_ptr -> sib) {
            node_ptr -> sib = malloc(sizeof (struct node));
            node_ptr = node_ptr -> sib;

            break;
         }

         node_ptr = node_ptr -> sib;
      }
   }

   NEW_SUFFIX:
   for (;;) {
      node_ptr -> value = *str_ptr++;
      node_ptr -> sib = NULL;

      if (! *str_ptr) {
         node_ptr -> end = true;
         node_ptr -> child = NULL;

         return;
      }
      node_ptr -> end = false;
      node_ptr -> child = malloc(sizeof (struct node));

      node_ptr = node_ptr -> child;
   }
}

bool element(struct trie* ptr, char* str_ptr) {
   struct node* node_ptr;

   if (! *str_ptr) { return ptr -> empty_str; }

   if (! (node_ptr = ptr -> initial)) { return false; }

   do {
      if (node_ptr -> value == *str_ptr) {
         if (! *(++str_ptr)) { return node_ptr -> end; }

         node_ptr = node_ptr -> child;
      }
      else {
         node_ptr = node_ptr -> sib;
      }
   } while (node_ptr);

   return false;
}
