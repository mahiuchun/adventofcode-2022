#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct elf {
  int x;
  int y;
  int nx;
  int ny;
} Elf;

#define NADJ 8
#define NDIR 4

Elf elves[5555];
int nelves;
Elf adj[NADJ];
int dir_dx[] = {0, 0, -1, 1};
int dir_dy[] = {-1, 1, 0, 0};
int dir_beg[] = {1, 5, 3, 7};
int dir_end[] = {4, 0, 6, 2};
int dir = 0;

#define R 500
#define MY_ELF 10

typedef struct table {
  char d[2 * R + 1][2 * R + 1];
  int maxx;
  int minx;
  int maxy;
  int miny;
} Table;

void table_clear(Table *t) {
  int i, j;
  for (i = t->miny; i <= t->maxy; i++) {
    for (j = t->minx; j <= t->maxx; j++) {
      t->d[i][j] = 0;
    }
  }
  t->maxx = t->minx = t->maxy = t->miny = R;
}

int table_get(Table *t, int x, int y) { return t->d[y + R][x + R]; }

void table_set(Table *t, int x, int y, int v) {
  x += R;
  y += R;
  t->maxx = MAX(t->maxx, x);
  t->minx = MIN(t->minx, x);
  t->maxy = MAX(t->maxy, y);
  t->miny = MIN(t->miny, y);
  t->d[y][x] = (char)v;
}

Table tbl;

char buf[1000];

void init_adj(void) {
  adj[0].x = 1;
  adj[0].y = 0;
  adj[1].x = 1;
  adj[1].y = -1;
  adj[2].x = 0;
  adj[2].y = -1;
  adj[3].x = -1;
  adj[3].y = -1;
  adj[4].x = -1;
  adj[4].y = 0;
  adj[5].x = -1;
  adj[5].y = 1;
  adj[6].x = 0;
  adj[6].y = 1;
  adj[7].x = 1;
  adj[7].y = 1;
}

int main(void) {
  int i, j, k, n, x, y = 0, dd;
  int maxx, minx, maxy, miny;
  FILE *fp = fopen("input.txt", "r");
  init_adj();
  while (fgets(buf, sizeof(buf), fp)) {
    buf[strlen(buf) - 1] = 0;
    n = strlen(buf);
    for (x = 0; x < n; x++) {
      if (buf[x] == '#') {
        elves[nelves].x = x;
        elves[nelves].y = y;
        nelves += 1;
      }
    }
    y += 1;
  }
  n = 10;
  while (n--) {
    table_clear(&tbl);
    for (i = 0; i < nelves; i++) {
      table_set(&tbl, elves[i].x, elves[i].y, MY_ELF);
    }
    /* first half */
    for (i = 0; i < nelves; i++) {
      elves[i].nx = elves[i].x;
      elves[i].ny = elves[i].y;
      for (j = 0; j < NADJ; j++) {
        if (table_get(&tbl, elves[i].x + adj[j].x, elves[i].y + adj[j].y) ==
            MY_ELF) {
          break;
        }
      }
      if (j == NADJ) continue;
      dd = dir;
      for (j = 0; j < NDIR; j++) {
        for (k = dir_beg[dd]; k != dir_end[dd]; k += 1, k %= NADJ) {
          if (table_get(&tbl, elves[i].x + adj[k].x, elves[i].y + adj[k].y) ==
              MY_ELF) {
            break;
          }
        }
        if (k == dir_end[dd]) {
          elves[i].nx = elves[i].x + dir_dx[dd];
          elves[i].ny = elves[i].y + dir_dy[dd];
          table_set(&tbl, elves[i].nx, elves[i].ny,
                    table_get(&tbl, elves[i].nx, elves[i].ny) + 1);
          break;
        }
        dd += 1;
        dd %= NDIR;
      }
    }
    /* second half */
    for (i = 0; i < nelves; i++) {
      if (elves[i].nx == elves[i].x && elves[i].ny == elves[i].y) {
        continue;
      }
      if (table_get(&tbl, elves[i].nx, elves[i].ny) == 1) {
        elves[i].x = elves[i].nx;
        elves[i].y = elves[i].ny;
      }
    }
    dir += 1;
    dir %= NDIR;
    maxx = maxy = -987654321;
    minx = miny = 987654321;
    for (i = 0; i < nelves; i++) {
      maxx = MAX(maxx, elves[i].x);
      minx = MIN(minx, elves[i].x);
      maxy = MAX(maxy, elves[i].y);
      miny = MIN(miny, elves[i].y);
    }
  }
  printf("%d\n", (maxx - minx + 1) * (maxy - miny + 1) - nelves);
  fclose(fp);
}
