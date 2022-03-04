import java.util.Arrays;
//import java.lang.Math;
import java.util.Scanner;

public class Main{
	static int[] ans=new int[10010];
	public static void main(String[] args) {
		Scanner scan= new Scanner(System.in);
		String stra=scan.nextLine();
		String strb=scan.nextLine();
		char[] d=stra.toCharArray();
		char[] e=strb.toCharArray();
		int la=stra.length();
		int lb=strb.length();
		int[] a=new int[la+10];
		int[] b=new int[lb+10];
		for(int i=1;i<=la;i++)a[i]=d[la-i]-'0';
		for(int i=1;i<=lb;i++)b[i]=e[lb-i]-'0';
		int[] c=new int[40010];
		Arrays.fill(c,0);
		for(int i=1;i<=la;i++){
			for(int j=1;j<=lb;j++){
				c[i+j-1]+=a[i]*b[j];
			}
		}
		int lc=la+lb;
		for(int i=1;i<=lc;i++){
			while(c[i]>9){
				c[i+1]++;
				c[i]-=10;
			}
			while(c[lc+1]>0)lc++;
		}
		while((c[lc]==0)&&(lc>1))lc--;
		for(int i=lc;i>=1;i--)System.out.printf("%d",c[i]);
		System.out.println("");
		scan.close();
	}
}