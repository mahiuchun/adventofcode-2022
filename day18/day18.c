#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

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

Cube cubes[3000];
int ncubes;

int main(void) {
  char buf[100];
  int i, j;
  int tot;
  FILE *fp = fopen("input.txt", "r");
  while (fscanf(fp, "%s", buf) == 1) {
    cubes[ncubes] = parse(buf);
    ncubes += 1;
  }
  fclose(fp);
  tot = 6 * ncubes;
  for (i = 0; i < ncubes; i++) {
    for (j = i + 1; j < ncubes; j++) {
      if (adjacent(&cubes[i], &cubes[j])) {
        tot -= 2;
      }
    }
  }
  printf("%d\n", tot);
}
