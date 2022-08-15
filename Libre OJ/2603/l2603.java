import java.util.Arrays;
import java.util.Comparator;
import java.util.Scanner;
import java.math.BigInteger;

class minister
{
	int a, b;
}
class cmp implements Comparator<minister>
{
	public int compare(minister lhs, minister rhs)
	{
		return lhs.a * lhs.b - rhs.a * rhs.b;
	}
}

public class Main
{
	public static void main(String[] args)
	{
		Scanner scan = new Scanner(System.in);
		int n = scan.nextInt();
		int ka = scan.nextInt();
		int nuse = scan.nextInt();
		minister[] d = new minister[n + 1];
		for (int i = 1; i <= n; i++)
		{
			d[i] = new minister();
			d[i].a = scan.nextInt();
			d[i].b = scan.nextInt();
		}
		Arrays.sort(d, 1, n + 1, new cmp());
		BigInteger maxn = BigInteger.ZERO;
		BigInteger cnt = new BigInteger(Integer.toString(ka));
		for (int i = 1; i <= n; i++)
		{
			BigInteger now = cnt.divide(new BigInteger(Integer.toString(d[i].b)));
			if (now.compareTo(maxn) > 0)maxn = now;
			cnt = cnt.multiply(new BigInteger(Integer.toString(d[i].a)));
		}
		System.out.println(maxn);
		scan.close();
	}
}