#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pos {
  int x;
  int y;
  int steps;
} Pos;

typedef struct node {
  Pos pos;
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

void enqueue(Queue* q, Pos pos) {
  Node* n = malloc(sizeof(Node));
  n->pos = pos;
  n->next = NULL;
  if (q->tail) {
    q->tail->next = n;
    q->tail = n;
  } else {
    q->head = q->tail = n;
  }
}

Pos dequeue(Queue* q) {
  Node* n = q->head;
  Pos pos = n->pos;
  if (q->head == q->tail) {
    q->head = q->tail = NULL;
  } else {
    q->head = q->head->next;
  }
  free(n);
  return pos;
}

char map[50][200];
char vis[50][200];

int elevation(char x) {
  if ('a' <= x && x <= 'z') {
    return x;
  }
  if (x == 'S') return 'a';
  if (x == 'E') return 'z';
  return -1;
}

int valid(Pos from, Pos to, int m, int n) {
  if (to.x < 0 || to.x >= n) return 0;
  if (to.y < 0 || to.y >= m) return 0;
  if (vis[to.y][to.x]) return 0;
  if (elevation(map[from.y][from.x]) < elevation(map[to.y][to.x]) - 1) {
    return 0;
  }
  return 1;
}

int main(void) {
  int best = 987654321;
  int i = 0, j;
  int m, n;
  FILE* fp = fopen("input.txt", "r");
  Queue* q;
  Pos u, v;
  while (fgets(map[i], 200, fp)) {
    map[i][strlen(map[i]) - 1] = 0;
    i++;
  }
  m = i;
  n = strlen(map[0]);
  fclose(fp);
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      if (elevation(map[i][j]) != 'a') continue;
      q = make_queue();
      u.x = j;
      u.y = i;
      u.steps = 0;
      memset(vis, 0, sizeof(vis));
      enqueue(q, u);
      vis[u.y][u.x] = 1;
      while (q->head) {
        u = dequeue(q);
        if (map[u.y][u.x] == 'E') {
          best = u.steps < best ? u.steps : best;
          break;
        }
        v.steps = u.steps + 1;
        v.x = u.x - 1;
        v.y = u.y;
        if (valid(u, v, m, n)) {
          enqueue(q, v);
          vis[v.y][v.x] = 1;
        }
        v.x = u.x + 1;
        v.y = u.y;
        if (valid(u, v, m, n)) {
          enqueue(q, v);
          vis[v.y][v.x] = 1;
        }
        v.x = u.x;
        v.y = u.y - 1;
        if (valid(u, v, m, n)) {
          enqueue(q, v);
          vis[v.y][v.x] = 1;
        }
        v.x = u.x;
        v.y = u.y + 1;
        if (valid(u, v, m, n)) {
          enqueue(q, v);
          vis[v.y][v.x] = 1;
        }
      }
      while (q->head) {
        dequeue(q);
      }
      free(q);
    }
  }
  printf("%d\n", best);
}
