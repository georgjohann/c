#include <stdlib.h>
#include <stdbool.h>

enum color { RED, BLACK };

struct tree {
   struct node* root;
};

struct node {
   enum color tag;
   int value;
   struct node* left;
   struct node* right;
};

struct tree* create(void) {
   struct tree* p = malloc(sizeof (struct tree));
   p -> root = NULL;
   return p;
}

void destroy(struct tree* p) {
   _destroy_rec(p -> root);
   free(p);
}

void _destroy_rec(struct node* p) {
   if (p) {
      _destroy_rec(p -> left);
      _destroy_rec(p -> right);
      free(p);
   }
}

bool search(struct tree* pt, int v) {
   struct node* p = pt -> root;
   while (p) {
      if (p -> value == v) {
         return true;
      }
      p = (p -> value > v) ? (p -> left) : (p -> right);
   }
   return false;
}

void insert(struct tree* p, int v) {
   p -> root = _insert_rec(p -> root, v);
   p -> root -> tag = BLACK;
}

struct node* _insert_rec(struct node* p, int v) {
   struct node* pc;
   struct node* pgc;

   if (! p) {
      p = malloc(sizeof (struct node));
      *p = { RED, v, NULL, NULL };
      return p;
   }
   else if (p -> value > v) {
      p -> left = _insert_rec(p -> left, v);

      if (p -> tag == BLACK && (pc = p -> left) -> tag == RED) {
         if ((pgc = pc -> left) && pgc -> tag == RED) {
            p -> left = pc -> right;
            pc -> right = p;

            pgc -> tag = BLACK;

            return pc;
         }
         if ((pgc = pc -> right) && pgc -> tag == RED) {
            pc -> right = pgc -> left;
            p -> left = pgc -> right;
            pgc -> left = pc;
            pgc -> right = p;

            pc -> tag = BLACK;

            return pgc;
         }
      }
      return p;
   }
   else if (p -> value < v) {
      p -> right = _insert_rec(p -> right, v);

      if (p -> tag == BLACK && (pc = p -> right) -> tag == RED) {
         if ((pgc = pc -> left) && pgc -> tag == RED) {
            p -> right = pgc -> left;
            pc -> left = pgc -> right;
            pgc -> left = p;
            pgc -> right = pc;

            pc -> tag = BLACK;

            return pgc;
         }
         if ((pgc = pc -> right) && pgc -> tag == RED) {
            p -> right = pc -> left;
            pc -> left = p;

            pgc -> tag = BLACK;

            return pc;
         }
      }
      return p;
   }
   return p;
}
