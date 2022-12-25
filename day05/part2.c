#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
  int top;
  char elems[500];
} stack;

stack* make_stack() {
  stack* st = malloc(sizeof(stack));
  st->top = -1;
  return st;
}

void stack_push(stack* st, char c) { st->elems[++(st->top)] = c; }

char stack_top(stack* st) { return st->elems[st->top]; }

char stack_pop(stack* st) { return st->elems[(st->top)--]; }

void stack_rev(stack* st) {
  int i = 0;
  int j = st->top;
  char t;
  while (i < j) {
    t = st->elems[i];
    st->elems[i] = st->elems[j];
    st->elems[j] = t;
    i++;
    j--;
  }
}

void stack_rev2(stack* st, int n) {
  int i = st->top - n + 1;
  int j = st->top;
  char t;
  while (i < j) {
    t = st->elems[i];
    st->elems[i] = st->elems[j];
    st->elems[j] = t;
    i++;
    j--;
  }
}

stack* stacks[10]; /* input dependent? */

int main() {
  int i, j, stage = 1, n;
  int num, from, to;
  char line[1000];
  FILE* fp = fopen("input.txt", "r");
  for (i = 1; i <= 9; i++) {
    stacks[i] = make_stack();
    /* stack_push(stacks[i], '?'); */
  }
  while (fgets(line, sizeof(line), fp)) {
    n = strlen(line);
    line[--n] = 0;
    if (n == 0) {
      for (i = 1; i <= 9; i++) {
        stack_rev(stacks[i]);
      }
      stage++;
      continue;
    }
    if (stage == 1) {
      for (i = 0; i < n; i++) {
        if (isalpha(line[i])) {
          j = (i + 3) / 4;
          stack_push(stacks[j], line[i]);
        }
      }
    } else {
      sscanf(line, "move %d from %d to %d", &num, &from, &to);
      for (i = 0; i < num; i++) {
        stack_push(stacks[to], stack_pop(stacks[from]));
      }
      stack_rev2(stacks[to], num);
    }
  }
  fclose(fp);
  for (i = 1; i <= 9; i++) {
    putchar(stack_top(stacks[i]));
  }
  putchar('\n');
}
