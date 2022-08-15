using System;

namespace Main
{
	public class SegmentTree
	{
		public class Node
		{
			public int l;
			public int r;
			public long sum;
			public long add;
			public Node()
			{
				l = 0;
				r = 0;
				sum = 0;
				add = 0;
			}
		}
		public Node[] tr;
		public long mod;

		public void Pushup(int p)
		{
			tr[p].sum = (tr[p << 1].sum + tr[p << 1 | 1].sum) % mod;
		}
		public void Pushdown(int p)
		{
			if (tr[p].add != 0)
			{
				int ls = p << 1, rs = p << 1 | 1;
				tr[ls].add = (tr[ls].add + tr[p].add) % mod;
				tr[rs].add = (tr[rs].add + tr[p].add) % mod;
				tr[ls].sum = (tr[ls].sum + (tr[ls].r - tr[ls].l + 1) * tr[p].add) % mod;
				tr[rs].sum = (tr[rs].sum + (tr[rs].r - tr[rs].l + 1) * tr[p].add) % mod;
				tr[p].add = 0;
			}
		}

		public void Build(int p, int l, int r, int[] a)
		{
			tr[p].l = l;
			tr[p].r = r;
			tr[p].add = 0;
			if (l == r)
			{
				tr[p].sum = a[l];
				return;
			}
			int mid = (l + r) >> 1;
			Build(p << 1, l, mid, a);
			Build(p << 1 | 1, mid + 1, r, a);
			Pushup(p);
		}

		public void Segadd(int p, int l, int r, long k)
		{
			if (tr[p].l >= l && tr[p].r <= r)
			{
				tr[p].add = (tr[p].add + k) % mod;
				tr[p].sum = (tr[p].sum + (tr[p].r - tr[p].l + 1) * k) % mod;
				return;
			}
			Pushdown(p);
			int mid = (tr[p].l + tr[p].r) >> 1;
			if (l <= mid) Segadd(p << 1, l, r, k);
			if (r > mid) Segadd(p << 1 | 1, l, r, k);
			Pushup(p);
		}
		public long Segsum(int p, int l, int r)
		{
			if (tr[p].l >= l && tr[p].r <= r)
			{
				return tr[p].sum;
			}
			Pushdown(p);
			long res = 0;
			int mid = (tr[p].l + tr[p].r) >> 1;
			if (l <= mid) res = (res + Segsum(p << 1, l, r)) % mod;
			if (r > mid) res = (res + Segsum(p << 1 | 1, l, r)) % mod;
			return res;
		}

		public SegmentTree(int n, int[] a, long mod)
		{
			tr = new Node[800010];
			for (int i = 0; i <= 800000; i++)
				tr[i] = new Node();
			this.mod = mod;
			Build(1, 1, n, a);
		}
	}

	class HeavyPathDec
	{
		const int N = 100010, M = 200010;
		public int[] h = new int[N];
		public int[] e = new int[M];
		public int[] ne = new int[M];
		public int idx = 0;

		public int[] fa = new int[N];
		public int[] son = new int[N];
		public int[] sz = new int[N];
		public int[] dep = new int[N];

		public int[] top = new int[N];
		public int[] id = new int[N];
		public int[] nw = new int[N];
		public int tot = 0;

		public SegmentTree tr;
		public long mod;

		public void Add(int a, int b)
		{
			e[idx] = b;
			ne[idx] = h[a];
			h[a] = idx++;
		}

		public void Dfs1(int p, int father, int depth)
		{
			fa[p] = father;
			dep[p] = depth;
			sz[p] = 1;
			for (int i = h[p]; i != -1; i = ne[i])
			{
				int j = e[i];
				if (e[i] == fa[p]) continue;
				Dfs1(j, p, depth + 1);
				sz[p] += sz[j];
				if (sz[j] > sz[son[p]]) son[p] = j;
			}
		}
		public void Dfs2(int p, int t, int[] w)
		{
			top[p] = t;
			id[p] = ++tot;
			nw[tot] = w[p];
			if (son[p] == 0) return;
			Dfs2(son[p], t, w);
			for (int i = h[p]; i != -1; i = ne[i])
			{
				int j = e[i];
				if (j == fa[p] || j == son[p]) continue;
				Dfs2(j, j, w);
			}
		}

		public void Addpath(int p, int q, int k)
		{
			while (top[p] != top[q])
			{
				if (dep[top[p]] < dep[top[q]]) Swap(ref p, ref q);
				tr.Segadd(1, id[top[p]], id[p], k);
				p = fa[top[p]];
			}
			if (dep[p] < dep[q]) Swap(ref p, ref q);
			tr.Segadd(1, id[q], id[p], k);
		}
		public long Sumpath(int p, int q)
		{
			long res = 0;
			while (top[p] != top[q])
			{
				if (dep[top[p]] < dep[top[q]]) Swap(ref p, ref q);
				res = (res + tr.Segsum(1, id[top[p]], id[p])) % mod;
				p = fa[top[p]];
			}
			if (dep[p] < dep[q]) Swap(ref p, ref q);
			res = (res + tr.Segsum(1, id[q], id[p])) % mod;
			return res;
		}
		public void Addtree(int p, int k)
		{
			tr.Segadd(1, id[p], id[p] + sz[p] - 1, k);
		}
		public long Sumtree(int p)
		{
			return tr.Segsum(1, id[p], id[p] + sz[p] - 1);
		}

		public HeavyPathDec(int rt, int n, long mod)
		{
			Array.Fill(h, -1);
			int[] w = new int[100010];
			for (int i = 1; i <= n; i++)
				w[i] = Read();
			for(int i = 1; i < n; i++)
			{
				int a, b;
				a = Read();
				b = Read();
				Add(a, b);
				Add(b, a);
			}
			this.mod = mod;
			Dfs1(rt, 0, 1);
			Dfs2(rt, rt, w);
			tr = new SegmentTree(n, nw, mod);
		}

		private void Swap(ref int a, ref int b)
		{
			int temp = a;
			a = b;
			b = temp;
		}
		static public int Read()
		{
			int x = 0;
			int c = Console.Read();
			while (c < '0' || c > '9') c = Console.Read();
			while (c >= '0' && c <= '9')
			{
				x = (x * 10) + (c - 48);
				c = Console.Read();
			}
			return x;
		}
	}

	class MainClass
	{
		static public int Read()
		{
			int x = 0;
			int c = Console.Read();
			while (c < '0' || c > '9') c = Console.Read();
			while (c >= '0' && c <= '9')
			{
				x = (x * 10) + (c - 48);
				c = Console.Read();
			}
			return x;
		}
		public static void Main(string[] args)
		{
			int n, m, rt, mod;
			n = Read();
			m = Read();
			rt = Read();
			mod = Read();
			HeavyPathDec tr = new HeavyPathDec(rt, n, mod);
			for (int i = 1; i <= m; i++)
			{
				int op;
				op = Read();
				if (op == 1)
				{
					int x, y, k;
					x = Read();
					y = Read();
					k = Read();
					tr.Addpath(x, y, k);
				}
				else if (op == 2)
				{
					int x, y;
					x = Read();
					y = Read();
					Console.WriteLine(tr.Sumpath(x, y));
				}
				else if (op == 3)
				{
					int x, k;
					x = Read();
					k = Read();
					tr.Addtree(x, k);
				}
				else if (op == 4)
				{
					int x;
					x = Read();
					Console.WriteLine(tr.Sumtree(x));
				}
			}
		}
	}
}