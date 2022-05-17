import java.lang.Math;
import java.util.Arrays;
import java.util.Scanner;

public class Main {

	static int[] p = new int[5010];

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int k = scan.nextInt();
		int n = scan.nextInt();
		Edge[] inp = new Edge[200010];
		for (int i = 0; i <= n; i++) p[i] = i;
		int m = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				int w = scan.nextInt();
				if ((i < j) && (w != 0)) inp[++m] = new Edge(i, j, w);
			}
			inp[++m] = new Edge(0, i, k);
		}
		Edge[] e = new Edge[m];
		for (int i = 1; i <= m; i++) e[i - 1] = new Edge(inp[i].a, inp[i].b, inp[i].w);
		Arrays.sort(e);
		int ans = 0;
		for (int i = 0; i < m; i++) {
			int a = e[i].a, b = e[i].b, w = e[i].w;
			int pa = find(a), pb = find(b);
			if (pa != pb) {
				p[pa] = pb;
				ans += w;
			}
		}
		System.out.printf("%d\n", ans);
		scan.close();
	}

	static class Edge implements Comparable<Edge> {

		int a, b, w;

		public int compareTo(Edge a) {
			return this.w - a.w;
		}

		public Edge(int _a, int _b, int _w) {
			this.a = _a;
			this.b = _b;
			this.w = _w;
		}
	}

	public static int find(int x) {
		if (p[x] != x) p[x] = find(p[x]);
		return p[x];
	}
}
