#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char line[100];

int main(void) {
  char ins[10];
  int v, x = 1;
  int cycle, busy = 0, pos;
  FILE *fp = fopen("input.txt", "r");
  for (cycle = 1; cycle <= 240; cycle++) {
    if (!busy) {
      fgets(line, sizeof(line), fp);
      sscanf(line, "%s %d\n", ins, &v);
      if (!strcmp(ins, "addx")) {
        busy = 2;
      } else {
        busy = 1;
      }
    }
    pos = (cycle - 1) % 40;
    if (abs(pos - x) <= 1) {
      putchar('#');
    } else {
      putchar('.');
    }
    if (cycle % 40 == 0) {
      putchar('\n');
    }
    if (busy > 0) {
      busy -= 1;
      if (busy == 0 && !strcmp(ins, "addx")) {
        x += v;
      }
    }
  }
  fclose(fp);
  return 0;
}
