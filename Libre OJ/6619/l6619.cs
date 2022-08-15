using System;

namespace Main
{
	class Map
	{
		public int[,] m = new int[20, 20];
		public int side;
		public bool isCaptured;
		public bool isInvalid;
		public bool isCheckmate;
		public int knockOut;
		public int sx, sy, tx, ty;

		public Map()
		{
			Array.Clear(m, 0, m.Length);
			side = 0;
			isCaptured = false;
			isInvalid = false;
			isCheckmate = false;
			knockOut = 0;
			sx = 0; sy = 0; tx = 0; ty = 0;
		}
		public void Init()
		{
			m[4, 0] = 1;
			m[4, 9] = 11;
			m[3, 0] = m[5, 0] = 2;
			m[3, 9] = m[5, 9] = 12;
			m[2, 0] = m[6, 0] = 3;
			m[2, 9] = m[6, 9] = 13;
			m[1, 0] = m[7, 0] = 4;
			m[1, 9] = m[7, 9] = 14;
			m[0, 0] = m[8, 0] = 5;
			m[0, 9] = m[8, 9] = 15;
			m[0, 2] = m[8, 2] = 6;
			m[0, 7] = m[8, 7] = 16;
			m[0, 3] = m[2, 3] = m[4, 3] = m[6, 3] = m[8, 3] = 7;
			m[0, 6] = m[2, 6] = m[4, 6] = m[6, 6] = m[8, 6] = 17;
		}
		public void Clear()
		{
			isInvalid = false;
			isCheckmate = false;
			knockOut = 0;
		}

		public void CheckOut()
		{
			bool flag = false;
			if (sx < 0 || sx > 8) flag = true;
			if (sy < 0 || sy > 9) flag = true;
			if (tx < 0 || tx > 8) flag = true;
			if (ty < 0 || ty > 9) flag = true;
			if (flag)
			{
				Console.WriteLine("Invalid command");
				isInvalid = true;
			}
		}

		public void Move()
		{
			if (m[sx, sy] / 10 != side)
			{
				Console.WriteLine("Invalid command");
				isInvalid = true;
				return;
			}
			else if (m[sx, sy] == 0)
			{
				Console.WriteLine("Invalid command");
				isInvalid = true;
				return;
			}
			else if (m[tx, ty] / 10 == side && m[tx, ty] != 0)
			{
				Console.WriteLine("Invalid command");
				isInvalid = true;
				return;
			}

			int type = m[sx, sy] % 10;
			if (type == 1)
			{
				if (Math.Abs(sx - tx) + Math.Abs(sy - ty) > 1)
				{
					Console.WriteLine("Invalid command");
					isInvalid = true;
					return;
				}
			}
			else if (type == 2)
			{
				if (Math.Abs(sx - tx) != 1 || Math.Abs(sy - ty) != 1)
				{
					Console.WriteLine("Invalid command");
					isInvalid = true;
					return;
				}
			}
			else if (type == 3)
			{
				if (Math.Abs(sx - tx) != 2 || Math.Abs(sy - ty) != 2)
				{
					Console.WriteLine("Invalid command");
					isInvalid = true;
					return;
				}
				if (m[(sx + tx) / 2, (sy + ty) / 2] != 0)
				{
					Console.WriteLine("Invalid command");
					isInvalid = true;
					return;
				}
			}
			else if (type == 4)
			{
				if (!(Math.Abs(sx - tx) == 2 && Math.Abs(sy - ty) == 1) && !(Math.Abs(sx - tx) == 1 && Math.Abs(sy - ty) == 2))
				{
					Console.WriteLine("Invalid command");
					isInvalid = true;
					return;
				}
				if (Math.Abs(sx - tx) > Math.Abs(sy - ty))
				{
					if (m[sx + (tx - sx) / 2, sy] != 0)
					{
						Console.WriteLine("Invalid command");
						isInvalid = true;
						return;
					}
				}
				else
				{
					if (m[sx, sy + (ty - sy) / 2] != 0)
					{
						Console.WriteLine("Invalid command");
						isInvalid = true;
						return;
					}
				}
			}
			else if (type == 5)
			{
				if (sx != tx && sy != ty)
				{
					Console.WriteLine("Invalid command");
					isInvalid = true;
					return;
				}
				bool RookCollide = false;
				if (sx != tx)
				{
					for (int i = Math.Min(sx, tx) + 1; i < Math.Max(sx, tx); i++)
					{
						if (m[i, sy] != 0)
						{
							RookCollide = true;
							break;
						}
					}
				}
				else
				{
					for (int i = Math.Min(sy, ty) + 1; i < Math.Max(sy, ty); i++)
					{
						if (m[sx, i] != 0)
						{
							RookCollide = true;
							break;
						}
					}
				}
				if (RookCollide)
				{
					Console.WriteLine("Invalid command");
					isInvalid = true;
					return;
				}
			}
			else if (type == 6)
			{
				if (!(Math.Abs(sx - tx) == 3 && Math.Abs(sy - ty) == 2) && !(Math.Abs(sx - tx) == 2 && Math.Abs(sy - ty) == 3))
				{
					Console.WriteLine("Invalid command");
					isInvalid = true;
					return;
				}
				int kx = (tx - sx > 0) ? 1 : -1;
				int ky = (ty - sy > 0) ? 1 : -1;
				if (Math.Abs(sx - tx) > Math.Abs(sy - ty))
				{
					if (m[sx + kx, sy] != 0 || m[sx + 2 * kx, sy + ky] != 0)
					{
						Console.WriteLine("Invalid command");
						isInvalid = true;
						return;
					}
				}
				else
				{
					if (m[sx, sy + ky] != 0 || m[sx + kx, sy + 2 * ky] != 0)
					{
						Console.WriteLine("Invalid command");
						isInvalid = true;
						return;
					}
				}
			}
			else if (type == 7)
			{

				if (Math.Abs(sx - tx) > 1 || Math.Abs(sy - ty) > 1)
				{
					Console.WriteLine("Invalid command");
					isInvalid = true;
					return;
				}
			}

			knockOut = m[tx, ty];
			m[tx, ty] = m[sx, sy];
			m[sx, sy] = 0;
		}

