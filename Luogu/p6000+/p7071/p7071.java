//import java.util.Arrays;
//import java.lang.Math;
import java.util.Scanner;

public class Main {

	static int[] ans = new int[10010];

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		if (n % 2 == 1) {
			System.out.println("-1");
		} else {
			int[] ans = new int[30];
			int tot = 0, x = 1;
			while (n != 0) {
				if (n % 2 == 1) ans[++tot] = x;
				x <<= 1;
				n >>= 1;
			}
			for (int i = tot; i >= 1; i--) System.out.printf("%d ", ans[i]);
			System.out.println("");
		}
		scan.close();
	}
}
