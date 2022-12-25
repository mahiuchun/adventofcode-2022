#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct sensor {
  int x;
  int y;
  int bx;
  int by;
  int d;
} Sensor;

Sensor sensors[30];

typedef struct interval {
  int min;
  int max;
} Int;

Int ints[30];

int intervalcmp(const void *v1, const void *v2) {
  const Int *i1 = v1;
  const Int *i2 = v2;
  if (i1->min < i2->min) {
    return -1;
  } else if (i1->min > i2->min) {
    return 1;
  } else {
    return 0;
  }
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MOST 4000000

int main(void) {
  int i = 0, j, k, m, n;
  int sx, sy, bx, by, dd;
  int minx, maxx;
  FILE *fp = fopen("input.txt", "r");
  while (!feof(fp)) {
    fscanf(fp, "Sensor at x=%d, y=%d: closest beacon is at x=%d, y=%d\n", &sx,
           &sy, &bx, &by);
    sensors[i].x = sx;
    sensors[i].y = sy;
    sensors[i].bx = bx;
    sensors[i].by = by;
    sensors[i].d = abs(sx - bx) + abs(sy - by);
    i += 1;
  }
  m = i;
  fclose(fp);
  for (j = 0; j <= MOST; j++) {
    k = 0;
    minx = 987654321;
    maxx = -987654321;
    for (i = 0; i < m; i++) {
      dd = sensors[i].d - abs(sensors[i].y - j);
      if (dd >= 0) {
        ints[k].min = sensors[i].x - dd;
        ints[k].max = sensors[i].x + dd;
        minx = MIN(minx, ints[k].min);
        maxx = MAX(maxx, ints[k].max);
        k += 1;
      }
    }
    n = k;
    if (n == 0) continue;
    if (minx > 0) {
      bx = 0;
      by = j;
      goto found;
    } else if (maxx < MOST) {
      bx = MOST;
      by = j;
      goto found;
    }
    qsort(ints, n, sizeof(Int), intervalcmp);
    minx = ints[0].min;
    maxx = ints[0].max;
    for (i = 0; i < n - 1; i++) {
      if (ints[i + 1].min > maxx + 1) {
        bx = maxx + 1;
        by = j;
        goto found;
      } else {
        maxx = MAX(maxx, ints[i + 1].max);
      }
    }
  }
  printf("NOT FOUND!\n");
found:
  printf("%lld\n", 4000000LL * bx + by);
}