		public bool CheckMate(int k)
		{
			int x = 0, y = 0;
			for (int i = 0; i <= 8; i++)
			{
				for (int j = 0; j <= 9; j++)
				{
					if (m[i, j] == (k ^ 1) * 10 + 1)
					{
						x = i; y = j;
						break;
					}
				}
			}

			bool flag = false;

			for (int i = x + 1; i <= 8; i++)
			{
				if (m[i, y] == k * 10 + 5)
				{
					flag = true;
					break;
				}
				else if (m[i, y] != 0) break;
			}
			for (int i = x - 1; i >= 0; i--)
			{
				if (m[i, y] == k * 10 + 5)
				{
					flag = true;
					break;
				}
				else if (m[i, y] != 0) break;
			}
			for (int i = y + 1; i <= 9; i++)
			{
				if (m[x, i] == k * 10 + 5)
				{
					flag = true;
					break;
				}
				else if (m[x, i] != 0) break;
			}
			for (int i = y - 1; i >= 0; i--)
			{
				if (m[x, i] == k * 10 + 5)
				{
					flag = true;
					break;
				}
				else if (m[x, i] != 0) break;
			}
			if (flag) return flag;
			if (x <= 7 && m[x + 1, y] == k * 10 + 1) flag = true;
			if (y <= 8 && m[x, y + 1] == k * 10 + 1) flag = true;
			if (x >= 1 && m[x - 1, y] == k * 10 + 1) flag = true;
			if (y >= 1 && m[x, y - 1] == k * 10 + 1) flag = true;
			if (flag) return flag;
			if (x <= 7 && y <= 8 && m[x + 1, y + 1] == k * 10 + 2) flag = true;
			if (x >= 1 && y <= 8 && m[x - 1, y + 1] == k * 10 + 2) flag = true;
			if (x <= 7 && y >= 1 && m[x + 1, y - 1] == k * 10 + 2) flag = true;
			if (x >= 1 && y >= 1 && m[x - 1, y - 1] == k * 10 + 2) flag = true;
			if (flag) return flag;
			if (x <= 7 && m[x + 1, y] == k * 10 + 7) flag = true;
			if (y <= 8 && m[x, y + 1] == k * 10 + 7) flag = true;
			if (x >= 1 && m[x - 1, y] == k * 10 + 7) flag = true;
			if (y >= 1 && m[x, y - 1] == k * 10 + 7) flag = true;
			if (x <= 7 && y <= 8 && m[x + 1, y + 1] == k * 10 + 7) flag = true;
			if (x >= 1 && y <= 8 && m[x - 1, y + 1] == k * 10 + 7) flag = true;
			if (x <= 7 && y >= 1 && m[x + 1, y - 1] == k * 10 + 7) flag = true;
			if (x >= 1 && y >= 1 && m[x - 1, y - 1] == k * 10 + 7) flag = true;
			if (flag) return flag;
			if (x <= 6 && y <= 8 && m[x + 2, y + 1] == k * 10 + 4 && m[x + 1, y + 1] == 0) flag = true;
			if (x >= 2 && y <= 8 && m[x - 2, y + 1] == k * 10 + 4 && m[x - 1, y + 1] == 0) flag = true;
			if (x <= 6 && y >= 1 && m[x + 2, y - 1] == k * 10 + 4 && m[x + 1, y - 1] == 0) flag = true;
			if (x >= 2 && y >= 1 && m[x - 2, y - 1] == k * 10 + 4 && m[x - 1, y - 1] == 0) flag = true;
			if (x <= 7 && y <= 7 && m[x + 1, y + 2] == k * 10 + 4 && m[x + 1, y + 1] == 0) flag = true;
			if (x >= 1 && y <= 7 && m[x - 1, y + 2] == k * 10 + 4 && m[x - 1, y + 1] == 0) flag = true;
			if (x <= 7 && y >= 2 && m[x + 1, y - 2] == k * 10 + 4 && m[x + 1, y - 1] == 0) flag = true;
			if (x >= 1 && y >= 2 && m[x - 1, y - 2] == k * 10 + 4 && m[x - 1, y - 1] == 0) flag = true;
			if (flag) return flag;
			if (x <= 6 && y <= 7 && m[x + 2, y + 2] == k * 10 + 3 && m[x + 1, y + 1] == 0) flag = true;
			if (x >= 2 && y <= 7 && m[x - 2, y + 2] == k * 10 + 3 && m[x - 1, y + 1] == 0) flag = true;
			if (x <= 6 && y >= 2 && m[x + 2, y - 2] == k * 10 + 3 && m[x + 1, y - 1] == 0) flag = true;
			if (x >= 2 && y >= 2 && m[x - 2, y - 2] == k * 10 + 3 && m[x - 1, y - 1] == 0) flag = true;
			if (flag) return flag;
			if (x <= 5 && y <= 7 && m[x + 3, y + 2] == k * 10 + 6 && m[x + 2, y + 2] == 0 && m[x + 1, y + 1] == 0) flag = true;
			if (x >= 3 && y <= 7 && m[x - 3, y + 2] == k * 10 + 6 && m[x - 2, y + 2] == 0 && m[x - 1, y + 1] == 0) flag = true;
			if (x <= 5 && y >= 2 && m[x + 3, y - 2] == k * 10 + 6 && m[x + 2, y - 2] == 0 && m[x + 1, y - 1] == 0) flag = true;
			if (x >= 3 && y >= 2 && m[x - 3, y - 2] == k * 10 + 6 && m[x - 2, y - 2] == 0 && m[x - 1, y - 1] == 0) flag = true;
			if (x <= 6 && y <= 6 && m[x + 2, y + 3] == k * 10 + 6 && m[x + 2, y + 2] == 0 && m[x + 1, y + 1] == 0) flag = true;
			if (x >= 2 && y <= 6 && m[x - 2, y + 3] == k * 10 + 6 && m[x - 2, y + 2] == 0 && m[x - 1, y + 1] == 0) flag = true;
			if (x <= 6 && y >= 3 && m[x + 2, y - 3] == k * 10 + 6 && m[x + 2, y - 2] == 0 && m[x + 1, y - 1] == 0) flag = true;
			if (x >= 2 && y >= 3 && m[x - 2, y - 3] == k * 10 + 6 && m[x - 2, y - 2] == 0 && m[x - 1, y - 1] == 0) flag = true;
			return flag;
		}

