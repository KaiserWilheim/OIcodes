import java.util.Scanner;

public class Main {

	static int[] p;

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		int m = scan.nextInt();
		p = new int[n + 1];
		for (int i = 1; i <= n; i++) {
			p[i] = i;
		}
		for (int i = 1; i <= m; i++) {
			int op = scan.nextInt();
			int a = scan.nextInt();
			int b = scan.nextInt();
			int pa = find(a);
			int pb = find(b);
			if (op == 1) {
				if (pa != pb) {
					p[pb] = pa;
				}
			} else {
				if (pa == pb) {
					System.out.println("Y");
				} else {
					System.out.println("N");
				}
			}
		}
	}

	public static int find(int x) {
		if (p[x] != x) {
			p[x] = find(p[x]);
		}
		return p[x];
	}
}
