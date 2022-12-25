#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pos {
  int x;
  int y;
} Pos;

char map[500][1000];
int maxy;

Pos parse_pos(char *s) {
  char *endp;
  Pos r;
  r.x = (int)strtol(s, &endp, 10);
  r.y = atoi(endp + 1);
  if (r.y > maxy) maxy = r.y;
  return r;
}

void swap(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

void add_to_map(Pos p1, Pos p2) {
  int i;
  if (p1.x > p2.x) swap(&p1.x, &p2.x);
  if (p1.y > p2.y) swap(&p1.y, &p2.y);
  if (p1.x == p2.x) {
    for (i = p1.y; i <= p2.y; i++) {
      map[i][p1.x] = '#';
    }
  } else {
    for (i = p1.x; i <= p2.x; i++) {
      map[p1.y][i] = '#';
    }
  }
}

void process(char *s) {
  char *tok;
  Pos p1, p2;
  int state = 0;
  tok = strtok(s, " ");
  while (tok) {
    if (!strcmp(tok, "->")) {
      tok = strtok(NULL, " ");
      continue;
    }
    if (state == 0) {
      p1 = parse_pos(tok);
      state++;
    } else if (state == 1) {
      p2 = parse_pos(tok);
      state++;
      add_to_map(p1, p2);
    } else {
      p1 = p2;
      p2 = parse_pos(tok);
      add_to_map(p1, p2);
    }
    tok = strtok(NULL, " ");
  }
}

int main(void) {
  int tot = 0;
  int sx, sy;
  char buf[1000];
  FILE *fp = fopen("input.txt", "r");
  memset(map, '.', sizeof(map));
  while (fgets(buf, sizeof(buf), fp)) {
    buf[strlen(buf) - 1] = 0;
    process(buf);
  }
  fclose(fp);
  while (1) {
    sx = 500;
    sy = 0;
    while (1) {
      sy += 1;
      if (sy > maxy) goto endless;
      if (map[sy - 1][sx] == '.' && map[sy][sx] != '.') {
        if (map[sy][sx - 1] == '.') {
          sx -= 1;
        } else if (map[sy][sx + 1] == '.') {
          sx += 1;
        } else {
          map[sy - 1][sx] = 'o';
          break;
        }
      }
    }
    tot += 1;
  }
endless:
  printf("%d\n", tot);
  return 0;
}
