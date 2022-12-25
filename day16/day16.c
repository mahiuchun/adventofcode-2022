#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int last;
int name_to_idx(char name[2]) {
  static int indices[26][26];
  if (indices[name[0] - 'A'][name[1] - 'A'] > 0) {
    return indices[name[0] - 'A'][name[1] - 'A'];
  } else {
    last += 1;
    indices[name[0] - 'A'][name[1] - 'A'] = last;
    return last;
  }
}
int i2_to_i[100];

typedef struct valve {
  int rate;
  int nnb;
  int nbs[10];
  int i2;
} Valve;

Valve valves[100];
char in_fmt[] = "Valve %s has flow rate=%d; %*s %*s to %*s %[^\n]\n";

int dp(int i, int opened, int t) {
  /* 32768 is just enough for my input ... */
  static int memo[100][32768][31];
  int res = 0, j, tmp;
  if (t <= 0) return 0;
  if (memo[i][opened][t] > 0) return memo[i][opened][t];
  if (valves[i].i2 >= 0 && (opened & (1 << valves[i].i2)) == 0) {
    res = dp(i, opened | (1 << valves[i].i2), t - 1) + valves[i].rate * (t - 1);
  }
  for (j = 0; j < valves[i].nnb; j++) {
    tmp = dp(valves[i].nbs[j], opened, t - 1);
    res = MAX(res, tmp);
  }
  return (memo[i][opened][t] = res);
}

int main(void) {
  int i, i2 = 0, rate, aai, best;
  char buf1[5];
  char buf2[100];
  char *tok;
  FILE *fp = fopen("input.txt", "r");
  while (fscanf(fp, in_fmt, buf1, &rate, buf2) == 3) {
    i = name_to_idx(buf1);
    if (!strcmp(buf1, "AA")) aai = i;
    valves[i].rate = rate;
    if (rate > 0) {
      valves[i].i2 = i2;
      i2_to_i[i2] = i;
      i2 += 1;
    } else {
      valves[i].i2 = -1;
    }
    valves[i].nnb = 0;
    tok = strtok(buf2, ", ");
    while (tok) {
      valves[i].nbs[valves[i].nnb] = name_to_idx(tok);
      valves[i].nnb += 1;
      tok = strtok(NULL, ", ");
    }
  }
  fclose(fp);
  printf("%d\n", dp(aai, 0, 30));
}
