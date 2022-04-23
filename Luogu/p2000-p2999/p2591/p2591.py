a = input("").split()
n = int(a[0])
k = int(a[1])
ans = 1 if n == 1 else (k << 1) if k <= (n >> 1 | 1) else (n - k + 1) << 1
print(ans)