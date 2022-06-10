//import java.util.Arrays;
//import java.lang.Math;
import java.util.Scanner;

public class Main {

	private static Scanner scan = new Scanner(System.in);

	public static void main(String args[]) {
		int T = scan.nextInt();
		while (T > 0) {
			solve();
			T--;
		}
		scan.close();
	}

	private static void solve() {
		int[] f = new int[10010];
		int[] g = new int[10010];
		int[] a = new int[10010];
		int n = scan.nextInt();
		int maxn = 0;
		for (int i = 1; i <= n; i++) {
			a[i] = scan.nextInt();
			f[i] = g[i] = 1;
			for (int j = 1; j < i; j++) {
				if (a[i] < a[j]) f[i] = max(f[i], f[j] + 1);
				if (a[i] > a[j]) g[i] = max(g[i], g[j] + 1);
			}
			maxn = max(maxn, max(f[i], g[i]));
		}
		System.out.println(maxn);
	}

	private static int max(int a, int b) {
		return a >= b ? a : b;
	}
}
