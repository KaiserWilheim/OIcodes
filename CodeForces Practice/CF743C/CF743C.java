import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		if (n <= 1) {
			System.out.println("-1");
		} else {
			System.out.printf("%d %d %d\n", n, n + 1, n * (n + 1));
		}
	}
}
