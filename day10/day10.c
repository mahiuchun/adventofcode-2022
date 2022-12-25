#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char line[100];

int main(void) {
  char ins[10];
  int i, v, x = 1;
  int cycle = 0, tot = 0;
  FILE *fp = fopen("input.txt", "r");
  while (fgets(line, sizeof(line), fp)) {
    sscanf(line, "%s %d\n", ins, &v);
    if (!strcmp(ins, "addx")) {
      for (i = 1; i <= 2; i++) {
        cycle += 1;
        if ((cycle - 20) % 40 == 0) {
          tot += x * cycle;
        }
      }
      x += v;
    } else {
      cycle += 1;
      if ((cycle - 20) % 40 == 0) {
        tot += x * cycle;
      }
    }
  }
  fclose(fp);
  printf("%d\n", tot);
  return 0;
}
