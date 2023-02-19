from math import *
def C(n, m):
	return factorial(n) // factorial(m) // factorial(n - m)
n, m = map(int, input().split())
print(C(n + m, m) - C(n + m, m - 1))