#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

char map[105][105];

int main(void) {
  int i = 0, j, k;
  int m, n;
  int best = 0, score;
  int du, dl, dr, dd;
  FILE *fp = fopen("input.txt", "r");
  while (fgets(map[i], 105, fp)) {
    map[i][strlen(map[i]) - 1] = 0;
    i++;
  }
  m = i;
  n = strlen(map[0]);
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      for (k = j - 1; k >= 0; k--) {
        if (map[i][k] >= map[i][j]) {
          break;
        }
      }
      dl = j - MAX(k, 0);
      for (k = j + 1; k < n; k++) {
        if (map[i][k] >= map[i][j]) {
          break;
        }
      }
      dr = MIN(k, n - 1) - j;
      for (k = i - 1; k >= 0; k--) {
        if (map[k][j] >= map[i][j]) {
          break;
        }
      }
      du = i - MAX(k, 0);
      for (k = i + 1; k < m; k++) {
        if (map[k][j] >= map[i][j]) {
          break;
        }
      }
      dd = MIN(k, m - 1) - i;
      score = du * dl * dr * dd;
      best = MAX(score, best);
    }
  }

  printf("%d\n", best);
  return 0;
}
