num = int(input())
arr = []
for _ in range(num):
    a, b = [int(i) for i in input().split(" ")]
    arr += [(a,b)]
arr.sort()
print(num)
for a, b in arr:
    print(a,b)
    
