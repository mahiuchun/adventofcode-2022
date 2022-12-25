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

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define Y 2000000

int main(void) {
  int i = 0, j, m;
  int tot = 0;
  int sx, sy, bx, by;
  int dd, minx = 987654321, maxx = -987654321;
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
  for (i = 0; i < m; i++) {
    dd = sensors[i].d - abs(sensors[i].y - Y);
    if (dd >= 0) {
      minx = MIN(minx, sensors[i].x - dd);
      maxx = MAX(maxx, sensors[i].x + dd);
    }
  }
  for (j = minx; j <= maxx; j++) {
    for (i = 0; i < m; i++) {
      if (sensors[i].bx == j && sensors[i].by == Y) {
        break;
      }
      dd = abs(sensors[i].x - j) + abs(sensors[i].y - Y);
      if (dd <= sensors[i].d) {
        tot += 1;
        break;
      }
    }
  }
  printf("%d\n", tot);
}
