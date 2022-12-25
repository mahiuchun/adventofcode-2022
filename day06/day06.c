#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tally[26];
char buf[10000];

int main(void) {
  int i, j, n;
  FILE *fp = fopen("input.txt", "r");
  fgets(buf, sizeof(buf), fp);
  n = strlen(buf);
  for (i = 0; i < n; i++) {
    tally[buf[i] - 'a']++;
    if (i >= 4) {
      tally[buf[i - 4] - 'a']--;
    }
    if (i >= 3) {
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
