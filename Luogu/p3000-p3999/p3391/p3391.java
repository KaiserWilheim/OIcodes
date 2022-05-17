//import java.util.Arrays;
//import java.lang.Math;
import java.util.Scanner;

public class Main {

  static int[][] s = new int[100010][2];
  static int[] f = new int[100010];
  static int[] v = new int[100010];
  static int[] sz = new int[100010];
  static int[] flag = new int[100010];
  static int rt = 0, idx = 0;
  static int n = 0;

  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    n = scan.nextInt();
    int m = scan.nextInt();
    for (int i = 0; i <= n + 1; i++) insert(i);
    for (int i = 1; i <= m; i++) {
      int l, r;
      l = scan.nextInt();
      r = scan.nextInt();
      int L = get_k(l);
      int R = get_k(r + 2);
      splay(L, 0);
      splay(R, L);
      flag[s[R][0]] ^= 1;
    }
    output(rt);
    scan.close();
  }

  static void pushup(int p) {
    sz[p] = sz[s[p][0]] + sz[s[p][1]] + 1;
  }

  static void pushdown(int p) {
    if (flag[p] != 0) {
      int temp = s[p][1];
      s[p][1] = s[p][0];
      s[p][0] = temp;
      flag[s[p][1]] ^= 1;
      flag[s[p][0]] ^= 1;
      flag[p] = 0;
    }
  }

  static void rotate(int x) {
    int y = f[x], z = f[y];
    if (y == 0) return;
    int k = (s[y][1] == x) ? 1 : 0;
    //z-x
    s[z][s[z][1] == y ? 1 : 0] = x;
    f[x] = z;
    //y-B
    s[y][k] = s[x][k ^ 1];
    f[s[x][k ^ 1]] = y;
    //x-y
    s[x][k ^ 1] = y;
    f[y] = x;
    pushup(y);
    pushup(x);
  }

  static void splay(int x, int k) {
    while (f[x] != k) {
      int y = f[x], z = f[y];
      if (z != k) {
        if (((s[y][1] == x ? 1 : 0) ^ (s[z][1] == y ? 1 : 0)) != 0) rotate(
          x
        ); else rotate(y);
      }
      rotate(x);
    }
    if (k == 0) rt = x;
  }

  static void insert(int k) {
    int u = rt, p = 0;
    while (u != 0) {
      p = u;
      u = s[u][k > v[u] ? 1 : 0];
    }
    u = ++idx;
    if (p != 0) s[p][k > v[p] ? 1 : 0] = u;
    v[u] = k;
    f[u] = p;
    splay(u, 0);
  }

  static int get_k(int k) {
    int u = rt;
    while (true) {
      pushdown(u);
      if (sz[s[u][0]] >= k) {
        u = s[u][0];
      } else if (sz[s[u][0]] + 1 == k) {
        return u;
      } else {
        k -= sz[s[u][0]] + 1;
        u = s[u][1];
      }
    }
  }

  static void output(int u) {
    pushdown(u);
    if (s[u][0] != 0) output(s[u][0]);
    if (v[u] >= 1 && v[u] <= n) System.out.printf("%d ", v[u]);
    if (s[u][1] != 0) output(s[u][1]);
  }
}
