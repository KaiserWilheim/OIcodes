//import java.util.Arrays;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		int k = scan.nextInt();
		System.out.printf("%d\n", (6 * n - 1) * k);
		for (int i = 1; i <= n; i++) {
			int t = 6 * (i - 1);
			System.out.printf("%d %d %d %d\n", k * (t + 1), k * (t + 2), k * (t + 3), k * (t + 5));
		}
	}
}
