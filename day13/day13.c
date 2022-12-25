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

char left[1000];
char right[1000];

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

int main(void) {
  int tot = 0;
  int index = 1;
  Res rl, rr;
  FILE* fp = fopen("input.txt", "r");
  while (!feof(fp)) {
    memset(left, 0, sizeof(left));
    memset(right, 0, sizeof(right));
    fscanf(fp, "%s\n", left);
    fscanf(fp, "%s\n", right);
    fscanf(fp, "\n");
    rl = parse(left, 0);
    rr = parse(right, 0);
    if (compare(rl.node, rr.node) < 0) tot += index;
    index += 1;
  }
  fclose(fp);
  printf("%d\n", tot);
  return 0;
}
