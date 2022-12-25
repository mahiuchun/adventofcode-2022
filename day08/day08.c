#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char map[105][105];

int main(void) {
  int i = 0, j, k;
  int m, n;
  int tot = 0;
  FILE *fp = fopen("input.txt", "r");
  while (fgets(map[i], 105, fp)) {
    map[i][strlen(map[i]) - 1] = 0;
    i++;
  }
  m = i;
  n = strlen(map[0]);
  for (i = 0; i < m; i++) {
    for (j = 0; j < n; j++) {
      for (k = 0; k < j; k++) {
        if (map[i][k] >= map[i][j]) {
          goto cont1;
        }
      }
      goto vis;
    cont1:
      for (k = j + 1; k < n; k++) {
        if (map[i][k] >= map[i][j]) {
          goto cont2;
        }
      }
      goto vis;
    cont2:
      for (k = 0; k < i; k++) {
        if (map[k][j] >= map[i][j]) {
          goto cont3;
        }
      }
      goto vis;
    cont3:
      for (k = i + 1; k < m; k++) {
        if (map[k][j] >= map[i][j]) {
          goto hid;
        }
      }
      goto vis;
    hid:
      continue;
    vis:
      tot += 1;
    }
  }

  printf("%d\n", tot);
  return 0;
}
