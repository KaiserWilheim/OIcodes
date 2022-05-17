//import java.util.Arrays;
import java.lang.Math;
import java.util.Scanner;

public class Main {

	static int[] ans = new int[10010];

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		String stra = scan.nextLine();
		String strb = scan.nextLine();
		int la = stra.length(), lb = strb.length();
		char[] a = stra.toCharArray();
		char[] b = strb.toCharArray();
		for (int i = 1; i <= la; i++) ans[i] += a[la - i] - '0';
		for (int i = 1; i <= lb; i++) ans[i] += b[lb - i] - '0';
		ans[0] = Math.max(la, lb);
		for (int i = 1; i <= ans[0]; i++) {
			if (ans[i] > 9) {
				ans[i + 1]++;
				ans[i] -= 10;
				if (ans[ans[0] + 1] > 0) ans[0]++;
			}
		}
		for (int i = ans[0]; i >= 1; i--) System.out.printf("%d", ans[i]);
		System.out.println("");
		scan.close();
	}
}
