#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HSIZE 11909

typedef struct Pos {
  int x;
  int y;
} Pos;

int hash(Pos* pos) {
  int h = 1013 * pos->y + pos->x;
  h %= HSIZE;
  if (h < 0) h += HSIZE;
  return h;
}

typedef struct Entry {
  Pos pos;
  struct Entry* next;
} Entry;

Entry* htab[HSIZE];

Entry* find(Pos* pos) {
  Entry* p;
  int h = hash(pos);
  p = htab[h];
  while (p) {
    if (p->pos.x == pos->x && p->pos.y == pos->y) return p;
    p = p->next;
  }
  return NULL;
}

int add(Pos* pos) {
  Entry* ent;
  int h;
  if (find(pos) != NULL) return 0;
  ent = malloc(sizeof(Entry));
  h = hash(pos);
  ent->pos = *pos;
  ent->next = htab[h];
  htab[h] = ent;
  return 1;
}

int main(void) {
  char dir;
  int i, j, n;
  int tot = 0;
  char buf[10];
  Pos knots[10];
  FILE* fp = fopen("input.txt", "r");
  for (i = 0; i < 10; i++) {
    knots[i].x = knots[i].y = 0;
  }
  tot += add(&knots[0]);
  while (fgets(buf, sizeof(buf), fp)) {
    buf[strlen(buf) - 1] = 0;
    sscanf(buf, "%c %d", &dir, &n);
    for (i = 1; i <= n; i++) {
      switch (dir) {
        case 'U':
          knots[0].y++;
          break;
        case 'D':
          knots[0].y--;
          break;
        case 'L':
          knots[0].x--;
          break;
        case 'R':
          knots[0].x++;
          break;
      }
      for (j = 1; j <= 9; j++) {
        int dx = abs(knots[j - 1].x - knots[j].x);
        int dy = abs(knots[j - 1].y - knots[j].y);
        if (dx >= 2 || dy >= 2) {
          if (knots[j].x > knots[j - 1].x) knots[j].x--;
          if (knots[j].x < knots[j - 1].x) knots[j].x++;
          if (knots[j].y > knots[j - 1].y) knots[j].y--;
          if (knots[j].y < knots[j - 1].y) knots[j].y++;
        }
      }
      tot += add(&knots[9]);
    }
  }
  printf("%d\n", tot);
  return 0;
}
