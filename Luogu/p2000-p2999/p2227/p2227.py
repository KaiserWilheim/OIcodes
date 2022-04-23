m = 1010
a = input("").split()
n = int(a[0])
s = int(a[1])

inp = input("").split();
p = [0] * (m + 1)
for i in range (1, n + 1):
	p[i] = int(inp[i-1])
A = [0] * (m + 1)
j = 1
for i in range (1, n + 1):
	A[i] = p[j]
	j = p[j]
z = 1
for i in range (0, s):
	z = (z * 2) % n
j = 1
B = [0] * (m + 1)
for i in range (1, n + 1):
	B[j] = A[i]
	j = (j + z - 1) % n + 1
x = [0] * (m + 1)
for i in range (1, n + 1):
	x[B[i]] = B[i % n + 1]
for i in range (1, n + 1):
	print(x[i],end = ' ')
print("")