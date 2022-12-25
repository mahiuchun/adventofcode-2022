#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_F 0
#define MY_D 1

typedef struct node {
  int type;
  char name[255];
  struct node* pi;
  int size;
  struct node* fc; /* first child */
  struct node* ns; /* next sibiling */
} node;

typedef void (*walk_fn)(node* n, void* data);

node* make_node(void) {
  node* n = malloc(sizeof(node));
  return n;
}

node* make_f(const char* name, int size) {
  node* n = make_node();
  n->type = MY_F;
  strcpy(n->name, name);
  n->pi = NULL;
  n->size = size;
  n->ns = NULL;
  return n;
}

node* make_d(const char* name) {
  node* n = make_node();
  n->type = MY_D;
  strcpy(n->name, name);
  n->pi = NULL;
  n->size = -1;
  n->fc = NULL;
  n->ns = NULL;
  return n;
}

void add_child(node* dst, node* src) {
  node* p = dst->fc;
  if (p == NULL) {
    dst->fc = src;
  } else {
    while (p->ns) {
      p = p->ns;
    }
    p->ns = src;
  }
  src->pi = dst;
}

node* find_child_d(node* n, const char* name) {
  node* p = n->fc;
  node* res = NULL;
  while (p) {
    if (p->type == MY_D && !strcmp(p->name, name)) {
      return p;
    }
    p = p->ns;
  }
  return res;
}

void walk(node* n, walk_fn fn, void* data) {
  if (n->type == MY_D && n->fc) {
    walk(n->fc, fn, data);
  }
  fn(n, data);
  if (n->ns) {
    walk(n->ns, fn, data);
  }
}

void compute_size(node* n, void* data) {
  node* p = NULL;
  if (n->type == MY_F) return;
  n->size = 0;
  p = n->fc;
  while (p) {
    n->size += p->size;
    p = p->ns;
  }
}

void find_sum(node* n, void* data) {
  int sofar = *(int*)data;
  if (n->type == MY_D && n->size <= 100000) {
    sofar += n->size;
  }
  *(int*)data = sofar;
}

char line[1000];
char buf[255];

int main(void) {
  int size, tot = 0;
  node* root = make_d("/");
  node* cwd = root;
  node* maybe = NULL;
  FILE* fp = fopen("input.txt", "r");
  while (fgets(line, sizeof(line), fp)) {
    line[strlen(line) - 1] = 0;
    if (line[0] == '$') {
      if (!strcmp(line, "$ ls")) {
        continue;
      } else {
        sscanf(line, "$ cd %s", buf);
        if (!strcmp(buf, "/")) {
          cwd = root;
        } else if (!strcmp(buf, "..")) {
          cwd = cwd->pi;
        } else {
          maybe = find_child_d(cwd, buf);
          if (maybe == NULL) {
            maybe = make_d(buf);
            add_child(cwd, maybe);
          }
          cwd = maybe;
        }
      }
    } else {
      if (sscanf(line, "dir %s", buf)) {
        maybe = make_d(buf);
        add_child(cwd, maybe);
      } else {
        sscanf(line, "%d %s", &size, buf);
        maybe = make_f(buf, size);
        add_child(cwd, maybe);
      }
    }
  }
  fclose(fp);
  walk(root, compute_size, NULL);
  walk(root, find_sum, &tot);
  printf("%d\n", tot);
  return 0;
}
