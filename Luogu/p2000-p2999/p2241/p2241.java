//import java.util.Arrays;
//import java.lang.Math;
import java.util.Scanner;

public class Main{
	static int[] ans=new int[10010];
	public static void main(String[] args) {
		Scanner scan= new Scanner(System.in);
		int m=scan.nextInt();
		int n=scan.nextInt();
		if(m<n){
			int tmp=n;
			n=m;
			m=tmp;
		}
		long s=0;
		for(int i=1;i<=n;i++)s+=(n-i+1)*(m-i+1);
		long r=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				r+=(n-i+1)*(m-j+1);
			}
		}
		r-=s;
		System.out.printf("%d %d\n",s,r);
		scan.close();
	}
}