//import java.util.Arrays;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		int[] ans = new int[15];
		int maxn = 0;
		ans[0] = 0;
		while (n > 0) {
			ans[++ans[0]] = n % 10;
			maxn = max(maxn, ans[ans[0]]);
			n /= 10;
		}
		System.out.printf("%d\n", maxn);
		for (int i = 1; i <= maxn; i++) {
			boolean flag = false;
			for (int j = ans[0]; j >= 1; j--) {
				if (ans[j] > 0) {
					ans[j]--;
					System.out.printf("%d", 1);
					flag = true;
				} else {
					if (flag) System.out.printf("%d", 0);
				}
			}
			System.out.print(" ");
		}
		System.out.println("");
	}

	private static int max(int a, int b) {
		if (a >= b) return a; else return b;
	}
}
