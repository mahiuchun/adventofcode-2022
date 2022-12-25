#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 14

int tally[26];
char buf[10000];

int main(void) {
  int i, j, n;
  FILE *fp = fopen("input.txt", "r");
  fgets(buf, sizeof(buf), fp);
  n = strlen(buf);
  for (i = 0; i < n; i++) {
    tally[buf[i] - 'a']++;
    if (i >= N) {
      tally[buf[i - N] - 'a']--;
    }
    if (i >= (N - 1)) {
      for (j = 0; j < 26; j++) {
        if (tally[j] > 1) break;
      }
      if (j == 26) {
        printf("%d\n", i + 1);
        break;
      }
    }
  }
  fclose(fp);
}