		public void Write()
		{
			switch (m[tx, ty])
			{
				case 1: { Console.Write("red captain;"); break; }
				case 2: { Console.Write("red guard;"); break; }
				case 3: { Console.Write("red elephant;"); break; }
				case 4: { Console.Write("red horse;"); break; }
				case 5: { Console.Write("red car;"); break; }
				case 6: { Console.Write("red duck;"); break; }
				case 7: { Console.Write("red soldier;"); break; }
				case 11: { Console.Write("blue captain;"); break; }
				case 12: { Console.Write("blue guard;"); break; }
				case 13: { Console.Write("blue elephant;"); break; }
				case 14: { Console.Write("blue horse;"); break; }
				case 15: { Console.Write("blue car;"); break; }
				case 16: { Console.Write("blue duck;"); break; }
				case 17: { Console.Write("blue soldier;"); break; }
			}
			switch (knockOut)
			{
				case 0: { Console.Write("NA;"); break; }
				case 1: { Console.Write("red captain;"); break; }
				case 2: { Console.Write("red guard;"); break; }
				case 3: { Console.Write("red elephant;"); break; }
				case 4: { Console.Write("red horse;"); break; }
				case 5: { Console.Write("red car;"); break; }
				case 6: { Console.Write("red duck;"); break; }
				case 7: { Console.Write("red soldier;"); break; }
				case 11: { Console.Write("blue captain;"); break; }
				case 12: { Console.Write("blue guard;"); break; }
				case 13: { Console.Write("blue elephant;"); break; }
				case 14: { Console.Write("blue horse;"); break; }
				case 15: { Console.Write("blue car;"); break; }
				case 16: { Console.Write("blue duck;"); break; }
				case 17: { Console.Write("blue soldier;"); break; }
			}
			if (knockOut == 1 || knockOut == 11) isCaptured = true;
			if (!isCaptured && isCheckmate) Console.Write("yes;");
			else Console.Write("no;");
			if (isCaptured) Console.WriteLine("yes");
			else Console.WriteLine("no");
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
			Map map = new Map();
			map.Init();
			int Q = Read();
			for (int i = 1; i <= Q; i++)
			{
				map.Clear();
				map.sy = Read();
				map.sx = Read();
				map.ty = Read();
				map.tx = Read();
				if (map.isCaptured)
				{
					Console.WriteLine("Invalid command");
					continue;
				}
				map.CheckOut();
				map.Move();
				if (map.isInvalid) continue;
				map.isCheckmate = map.CheckMate(0) || map.CheckMate(1);
				map.Write();
				map.side ^= 1;
			}
		}
	}
}