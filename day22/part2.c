#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

typedef struct row {
  char d[500];
  int beg;
  int end;
  int ncols;
} Row;

Row map[250];
int nrows = 0;

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

typedef struct rc {
  int r;
  int c;
  int dr;
  int dc;
} RC;

#if defined(SAMPLE_INPUT)
RC wrap(int r, int c, int dr, int dc, int side) {
  RC rc;
  int rlocal, clocal;
  if (r < 0 && 2 * side <= c && c < 3 * side && dr == -1) {
    clocal = c - 2 * side;
    clocal = side - clocal - 1;
    rc.r = side;
    rc.c = clocal;
    rc.dr = -dr;
    rc.dc = dc;
  } else if (0 <= r && r < side && c < 2 * side && dc == -1) {
    rlocal = r;
    clocal = rlocal;
    rc.r = side;
    rc.c = side + clocal;
    rc.dr = -dc;
    rc.dc = dr;
  } else if (0 <= r && r < side && c >= 3 * side && dc == 1) {
    rlocal = r;
    rlocal = side - rlocal - 1;
    rc.r = 2 * side + rlocal;
    rc.c = 4 * side - 1;
    rc.dr = dr;
    rc.dc = -dc;
  } else if (r < side && 0 <= c && c < side && dr == -1) {
    clocal = c;
    clocal = side - clocal - 1;
    rc.r = 0;
    rc.c = clocal;
    rc.dr = -dr;
    rc.dc = dc;
  } else if (r < side && side <= c && c < 2 * side && dr == -1) {
    clocal = c - side;
    rlocal = clocal;
    rc.r = rlocal;
    rc.c = 2 * side;
    rc.dr = dc;
    rc.dc = -dr;
  } else if (side <= r && r < 2 * side && c < 0 && dc == -1) {
    rlocal = r - side;
    clocal = side - rlocal - 1;
    rc.r = 3 * side - 1;
    rc.c = 3 * side + clocal;
    rc.dr = dc;
    rc.dc = dr;
  } else if (side <= r && r < 2 * side && c >= 3 * side && dc == 1) {
    rlocal = r - side;
    clocal = side - rlocal - 1;
    rc.r = 2 * side;
    rc.c = 3 * side + clocal;
    rc.dr = dc;
    rc.dc = dr;
  } else if (r >= 2 * side && 0 <= c && c < side && dr == 1) {
    clocal = c;
    clocal = side - clocal - 1;
    rc.r = 3 * side - 1;
    rc.c = 2 * side + clocal;
    rc.dr = -dr;
    rc.dc = dc;
  } else if (r >= 2 * side && side <= c && c < 2 * side && dr == 1) {
    clocal = c - side;
    rlocal = side - clocal - 1;
    rc.r = 2 * side + rlocal;
    rc.c = 2 * side;
    rc.dr = dc;
    rc.dc = dr;
  } else if (r < 2 * side && 3 * side <= c && c < 4 * side && dr == -1) {
    clocal = c - 3 * side;
    rlocal = side - clocal - 1;
    rc.r = side + rlocal;
    rc.c = 3 * side;
    rc.dr = dc;
    rc.dc = dr;
  } else if (2 * side <= r && r < 3 * side && c < 2 * side && dc == -1) {
    rlocal = r - 2 * side;
    clocal = side - rlocal - 1;
    rc.r = 2 * side - 1;
    rc.c = side + clocal;
    rc.dr = dc;
    rc.dc = dr;
  } else if (2 * side <= r && r < 3 * side && c >= 4 * side && dc == 1) {
    rlocal = r - 2 * side;
    rlocal = side - rlocal - 1;
    rc.r = rlocal;
    rc.c = 3 * side - 1;
    rc.dr = dr;
    rc.dc = -dc;
  } else if (r >= 3 * side && 2 * side <= c && c < 3 * side && dr == 1) {
    clocal = c - 2 * side;
    clocal = side - clocal - 1;
    rc.r = 2 * side - 1;
    rc.c = clocal;
    rc.dr = -dr;
    rc.dc = dc;
  } else if (r >= 3 * side && 3 * side <= c && c < 4 * side && dr == 1) {
    clocal = c - 3 * side;
    rlocal = side - clocal - 1;
    rc.r = side + rlocal;
    rc.c = 0;
    rc.dr = dc;
    rc.dc = dr;
  } else {
    rc.r = r;
    rc.c = c;
    rc.dr = dr;
    rc.dc = dc;
  }
  return rc;
}
#else
RC wrap(int r, int c, int dr, int dc, int side) {
  /* specific to my input */
  RC rc;
  int rlocal = -999, clocal = -999;
  if (r < 0 && side <= c && c < 2 * side && dr == -1) {
    clocal = c - side;
    rlocal = clocal;
    rc.r = 3 * side + rlocal;
    rc.c = 0;
    rc.dr = 0;
    rc.dc = 1;
  } else if (r < 0 && 2 * side <= c && c < 3 * side && dr == -1) {
    clocal = c - 2 * side;
    rc.r = 4 * side - 1;
    rc.c = clocal;
    rc.dr = -1;
    rc.dc = 0;
  } else if (0 <= r && r < side && c < side && dc == -1) {
    rlocal = r;
    rlocal = side - rlocal - 1;
    rc.r = 2 * side + rlocal;
    rc.c = 0;
    rc.dr = 0;
    rc.dc = 1;
  } else if (0 <= r && r < side && c >= 3 * side && dc == 1) {
    rlocal = r;
    rlocal = side - rlocal - 1;
    rc.r = 2 * side + rlocal;
    rc.c = 2 * side - 1;
    rc.dr = 0;
    rc.dc = -1;
  } else if (r >= side && 2 * side <= c && c < 3 * side && dr == 1) {
    clocal = c - 2 * side;
    rlocal = clocal;
    rc.r = side + rlocal;
    rc.c = 2 * side - 1;
    rc.dr = 0;
    rc.dc = -1;
  } else if (side <= r && r < 2 * side && c < side && dc == -1) {
    rlocal = r - side;
    clocal = rlocal;
    rc.r = 2 * side;
    rc.c = clocal;
    rc.dr = 1;
    rc.dc = 0;
  } else if (side <= r && r < 2 * side && c >= 2 * side && dc == 1) {
    rlocal = r - side;
    clocal = rlocal;
    rc.r = side - 1;
    rc.c = 2 * side + clocal;
    rc.dr = -1;
    rc.dc = 0;
  } else if (r < 2 * side && 0 <= c && c < side && dr == -1) {
    clocal = c;
    rlocal = clocal;
    rc.r = side + rlocal;
    rc.c = side;
    rc.dr = 0;
    rc.dc = 1;
  } else if (2 * side <= r && r < 3 * side && c < 0 && dc == -1) {
    rlocal = r - 2 * side;
    rlocal = side - rlocal - 1;
    rc.r = rlocal;
    rc.c = side;
    rc.dr = 0;
    rc.dc = 1;
  } else if (2 * side <= r && r < 3 * side && c >= 2 * side && dc == 1) {
    rlocal = r - 2 * side;
    rlocal = side - rlocal - 1;
    rc.r = rlocal;
    rc.c = 3 * side - 1;
    rc.dr = 0;
    rc.dc = -1;
  } else if (r >= 3 * side && side <= c && c < 2 * side && dr == 1) {
    clocal = c - side;
    rlocal = clocal;
    rc.r = 3 * side + rlocal;
    rc.c = side - 1;
    rc.dr = 0;
    rc.dc = -1;
  } else if (3 * side <= r && r < 4 * side && c < 0 && dc == -1) {
    rlocal = r - 3 * side;
    clocal = rlocal;
    rc.r = 0;
    rc.c = side + clocal;
    rc.dr = 1;
    rc.dc = 0;
  } else if (3 * side <= r && r < 4 * side && c >= side && dc == 1) {
    rlocal = r - 3 * side;
    clocal = rlocal;
    rc.r = 3 * side - 1;
    rc.c = side + clocal;
    rc.dr = -1;
    rc.dc = 0;
  } else if (r >= 4 * side && 0 <= c && c < side && dr == 1) {
    clocal = c;
    rc.r = 0;
    rc.c = 2 * side + clocal;
    rc.dr = 1;
    rc.dc = 0;
  } else {
    rc.r = r;
    rc.c = c;
    rc.dr = dr;
    rc.dc = dc;
  }
  return rc;
}
#endif

int main(void) {
  int i, n, side, area = 0;
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
    area += map[nrows].ncols;
    nrows += 1;
  }
  area /= 6;
  side = (int)sqrt(area);
  r = 0;
  c = map[r].beg;
  while (fscanf(fp, "%d%c", &n, &ltr) == 2) {
    int rnext, cnext;
    RC rc;
    for (i = 0; i < n; i++) {
      cnext = c + dc;
      rnext = r + dr;
      rc = wrap(rnext, cnext, dr, dc, side);
      if (map[rc.r].d[rc.c] == '#') break;
      r = rc.r;
      c = rc.c;
      dr = rc.dr;
      dc = rc.dc;
    }
    if (map[r].d[c] != '.') {
      fprintf(stderr, "Something is wrong r=%d, c=%d\n", r, c);
      break;
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
  printf("%d\n", 1000 * (r + 1) + 4 * (c + 1) + facing(dr, dc));
}
