class Sieve:
    maxn = int(2e6 + 10)

    def __init__(self):
        self.check = [False] * Sieve.maxn
        self.prime = list()

    def calc(self, n: int) -> None:
        for i in range(2,n+1):
            if not self.check[i]:
                self.prime.append(i)
            for j in self.prime:
                if i*j > n: break
                self.check[i*j] = True
                if i%j == 0: break