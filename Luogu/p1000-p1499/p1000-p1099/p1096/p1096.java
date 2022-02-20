//import java.util.Arrays;
import java.util.Scanner;

public class Main{
	static int[] num=new int[210];
	public static void main(String[] args) {
		Scanner scan= new Scanner(System.in);
		int n=scan.nextInt();
		num[0]=1;
		num[1]=1;
		for(int i=0;i<=n;i++)mul(2);
		num[1]-=2;
		for(int i=1;i<=num[0];i++){
			if(num[i]<0){
				num[i]+=10;
				num[i+1]--;
			}
			if(num[num[0]]==0)num[0]--;
		}
		for(int i=num[0];i>=1;i--)System.out.printf("%d",num[i]);
		System.out.print("\n");
		scan.close();
	}

	private static void mul(int k){
		for(int i=1;i<=num[0];i++)num[i]*=k;
		for(int i=1;i<=num[0];i++){
			if(num[i]>9){
				num[i+1]++;
				num[i]-=10;
			}
			if(num[num[0]+1]>0)num[0]++;
		}
	}
}