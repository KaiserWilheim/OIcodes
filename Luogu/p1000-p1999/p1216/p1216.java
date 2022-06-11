//import java.util.Arrays;
//import java.lang.Math;
import java.util.Scanner;

public class Main {

	public static void main(String args[]) {
		Scanner scan = new Scanner(System.in);
		int[][] f = new int[1010][1010];
		int n = 0;
		n = scan.nextInt();
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= i; j++) {
				f[i][j] = scan.nextInt();
			}
		}
		for (int i = n - 1; i >= 1; i--) {
			for (int j = 1; j <= n; j++) {
				if (f[i + 1][j] >= f[i + 1][j + 1]) f[i][j] += f[i + 1][j]; 
				else f[i][j] += f[i + 1][j + 1];
			}
		}
		System.out.println(f[1][1]);
		scan.close();
	}
}
