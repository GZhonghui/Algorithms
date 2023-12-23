#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
#define int long long
const int maxn = 100010;
const int mod = 51061;
int n, q, u, v, c;
char op;
struct Splay {
    int ch[maxn][2],fa[maxn],siz[maxn],val[maxn],sum[maxn],
    rev[maxn],add[maxn],mul[maxn];
  void clear(int x) {
    ch[x][0] = ch[x][1] = fa[x] = siz[x]=val[x]=sum[x]=rev[x]=add[x]=0;
    mul[x] = 1;
  }
  int getch(int x) { return (ch[fa[x]][1] == x); }
  int isroot(int x) {
    clear(0);
    return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
  }
  void maintain(int x) {
    clear(0);
    siz[x] = (siz[ch[x][0]] + 1 + siz[ch[x][1]]) % mod;
    sum[x] = (sum[ch[x][0]] + val[x] + sum[ch[x][1]]) % mod;
  }
  void pushdown(int x) {
    clear(0);
    if (mul[x] != 1) {
      if (ch[x][0])
        mul[ch[x][0]] = (mul[x] * mul[ch[x][0]]) % mod,
        val[ch[x][0]] = (val[ch[x][0]] * mul[x]) % mod,
        sum[ch[x][0]] = (sum[ch[x][0]] * mul[x]) % mod,
        add[ch[x][0]] = (add[ch[x][0]] * mul[x]) % mod;
      if (ch[x][1])
        mul[ch[x][1]] = (mul[x] * mul[ch[x][1]]) % mod,
        val[ch[x][1]] = (val[ch[x][1]] * mul[x]) % mod,
        sum[ch[x][1]] = (sum[ch[x][1]] * mul[x]) % mod,
        add[ch[x][1]] = (add[ch[x][1]] * mul[x]) % mod;
      mul[x] = 1;
    }
    if (add[x]) {
      if (ch[x][0])
        add[ch[x][0]] = (add[ch[x][0]] + add[x]) % mod,
        val[ch[x][0]] = (val[ch[x][0]] + add[x]) % mod,
        sum[ch[x][0]] = (sum[ch[x][0]] + add[x] * siz[ch[x][0]] % mod) % mod;
      if (ch[x][1])
        add[ch[x][1]] = (add[ch[x][1]] + add[x]) % mod,
        val[ch[x][1]] = (val[ch[x][1]] + add[x]) % mod,
        sum[ch[x][1]] = (sum[ch[x][1]] + add[x] * siz[ch[x][1]] % mod) % mod;
      add[x] = 0;
    }
    if (rev[x]) {
      if (ch[x][0]) rev[ch[x][0]] ^= 1, swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
      if (ch[x][1]) rev[ch[x][1]] ^= 1, swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
      rev[x] = 0;
    }
  }
  void update(int x) {
    if (!isroot(x)) update(fa[x]);
    pushdown(x);
  }
  void print(int x) {
    if (!x) return;
    pushdown(x);
    print(ch[x][0]);
    printf("%lld ", x);
    print(ch[x][1]);
  }
  void rotate(int x) {
    int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
    fa[x] = z;
    if (!isroot(y)) ch[z][chy] = x;
    ch[y][chx] = ch[x][chx ^ 1];
    fa[ch[x][chx ^ 1]] = y;
    ch[x][chx ^ 1] = y;
    fa[y] = x;
    maintain(y);
    maintain(x);
    maintain(z);
  }
  void splay(int x) {
    update(x);
    for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
      if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
  }
  void access(int x) {
    for (int f = 0; x; f = x, x = fa[x]) splay(x), ch[x][1] = f, maintain(x);
  }
  void makeroot(int x) {
    access(x);
    splay(x);
    swap(ch[x][0], ch[x][1]);
    rev[x] ^= 1;
  }
  int find(int x) {
    access(x);
    splay(x);
    while (ch[x][0]) x = ch[x][0];
    splay(x);
    return x;
  }
} st;
int main() {
  scanf("%lld%lld", &n, &q);
  for (int i = 1; i <= n; i++) st.val[i] = 1, st.maintain(i);
  for (int i = 1; i < n; i++) {
    scanf("%lld%lld", &u, &v);
    if (st.find(u) != st.find(v)) st.makeroot(u), st.fa[u] = v;
  }
  while (q--) {
    scanf(" %c%lld%lld", &op, &u, &v);
    if (op == '+') {
      scanf("%lld", &c);
      st.makeroot(u), st.access(v), st.splay(v);
      st.val[v] = (st.val[v] + c) % mod;
      st.sum[v] = (st.sum[v] + st.siz[v] * c % mod) % mod;
      st.add[v] = (st.add[v] + c) % mod;
    }
    if (op == '-') {
      st.makeroot(u);
      st.access(v);
      st.splay(v);
      if (st.ch[v][0] == u && !st.ch[u][1]) st.ch[v][0] = st.fa[u] = 0;
      scanf("%lld%lld", &u, &v);
      if (st.find(u) != st.find(v)) st.makeroot(u), st.fa[u] = v;
    }
    if (op == '*') {
      scanf("%lld", &c);
      st.makeroot(u), st.access(v), st.splay(v);
      st.val[v] = st.val[v] * c % mod;
      st.sum[v] = st.sum[v] * c % mod;
      st.mul[v] = st.mul[v] * c % mod;
    }
    if (op == '/')
      st.makeroot(u), st.access(v), st.splay(v), printf("%lld\n", st.sum[v]);
  }
  return 0;
}