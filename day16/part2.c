#include <stdio.h>
#include <stdlib.h>
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
int i2m;

typedef struct valve {
  int rate;
  int nnb;
  int nbs[10];
  int i2;
} Valve;

Valve valves[100];
char in_fmt[] = "Valve %s has flow rate=%d; %*s %*s to %*s %[^\n]\n";

typedef struct entry {
  int t;
  int v;
} Entry;

Entry memo[52][52][32678];

int memo_get(int i, int j, int opened, int t) {
  if (memo[i-1][j-1][opened].t > t) {
    return -999;
  } else if (memo[i-1][j-1][opened].t < t) {
    return 0;
  } else {
    return memo[i-1][j-1][opened].v;
  }
}

void memo_set(int i, int j, int opened, int t, int v) {
  memo[i-1][j-1][opened].t = t;
  memo[i-1][j-1][opened].v = v;
}

int dp(int i, int fromi, int j, int fromj, int opened, int t) {
  int res = -999, ii, jj, k, tmp;
  int ni[6], oi[6], pi[6], nni = 0;
  int nj[6], oj[6], pj[6], nnj = 0;
  if (t <= 0) return 0;
  if (opened == (1 << i2m) - 1) return 0;
  tmp = memo_get(i, j, opened, t);
  if (tmp != 0) return tmp;
  for (k = 0; k < valves[i].nnb; k++) {
    if (valves[i].nbs[k] == fromi) continue;
    ni[nni] = valves[i].nbs[k];
    oi[nni] = pi[nni] = 0;
    nni++;
  }
  if (valves[i].rate > 0 && (opened & (1 << valves[i].i2)) == 0) {
    ni[nni] = i;
    oi[nni] = (1 << valves[i].i2);
    pi[nni] = valves[i].rate * (t - 1);
    nni++;
  }
  for (k = 0; k < valves[j].nnb; k++) {
    if (valves[j].nbs[k] == fromj) continue;
    nj[nnj] = valves[j].nbs[k];
    oj[nnj] = pj[nnj] = 0;
    nnj++;
  }
  if (valves[j].rate > 0 && (opened & (1 << valves[j].i2)) == 0) {
    nj[nnj] = j;
    oj[nnj] = (1 << valves[j].i2);
    pj[nnj] = valves[j].rate * (t - 1);
    nnj++;
  }
  for (ii = 0; ii < nni; ii++) {
    for (jj = 0; jj < nnj; jj++) {
      tmp = dp(ni[ii], i, nj[jj], j, opened | oi[ii] | oj[jj], t - 1);
      if (tmp < 0) continue;
      tmp += pi[ii] + pj[jj];
      if (oi[ii] == oj[jj]) tmp -= pi[ii];
      res = MAX(res, tmp);
    }
  }
  memo_set(i, j, opened, t, res);
  return res;
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
      valves[i].i2 = -999;
    }
    valves[i].nnb = 0;
    tok = strtok(buf2, ", ");
    while (tok) {
      valves[i].nbs[valves[i].nnb] = name_to_idx(tok);
      valves[i].nnb += 1;
      tok = strtok(NULL, ", ");
    }
  }
  i2m = i2;
  fclose(fp);
  printf("%d\n", dp(aai, 0, aai, 0, 0, 26));
}
