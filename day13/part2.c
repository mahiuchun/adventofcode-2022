#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MY_D 0
#define MY_L 1

typedef struct node {
  int type;
  int val;
  struct node* list;
  struct node* next;
} Node;

typedef struct res {
  Node* node;
  int eat;
} Res;

char buf[1000];

Res parse(const char* s, int i) {
  Res r, rr;
  Node* head;
  Node* tail;
  if (s[i] == ']') {
    r.node = NULL;
    r.eat = 1;
    return r;
  } else if (isdigit(s[i])) {
    r.eat = 0;
    r.node = malloc(sizeof(Node));
    r.node->type = MY_D;
    r.node->val = 0;
    r.node->list = NULL;
    r.node->next = NULL;
    while (isdigit(s[i])) {
      r.node->val = 10 * r.node->val + s[i] - '0';
      r.eat++;
      i++;
    }
    return r;
  } else {
    r.node = malloc(sizeof(Node));
    r.node->type = MY_L;
    r.node->val = 0;
    head = tail = r.node->list = malloc(sizeof(Node));
    r.eat = 1;
    i++;
    do {
      rr = parse(s, i);
      i += rr.eat;
      r.eat += rr.eat;
      if (s[i] == ',') {
        i++;
        r.eat++;
      }
      tail->next = rr.node;
      tail = rr.node;
    } while (tail && s[i]);
    r.node->list = head->next;
    free(head);
    r.node->next = NULL;
    return r;
  }
}

void print(Node* n) {
  Node* p;
  if (n->type == MY_D) {
    printf("%d", n->val);
  } else {
    printf("[");
    p = n->list;
    while (p) {
      if (p != n->list) printf(",");
      print(p);
      p = p->next;
    }
    printf("]");
  }
}

void tolist(Node* n) {
  n->list = malloc(sizeof(Node));
  n->list->type = MY_D;
  n->list->val = n->val;
  n->list->list = NULL;
  n->list->next = NULL;
  n->type = MY_L;
  n->val = 0;
}

int compare(Node* l, Node* r) {
  Node* pl;
  Node* pr;
  int rr;
  if (l == NULL && r == NULL) {
    return 0;
  } else if (l == NULL) {
    return -1;
  } else if (r == NULL) {
    return 1;
  } else if (l->type == MY_D && r->type == MY_D) {
    return l->val - r->val;
  } else if (l->type == MY_L && r->type == MY_L) {
    pl = l->list;
    pr = r->list;
    while (pl && pr) {
      rr = compare(pl, pr);
      if (rr != 0) return rr;
      pl = pl->next;
      pr = pr->next;
    }
    return compare(pl, pr);
  } else if (l->type == MY_L) {
    tolist(r);
    return compare(l, r);
  } else if (r->type == MY_L) {
    tolist(l);
    return compare(l, r);
  }
  return 0;
}

typedef struct both {
  char s[1000];
  Node* n;
} Both;

int compare_s(const void* v1, const void* v2) {
  const Both* b1 = v1;
  const Both* b2 = v2;
  return compare(b1->n, b2->n);
}

Both strings[500];
int si;

void add_string(const char* s) {
  Res r;
  strcpy(strings[si].s, s);
  r = parse(s, 0);
  strings[si].n = r.node;
  si++;
}

int main(void) {
  int i, i1, i2, m;
  FILE* fp = fopen("input.txt", "r");
  while (!feof(fp)) {
    fscanf(fp, "%s\n", buf);
    add_string(buf);
    fscanf(fp, "%s\n", buf);
    add_string(buf);
    fscanf(fp, "\n");
  }
  add_string("[[2]]");
  add_string("[[6]]");
  m = si;
  fclose(fp);
  qsort(strings, m, sizeof(Both), compare_s);
  for (i = 0; i < m; i++) {
    if (!strcmp(strings[i].s, "[[2]]")) i1 = i;
    if (!strcmp(strings[i].s, "[[6]]")) i2 = i;
  }
  printf("%d\n", (i1 + 1) * (i2 + 1));
  return 0;
}
