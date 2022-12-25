#include <ctype.h>
#include <stdio.h>
#include <string.h>

long long from_snafu(const char *s) {
  long long res = 0;
  long long power = 1, x;
  int i, n;
  n = strlen(s);
  for (i = n - 1; i >= 0; i--) {
    if (isdigit(s[i])) {
      x = s[i] - '0';
    } else if (s[i] == '-') {
      x = -1;
    } else if (s[i] == '=') {
      x = -2;
    } else {
      fprintf(stderr, "Something is wrong s=%s\n", s);
    }
    res += x * power;
    power *= 5;
  }
  return res;
}

void print_snafu(long long x) {
  if (x > 0) {
    long long y = x / 5;
    if (x % 5 >= 3) y += 1;
    print_snafu(y);
    putchar("012=-"[x % 5]);
  }
}

int main(void) {
  char buf[100];
  long long tot = 0, tmp;
  FILE *fp = fopen("input.txt", "r");
  while (fgets(buf, sizeof(buf), fp)) {
    buf[strlen(buf) - 1] = 0;
    tmp = from_snafu(buf);
    tot += tmp;
  }
  fclose(fp);
  print_snafu(tot);
  putchar('\n');
  return 0;
}
