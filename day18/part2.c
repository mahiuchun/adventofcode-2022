#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MY_CUBE 1
#define MY_FREE 2
#define MY_TRAP 3
#define N 20

typedef struct cube {
  int x;
  int y;
  int z;
} Cube;

int adjacent(Cube *c1, Cube *c2) {
  int d = abs(c1->x - c2->x) + abs(c1->y - c2->y) + abs(c1->z - c2->z);
  return d == 1;
}

Cube parse(char *s) {
  Cube res;
  char *tok = strtok(s, ",");
  res.x = atoi(tok);
  tok = strtok(NULL, ",");
  res.y = atoi(tok);
  tok = strtok(NULL, ",");
  res.z = atoi(tok);
  return res;
}

typedef struct grid {
  char d[N][N][N];
} Grid;

Grid gg, tt;

int count_faces(Grid *g) {
  static Cube cubes[N * N * N + 5];
  int ncubes = 0, tot;
  int i, j, k;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
        if (g->d[i][j][k]) {
          cubes[ncubes].x = i;
          cubes[ncubes].y = j;
          cubes[ncubes].z = k;
          ncubes += 1;
        }
      }
    }
  }
  tot = 6 * ncubes;
  for (i = 0; i < ncubes; i++) {
    for (j = i + 1; j < ncubes; j++) {
      if (adjacent(&cubes[i], &cubes[j])) {
        tot -= 2;
      }
    }
  }
  return tot;
}

int dfs(int x, int y, int z) {
#define MY_TRY(dx, dy, dz)                                 \
  do {                                                     \
    if (dfs((x + (dx)), (y + (dy)), (z + (dz)))) return 1; \
  } while (0)
  if (x < 0 || x >= N) return 1;
  if (y < 0 || y >= N) return 1;
  if (z < 0 || z >= N) return 1;
  if (gg.d[x][y][z] == MY_CUBE) return 0;
  if (tt.d[x][y][z]) return 0;
  tt.d[x][y][z] = 1;
  MY_TRY(-1, 0, 0);
  MY_TRY(1, 0, 0);
  MY_TRY(0, -1, 0);
  MY_TRY(0, 1, 0);
  MY_TRY(0, 0, -1);
  MY_TRY(0, 0, 1);
#undef MY_TRY
  return 0;
}

int trapped(int x, int y, int z) {
  int i, j, k;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
        tt.d[i][j][k] = 0;
      }
    }
  }
  return !dfs(x, y, z);
}

void copy_trapped() {
  int i, j, k;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
        if (tt.d[i][j][k]) gg.d[i][j][k] = MY_TRAP;
      }
    }
  }
}

int main(void) {
  char buf[100];
  int i, j, k, tot;
  Cube cube;
  FILE *fp = fopen("input.txt", "r");
  while (fscanf(fp, "%s", buf) == 1) {
    cube = parse(buf);
    gg.d[cube.x][cube.y][cube.z] = MY_CUBE;
  }
  fclose(fp);
  tot = count_faces(&gg);
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++) {
      for (k = 0; k < N; k++) {
        if (gg.d[i][j][k] > 0) continue;
        if (trapped(i, j, k)) {
          copy_trapped();
          tot -= count_faces(&tt);
        }
      }
    }
  }
  printf("%d\n", tot);
}
