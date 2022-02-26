import java.util.Arrays;
import java.lang.Math;
import java.util.Scanner;

public class Main{
	static int[] p=new int[10010];
	public static void main(String[] args) {
		Scanner scan= new Scanner(System.in);
		int n=scan.nextInt();
		int m=scan.nextInt();
		int[] num=new int[n+1];
		Edge[] e=new Edge[m];
		int minn=0x3f3f3f3f;
		for(int i=1;i<=n;i++)p[i]=i;
		for(int i=1;i<=n;i++){
			num[i]=scan.nextInt();
			minn=Math.min(minn,num[i]);
		}
		for(int i=0;i<m;i++){
			int a=scan.nextInt();
			int b=scan.nextInt();
			int w=scan.nextInt();
			e[i]=new Edge(a,b,w*2+num[a]+num[b]);
		}
		Arrays.sort(e);
		int ans=0;
		for(int i=0;i<m;i++){
			int a=e[i].a,b=e[i].b,w=e[i].w;
			int pa=find(a),pb=find(b);
			if(pa!=pb){
				p[pa]=pb;
				ans+=w;
			}
		}
		System.out.printf("%d\n",ans+minn);
		scan.close();
	}

	static class Edge implements Comparable<Edge>{
		int a,b,w;
		public int compareTo(Edge a){
			return this.w-a.w;
		}
		public Edge(int _a,int _b,int _w){
			this.a=_a;
			this.b=_b;
			this.w=_w;
		}
	}

	public static int find(int x){
		if(p[x]!=x)p[x]=find(p[x]);
		return p[x];
	}
}