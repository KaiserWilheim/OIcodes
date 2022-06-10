//import java.util.Arrays;
//import java.lang.Math;
import java.util.Scanner;

public class Main {

	public static void main(String args[]) {
		Scanner scan = new Scanner(System.in);
		int[] f = new int[10010];
		int[] g = new int[10010];
		int[] a = new int[10010];
		int n = scan.nextInt();
		int maxn = 0;
		for (int i = 1; i <= n; i++) {
			a[i] = scan.nextInt();
			f[i] = g[i] = 1;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j < i; j++) {
				if (a[i] > a[j]) f[i] = max(f[i], f[j] + 1);
			}
		}
		for (int i = n; i >= 1; i--) {
			for (int j = n; j > i; j--) {
				if (a[i] > a[j]) g[i] = max(g[i], g[j] + 1);
			}
		}
		for (int i = 1; i <= n; i++) {
			maxn = max(maxn, f[i] + g[i] - 1);
		}
		System.out.println(n - maxn);
		scan.close();
	}

	private static int max(int a, int b) {
		return a >= b ? a : b;
	}
}
