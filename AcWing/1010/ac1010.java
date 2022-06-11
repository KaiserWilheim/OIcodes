//import java.util.Arrays;
//import java.lang.Math;
import java.util.Scanner;

public class Main {

	public static void main(String args[]) {
		Scanner scan = new Scanner(System.in);
		int[] f = new int[10010];
		int[] q = new int[10010];
		int[] a = new int[10010];
		int n = 0;
		int maxn = 0;
		while (scan.hasNextInt()) a[++n] = scan.nextInt();
		for (int i = n; i >= 1; i--) {
			if (maxn == 0 || a[i] >= f[maxn]) {
				maxn++;
				f[maxn] = a[i];
				continue;
			}
			int k = upper_bound(f, 1, maxn, a[i]);
			f[k] = a[i];
		}
		System.out.println(maxn);
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			if (cnt == 0) {
				cnt++;
				q[cnt] = a[i];
				continue;
			}
			int k = lower_bound(q, 1, cnt, a[i]);
			if (q[k] < a[i]) q[++cnt] = a[i]; else q[k] = a[i];
		}
		System.out.println(cnt);
		scan.close();
	}

	public static int lower_bound(int[] arr, int begin, int end, int tar) {
		while (begin < end) {
			int mid = begin + (end - begin) / 2;
			if (arr[mid] < tar) begin = mid + 1; 
			else if (arr[mid] >= tar) end = mid;
		}
		return begin;
	}

	public static int upper_bound(int[] arr, int begin, int end, int tar) {
		while (begin < end) {
			int mid = begin + (end - begin) / 2;
			if (arr[mid] <= tar) begin = mid + 1; 
			else if (arr[mid] > tar) end = mid;
		}
		return begin;
	}
}
