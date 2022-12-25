#include <stdio.h>
#include <string.h>

#define W 7
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct rock {
  int w;
  int h;
  char data[10];
} Rock;

Rock types[5];
char buf[15000];
char map[2022 * 4][W];

int collides(int tt, int x, int y) {
  int i, j;
  if (x < 0 || x + types[tt].w > W) return 1;
  if (y < 0) return 1;
  for (i = 0; i < types[tt].h; i++) {
    for (j = 0; j < types[tt].w; j++) {
      if (types[tt].data[i * types[tt].w + j] == '#' &&
          map[y + i][x + j] == '#') {
        return 1;
      }
    }
  }
  return 0;
}

int main(void) {
  int highest = 0, len, t, tt, jet = 0;
  int x, y, i, j;
  FILE *fp = fopen("input.txt", "r");
  memset(map, '.', sizeof(map));
  fscanf(fp, "%s", buf);
  fclose(fp);
  len = strlen(buf);
  types[0].w = 4;
  types[0].h = 1;
  strcpy(types[0].data, "####");
  types[1].w = 3;
  types[1].h = 3;
  strcpy(types[1].data, ".#.###.#.");
  types[2].w = 3;
  types[2].h = 3;
  strcpy(types[2].data, "###..#..#");
  types[3].w = 1;
  types[3].h = 4;
  strcpy(types[3].data, "####");
  types[4].w = 2;
  types[4].h = 2;
  strcpy(types[4].data, "####");
  for (t = 0; t < 2022; t++) {
    tt = t % 5;
    x = 2;
    y = highest + 3;
    while (1) {
      /* pushed */
      if (buf[jet] == '<') {
        x -= 1;
        if (collides(tt, x, y)) x += 1;
      } else {
        x += 1;
        if (collides(tt, x, y)) x -= 1;
      }
      jet += 1;
      jet %= len;
      /* falling */
      y -= 1;
      if (collides(tt, x, y)) {
        y += 1;
        break;
      }
    }
    for (i = 0; i < types[tt].h; i++) {
      for (j = 0; j < types[tt].w; j++) {
        if (types[tt].data[i * types[tt].w + j] == '#') {
          map[y + i][x + j] = '#';
        }
      }
    }
    highest = MAX(highest, y + types[tt].h);
  }
  printf("%d\n", highest);
}
