ans = 1
n = int(input(""))
for i in range(2, n + 1):
    ans = ans * (4 * i - 2) // (i + 1)
print(str(ans))