f = [[0] * 40 for _ in range (40)]
r = input("").split()
n = int(r[0])
m = int(r[1])
f[0][1] = 1
for i in range (1, m + 1):
    for j in range (1, n + 1):
        if j == 1:
            f[i][j] = f[i - 1][n] + f[i - 1][2]
        elif j == n:
            f[i][j] = f[i - 1][1] + f[i - 1][n - 1]
        else:
            f[i][j] = f[i - 1][j - 1] + f[i - 1][j + 1]
print(f[m][1])