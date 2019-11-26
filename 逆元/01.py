mod=int(998244353)
maxn=int(1e5+10)
inv=[0 for i in range(maxn)]
def rev(x):
    count=mod-2
    ans=1
    x=(x%mod+mod)%mod
    while count!=0:
        if count%2==1:
            ans=(x*ans)%mod
        x=(x*x)%mod
        count=count//2
    return ans
def main():
    inv[1]=1
    for i in range(2,maxn-1):
        inv[i]=(mod-(mod//i))*inv[mod%i]%mod
    T=int(input())
    for i in range(T):
        x=int(input())
        n=1;H=1
        while n<=x-2:
            n+=1
            H=((H*(4*n-2)%mod)*inv[n+1])%mod
        ans=((((H*(4*x-2)%mod)*inv[x+1])%mod)+mod-H)%mod
        print('Case #%d: %d'%(i+1,ans))
if __name__=='__main__':
    main()
