#include <stdio.h>
#include <string.h>

#define B 7
#define X 1000000000000LL
#define Y 2022
#define W 7
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct rock {
  int w;
  int h;
  char data[10];
} Rock;

Rock types[5];
char buf[15000];

typedef struct back {
  int y;
  int t;
  char map[W * 4];
} Back;

Back back[15000];
char map[Y * 4][W];

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

void print0(long long x) {
  if (x >= 10) {
    print0(x / 10);
  }
  putchar('0' + x % 10);
}

void print(long long x) {
  print0(x);
  putchar('\n');
}

int main(void) {
  long long res = 0;
  int highest = 0;
  int len, t, tt, jet = 0;
  int nt, period, found = 0;
  long long nx, np;
  int x, y, i, j;
  char minimap[W * B];
  FILE *fp = fopen("input.txt", "r");
  memset(map, '.', sizeof(map));
  fscanf(fp, "%s", buf);
  fclose(fp);
  len = strlen(buf);
  for (i = 0; i < len; i++) {
    back[i].t = -1;
  }
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
  nt = Y;
  for (t = 0; t < nt; t++) {
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
    if (found) continue;
    y = highest - B + 1;
    if (y < 0) continue;
    for (j = 0; j < W; j++) {
      for (i = 0; i < B; i++) {
        if (map[y + i][x + j] == '#') {
          break;
        }
      }
      if (x == 4) break;
      for (i = 0; i < B; i++) {
        minimap[i * W + j] = map[y + i][x + j];
      }
    }
    if (j == W) {
      if (back[jet].t >= 0) {
        if (!strncmp(back[jet].map, minimap, W * B)) {
          period = t - back[jet].t;
          nx = X;
          nx -= (t + 1);
          np = nx / period;
          res = np * (y - back[jet].y);
          nx %= period;
          nt = nx + t + 1;
          found = 1;
        }
      } else {
        back[jet].y = y;
        back[jet].t = t;
        strncpy(back[jet].map, minimap, W * B);
      }
    }
  }
  if (!found) printf("NOT FOUND!\n");
  res += highest;
  print(res);
}
