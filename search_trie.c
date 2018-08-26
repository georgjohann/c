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

struct trie* new(void) {
   struct trie* p = malloc(sizeof (struct trie));
   p -> empty_str = false;
   p -> initial = NULL;
   return p;
}

void delete(struct trie* p) {
   _delete_rec(p -> initial);
   free(p);
}

void _delete_rec(struct node* p) {
   if (p) {
      _delete_rec(p -> sib);
      _delete_rec(p -> child);

      free(p);
   }
}

void insert(struct trie* trie_p, char* str_p) {
   struct node* p;

   if (! *str_p) {
      trie_p -> empty_str = true;
      return;
   }

   if (! (p = trie_p -> initial)) {
      trie_p -> initial = malloc(sizeof (struct node));
      p = trie_p -> initial;

      goto NEW_SUFFIX;
   }

   for (;;) {
      if (p -> value == *str_p) {
         if (! *(++str_p)) {
            p -> end = true;
            return;
         }

         if (! p -> child) {
            p -> child = malloc(sizeof (struct node));
            p = node_ptr -> child;

            break;
         }

         p = p -> child;
      }
      else {
         if (! p -> sib) {
            p -> sib = malloc(sizeof (struct node));
            p = node_ptr -> sib;

            break;
         }

         p = p -> sib;
      }
   }

   NEW_SUFFIX:
   for (;;) {
      p -> value = *(str_p++);
      p -> sib = NULL;

      if (! *str_p) {
         p -> end = true;
         p -> child = NULL;

         return;
      }
      p -> end = false;
      p -> child = malloc(sizeof (struct node));

      p = p -> child;
   }
}

bool element(struct trie* trie_p, char* str_p) {
   struct node* p;

   if (! *str_p) { return trie_p -> empty_str; }

   if (! (p = trie_p -> initial)) { return false; }

   do {
      if (p -> value == *str_p) {
         if (! *(++str_p)) { return p -> end; }

         p = p -> child;
      }
      else {
         p = p -> sib;
      }
   } while (p);

   return false;
}
