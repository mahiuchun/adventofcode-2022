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
  int i, n;
  int tot = 0, dx, dy;
  char buf[10];
  Pos head, tail;
  FILE* fp = fopen("input.txt", "r");
  head.x = 0;
  head.y = 0;
  tail.x = 0;
  tail.y = 0;
  tot += add(&tail);
  while (fgets(buf, sizeof(buf), fp)) {
    buf[strlen(buf) - 1] = 0;
    sscanf(buf, "%c %d", &dir, &n);
    for (i = 1; i <= n; i++) {
      switch (dir) {
        case 'U':
          head.y++;
          break;
        case 'D':
          head.y--;
          break;
        case 'L':
          head.x--;
          break;
        case 'R':
          head.x++;
          break;
      }
      dx = abs(head.x - tail.x);
      dy = abs(head.y - tail.y);
      if (dx >= 2 || dy >= 2) {
        if (tail.x > head.x) tail.x--;
        if (tail.x < head.x) tail.x++;
        if (tail.y > head.y) tail.y--;
        if (tail.y < head.y) tail.y++;
      }
      tot += add(&tail);
    }
  }
  printf("%d\n", tot);
  return 0;
}
