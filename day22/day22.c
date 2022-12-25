#include <ctype.h>
#include <stdio.h>
#include <string.h>

typedef struct row {
  char d[500];
  int beg;
  int end;
  int ncols;
} Row;

Row map[250];
int nrows = 1;

char buf[1000];

int facing(int dr, int dc) {
  if (dr == 0 && dc == 1) {
    return 0;
  } else if (dr == 1 && dc == 0) {
    return 1;
  } else if (dr == 0 && dc == -1) {
    return 2;
  } else if (dr == -1 && dc == 0) {
    return 3;
  } else {
    printf("ERROR: dr=%d dc=%d\n", dr, dc);
    return -999;
  }
}

int main(void) {
  int i, j, n;
  char ltr;
  int r, c, dr = 0, dc = 1;
  FILE *fp = fopen("input.txt", "r");
  while (fgets(buf, sizeof(buf), fp)) {
    buf[strlen(buf) - 1] = 0;
    if (strlen(buf) == 0) {
      break;
    }
    strcpy(map[nrows].d, buf);
    map[nrows].end = strlen(buf);
    for (i = 0; i < map[nrows].end; i++) {
      if (!isspace(map[nrows].d[i])) {
        map[nrows].beg = i;
        break;
      }
    }
    map[nrows].ncols = map[nrows].end - map[nrows].beg;
    nrows += 1;
  }
  r = 1;
  c = map[r].beg;
  while (fscanf(fp, "%d%c", &n, &ltr) == 2) {
    int rnext, cnext;
    for (i = 0; i < n; i++) {
      if (dc != 0) {
        cnext = c + dc;
        if (cnext == map[r].end) cnext = map[r].beg;
        if (cnext < map[r].beg) cnext = map[r].end - 1;
        if (map[r].d[cnext] == '#') break;
        c = cnext;
      } else {
        rnext = r + dr;
        if (map[rnext].d[c] == 0 || map[rnext].d[c] == ' ') {
          for (j = r; map[j].d[c] != 0 && map[j].d[c] != ' '; j -= dr)
            ;
          rnext = j + dr;
        }
        if (map[rnext].d[c] == '#') break;
        r = rnext;
      }
    }
    rnext = dr;
    cnext = dc;
    switch (ltr) {
      case 'L':
        dr = -cnext;
        dc = rnext;
        break;
      case 'R':
        dr = cnext;
        dc = -rnext;
        break;
    }
  }
  fclose(fp);
  printf("%d\n", 1000 * r + 4 * (c + 1) + facing(dr, dc));
}
