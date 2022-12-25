#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int item;
  struct node* next;
} Node;

typedef struct queue {
  Node* head;
  Node* tail;
} Queue;

Queue* make_queue(void) {
  Queue* q = malloc(sizeof(Queue));
  q->head = q->tail = NULL;
  return q;
}

void enqueue(Queue* q, int item) {
  Node* n = malloc(sizeof(Node));
  n->item = item;
  n->next = NULL;
  if (q->tail) {
    q->tail->next = n;
    q->tail = n;
  } else {
    q->head = q->tail = n;
  }
}

int dequeue(Queue* q) {
  Node* n = q->head;
  int item = n->item;
  if (q->head == q->tail) {
    q->head = q->tail = NULL;
  } else {
    q->head = q->head->next;
  }
  free(n);
  return item;
}

typedef struct monkey {
  char op;
  char self;
  int val;
  int test;
  int throw1;
  int throw0;
  int times;
  Queue* q1;
} Monkey;

Monkey monkeys[10];

int main(void) {
  char buf[255];
  char buf1[10], buf2[10];
  char* tok;
  int i, j, x;
  long long t;
  int most0, most1;
  int prod = 1;
  FILE* fp = fopen("input.txt", "r");
  for (i = 0; i < 10; i++) {
    monkeys[i].q1 = NULL;
  }
  while (!feof(fp)) {
    fscanf(fp, "Monkey %d:\n", &i);
    monkeys[i].q1 = make_queue();
    monkeys[i].times = 0;
    fscanf(fp, "  Starting items: %[0-9, ]\n", buf);
    tok = strtok(buf, ", ");
    while (tok) {
      sscanf(tok, "%d", &x);
      enqueue(monkeys[i].q1, x);
      tok = strtok(NULL, ", ");
    }
    fscanf(fp, "  Operation: new = %[^ ] %c %[^ \n]\n", buf1, &monkeys[i].op,
           buf2);
    if (!strcmp(buf2, "old")) {
      monkeys[i].self = 1;
    } else {
      monkeys[i].self = 0;
      sscanf(buf2, "%d", &monkeys[i].val);
    }
    fscanf(fp, "  Test: divisible by %d\n", &monkeys[i].test);
    prod *= monkeys[i].test;
    fscanf(fp, "    If true: throw to monkey %d\n", &monkeys[i].throw1);
    fscanf(fp, "    If false: throw to monkey %d\n", &monkeys[i].throw0);
    fscanf(fp, "\n");
  }
  fclose(fp);
  for (i = 1; i <= 10000; i++) {
    for (j = 0; monkeys[j].q1; j++) {
      while (monkeys[j].q1->head) {
        monkeys[j].times += 1;
        x = dequeue(monkeys[j].q1);
        if (monkeys[j].self) {
          t = x;
        } else {
          t = monkeys[j].val;
        }
        if (monkeys[j].op == '+') {
          t += x;
        } else {
          t *= x;
        }
        x = (int)(t % prod);
        if (x % monkeys[j].test == 0) {
          enqueue(monkeys[monkeys[j].throw1].q1, x);
        } else {
          enqueue(monkeys[monkeys[j].throw0].q1, x);
        }
      }
    }
  }
  most0 = 0;
  most1 = 0;
  for (j = 0; monkeys[j].q1; j++) {
    if (monkeys[j].times > most0) {
      most1 = most0;
      most0 = monkeys[j].times;
    } else if (monkeys[j].times > most1) {
      most1 = monkeys[j].times;
    }
  }
  printf("%lld\n", (long long)most0 * most1);
}
