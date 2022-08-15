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
			public long mul;
			public Node()
			{
				l = 0;
				r = 0;
				sum = 0;
				add = 0;
				mul = 1;
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
			if (tr[p].mul != 1 || tr[p].add != 0)
			{
				int ls = p << 1, rs = p << 1 | 1;
				tr[ls].mul = (tr[ls].mul * tr[p].mul) % mod;
				tr[rs].mul = (tr[rs].mul * tr[p].mul) % mod;
				tr[ls].add = (tr[ls].add * tr[p].mul + tr[p].add) % mod;
				tr[rs].add = (tr[rs].add * tr[p].mul + tr[p].add) % mod;
				tr[ls].sum = (tr[ls].sum * tr[p].mul + (tr[ls].r - tr[ls].l + 1) * tr[p].add) % mod;
				tr[rs].sum = (tr[rs].sum * tr[p].mul + (tr[rs].r - tr[rs].l + 1) * tr[p].add) % mod;
				tr[p].mul = 1;
				tr[p].add = 0;
			}
		}

		public void Build(int p, int l, int r, long[] a)
		{
			tr[p].l = l;
			tr[p].r = r;
			tr[p].add = 0;
			tr[p].mul = 1;
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
		public void Segmul(int p, int l, int r, long k)
		{
			if (tr[p].l >= l && tr[p].r <= r)
			{
				tr[p].mul = (tr[p].mul * k) % mod;
				tr[p].add = (tr[p].add * k) % mod;
				tr[p].sum = (tr[p].sum * k) % mod;
				return;
			}
			Pushdown(p);
			int mid = (tr[p].l + tr[p].r) >> 1;
			if (l <= mid) Segmul(p << 1, l, r, k);
			if (r > mid) Segmul(p << 1 | 1, l, r, k);
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

		public SegmentTree(int n, long[] a, long mod)
		{
			tr = new Node[800010];
			for (int i = 0; i <= 800000; i++)
				tr[i] = new Node();
			this.mod = mod;
			Build(1, 1, n, a);
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
			int n, m, mod;
			n = Read();
			m = Read();
			mod = Read();
			long[] a = new long[100010];
			for (int i = 1; i <= n; i++)
				a[i] = Read();
			SegmentTree tr = new SegmentTree(n, a, mod);
			for (int i = 1; i <= m; i++)
			{
				int op, l, r;
				op = Read();
				l = Read();
				r = Read();
				if (op == 1)
				{
					long k = Read();
					tr.Segmul(1, l, r, k);
				}
				else if (op == 2)
				{
					long k = Read();
					tr.Segadd(1, l, r, k);
				}
				else
				{
					Console.WriteLine(tr.Segsum(1, l, r));
				}
			}
		}
	}
}