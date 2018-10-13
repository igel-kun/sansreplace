import random

def choose(n, k):
    "k distinct integers 0 <= x < n, sorted"
    t = n - k + 1
    d = []
    for i in range(k):
        r = random.randrange(t + i)
        if r < t:
            d.append(r)
        else:
            d.append(d[r - t])
    d.sort()
    return [i + v for i, v in enumerate(d)]
