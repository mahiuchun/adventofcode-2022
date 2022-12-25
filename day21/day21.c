#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry {
  char key[5];
  char val[20];
} Entry;

int entry_cmp(const void *v1, const void *v2) {
  const Entry *e1 = v1;
  const Entry *e2 = v2;
  return strcmp(e1->key, e2->key);
}

Entry entries[2000];
int len;

Entry *find_entry(const char *key) {
  Entry dummy;
  strcpy(dummy.key, key);
  strcpy(dummy.val, "");
  return bsearch(&dummy, entries, len, sizeof(Entry), entry_cmp);
}

long long yell(const char *key) {
  Entry *e = find_entry(key);
  if (isdigit(e->val[0])) {
    return atoi(e->val);
  } else {
    char buf[20], op;
    char *tok, *k1, *k2;
    long long i1, i2;
    strcpy(buf, e->val);
    k1 = strtok(buf, " ");
    tok = strtok(NULL, " ");
    op = *tok;
    k2 = strtok(NULL, " ");
    i1 = yell(k1);
    i2 = yell(k2);
    switch (op) {
      case '+':
        return i1 + i2;
      case '-':
        return i1 - i2;
      case '*':
        return i1 * i2;
      case '/':
        return i1 / i2;
    }
  }
  return -999;
}

int main(void) {
  char line[100];
  char *tok;
  FILE *fp = fopen("input.txt", "r");
  while (fgets(line, sizeof(line), fp)) {
    line[strlen(line) - 1] = 0;
    tok = strtok(line, ":");
    strcpy(entries[len].key, tok);
    tok = strtok(NULL, ":");
    strcpy(entries[len].val, tok + 1);
    len += 1;
  }
  fclose(fp);
  qsort(entries, len, sizeof(Entry), entry_cmp);
  printf("%lld\n", yell("root"));
}
