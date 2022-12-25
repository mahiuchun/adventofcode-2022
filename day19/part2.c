#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define T 32

typedef struct res {
  int ore;
  int clay;
  int obsidian;
  int geode;
} Res;

void zero_res(Res *r) { r->ore = r->clay = r->obsidian = r->geode = 0; }

void print_res(Res *r) {
  printf("%d %d %d %d\n", r->ore, r->clay, r->obsidian, r->geode);
}

int eq_res(Res *r1, Res *r2) {
  return (r1->ore == r2->ore) && (r1->clay == r2->clay) &&
         (r1->obsidian == r2->obsidian) && (r1->geode == r2->geode);
}

typedef struct bp {
  Res ore;
  Res clay;
  Res obsidian;
  Res geode;
  int max_ore;
} BP;

BP parse_bp(FILE *fp) {
  BP bp;
  zero_res(&bp.ore);
  zero_res(&bp.clay);
  zero_res(&bp.obsidian);
  zero_res(&bp.geode);
  fscanf(fp,
         " Each ore robot costs %d ore."
         " Each clay robot costs %d ore."
         " Each obsidian robot costs %d ore and %d clay."
         " Each geode robot costs %d ore and %d obsidian.\n",
         &bp.ore.ore, &bp.clay.ore, &bp.obsidian.ore, &bp.obsidian.clay,
         &bp.geode.ore, &bp.geode.obsidian);
  bp.max_ore = 0;
  bp.max_ore = MAX(bp.max_ore, bp.clay.ore);
  bp.max_ore = MAX(bp.max_ore, bp.obsidian.ore);
  bp.max_ore = MAX(bp.max_ore, bp.geode.ore);
  return bp;
}

typedef struct state {
  Res robots;
  Res res;
} State;

int backtrack(const BP *bp, State *st, int t) {
  Res r = st->res;
  int best = 0, tmp;
  if (t > T) return st->res.geode;
  st->res.ore += st->robots.ore;
  st->res.clay += st->robots.clay;
  st->res.obsidian += st->robots.obsidian;
  st->res.geode += st->robots.geode;
  if (r.ore >= bp->geode.ore && r.obsidian >= bp->geode.obsidian && t < T) {
    st->res.ore -= bp->geode.ore;
    st->res.obsidian -= bp->geode.obsidian;
    st->robots.geode += 1;
    tmp = backtrack(bp, st, t + 1);
    best = MAX(best, tmp);
    st->res.ore += bp->geode.ore;
    st->res.obsidian += bp->geode.obsidian;
    st->robots.geode -= 1;
    st->res = r;
    return best;
  }
  tmp = backtrack(bp, st, t + 1);
  best = MAX(best, tmp);
  if (r.ore >= bp->ore.ore && (T - t) * bp->max_ore > st->res.ore &&
      bp->max_ore > st->robots.ore) {
    st->res.ore -= bp->ore.ore;
    st->robots.ore += 1;
    tmp = backtrack(bp, st, t + 1);
    best = MAX(best, tmp);
    st->res.ore += bp->ore.ore;
    st->robots.ore -= 1;
  }
  if (r.ore >= bp->clay.ore && (T - 2 - t) * bp->obsidian.clay > st->res.clay &&
      bp->obsidian.clay > st->robots.clay) {
    st->res.ore -= bp->clay.ore;
    st->robots.clay += 1;
    tmp = backtrack(bp, st, t + 1);
    best = MAX(best, tmp);
    st->res.ore += bp->clay.ore;
    st->robots.clay -= 1;
  }
  if (r.ore >= bp->obsidian.ore && r.clay >= bp->obsidian.clay &&
      (T - 1 - t) * bp->geode.obsidian > st->res.obsidian &&
      bp->geode.obsidian > st->robots.obsidian) {
    st->res.ore -= bp->obsidian.ore;
    st->res.clay -= bp->obsidian.clay;
    st->robots.obsidian += 1;
    tmp = backtrack(bp, st, t + 1);
    best = MAX(best, tmp);
    st->res.ore += bp->obsidian.ore;
    st->res.clay += bp->obsidian.clay;
    st->robots.obsidian -= 1;
  }

  st->res = r;
  return best;
}

int main(void) {
  int prod = 1, ans;
  int i;
  BP bp;
  FILE *fp = fopen("input.txt", "r");
  State init;
  while (fscanf(fp, "Blueprint %d:", &i) == 1) {
    bp = parse_bp(fp);
    zero_res(&init.robots);
    zero_res(&init.res);
    init.robots.ore = 1;
    ans = backtrack(&bp, &init, 1);
    /* printf("DEBUG: %d %d\n", i, ans); */
    prod *= ans;
    if (i == 3) break;
  }
  fclose(fp);
  printf("%d\n", prod);
  return 0;
}
