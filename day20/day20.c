#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int x;
  struct node *prev;
  struct node *next;
} Node;

typedef struct list {
  struct node *head;
  int n;
} List;

Node *list_append(List *list, int x) {
  if (list->head == NULL) {
    list->head = malloc(sizeof(Node));
    list->head->x = x;
    list->head->prev = list->head->next = list->head;
    list->n += 1;
    return list->head;
  } else {
    Node *p = malloc(sizeof(Node));
    list->head->prev->next = p;
    p->x = x;
    p->prev = list->head->prev;
    p->next = list->head;
    list->head->prev = p;
    list->n += 1;
    return p;
  }
}

void list_print(const List *list) {
  if (list->head == NULL) {
    printf("empty list\n");
  } else {
    Node *p = list->head;
    Node *tail = list->head->prev;
    while (p != tail) {
      printf("%d ", p->x);
      p = p->next;
    }
    printf("%d n=%d\n", tail->x, list->n);
  }
}

List list;
Node *nlist[5005];
int len;

void move(Node *p) {
  int x = p->x;
  int fwd = x % (list.n - 1);
  Node *q;
  int i;
  if (fwd < 0) fwd += (list.n - 1);
  for (i = 0; i < fwd; i++) {
    q = p->next;
    p->prev->next = q;
    q->prev = p->prev;
    p->prev = q;
    q->next->prev = p;
    p->next = q->next;
    q->next = p;
  }
}

int nth_after_zero(int n) {
  Node *p = list.head;
  int i;
  while (p != list.head->prev) {
    if (p->x == 0) break;
    p = p->next;
  }
  for (i = 0; i < n; i++) {
    p = p->next;
  }
  return p->x;
}

int main(void) {
  int i, x;
  int tot = 0;
  FILE *fp = fopen("input.txt", "r");
  while (fscanf(fp, "%d", &x) == 1) {
    nlist[len++] = list_append(&list, x);
  }
  fclose(fp);
  for (i = 0; i < len; i++) {
    move(nlist[i]);
  }
  tot += nth_after_zero(1000);
  tot += nth_after_zero(2000);
  tot += nth_after_zero(3000);
  printf("%d\n", tot);
  return 0;
}
