#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pos {
  int r;
  int c;
  int t;
} Pos;

#define NMOVES 5
int drs[] = {-1, 1, 0, 0, 0};
int dcs[] = {0, 0, -1, 1, 0};

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

typedef struct blizzard {
  int r;
  int c;
  int dr;
  int dc;
} Blizzard;

Blizzard bs[5000];
int nbs;

char map[100][1000];
int nr, nc;
int t;

int fewest(int startr, int startc, int startt, int goalr, int goalc) {
  Queue* q = make_queue();
  Pos pos, tmp;
  int i, j;
  pos.r = startr;
  pos.c = startc;
  pos.t = startt;
  enqueue(q, pos);
  while (q->head) {
    pos = dequeue(q);
    if (pos.r == goalr && pos.c == goalc) {
      return pos.t;
    }
    if (t == pos.t) {
      map[startr][startc] = '.';
      map[goalr][goalc] = '.';
      for (i = 1; i < nr - 1; i++) {
        for (j = 1; j <= nc - 2; j++) {
          map[i][j] = '.';
        }
      }
      for (i = 0; i < nbs; i++) {
        bs[i].r += bs[i].dr;
        bs[i].c += bs[i].dc;
        if (bs[i].r == 0) {
          bs[i].r = nr - 2;
        } else if (bs[i].r == nr - 1) {
          bs[i].r = 1;
        }
        if (bs[i].c == 0) {
          bs[i].c = nc - 2;
        } else if (bs[i].c == nc - 1) {
          bs[i].c = 1;
        }
        map[bs[i].r][bs[i].c] = '*';
      }
      t += 1;
    }
    for (i = 0; i < NMOVES; i++) {
      tmp.r = pos.r + drs[i];
      if (tmp.r < 0 || tmp.r >= nr) continue;
      tmp.c = pos.c + dcs[i];
      if (tmp.c < 0 || tmp.c >= nc) continue;
      if (map[tmp.r][tmp.c] == '.') {
        map[tmp.r][tmp.c] = 'E';
        tmp.t = pos.t + 1;
        enqueue(q, tmp);
      }
    }
  }
  return -999;
}

int main(void) {
  int i, j;
  int startc, endc;
  FILE* fp = fopen("input.txt", "r");
  int t1, t2, t3;
  while (fgets(map[nr], 1000, fp)) {
    map[nr][strlen(map[nr]) - 1] = 0;
    nr += 1;
  }
  fclose(fp);
  nc = strlen(map[0]);
  for (i = 0; i < nc; i++) {
    if (map[0][i] != '#') {
      startc = i;
      break;
    }
  }
  for (i = 1; i < nr - 1; i++) {
    for (j = 1; j <= nc - 2; j++) {
      if (strchr("^v<>", map[i][j])) {
        bs[nbs].r = i;
        bs[nbs].c = j;
        switch (map[i][j]) {
          case '^':
            bs[nbs].dr = -1;
            bs[nbs].dc = 0;
            break;
          case 'v':
            bs[nbs].dr = 1;
            bs[nbs].dc = 0;
            break;
          case '<':
            bs[nbs].dr = 0;
            bs[nbs].dc = -1;
            break;
          case '>':
            bs[nbs].dr = 0;
            bs[nbs].dc = 1;
            break;
        }
        nbs += 1;
      }
    }
  }
  for (i = 0; i < nc; i++) {
    if (map[nr - 1][i] != '#') {
      endc = i;
      break;
    }
  }
  t1 = fewest(0, startc, 0, nr - 1, endc);
  t2 = fewest(nr - 1, endc, t1, 0, startc);
  t3 = fewest(0, startc, t2, nr - 1, endc);
  printf("%d\n", t3);
}
