#include<algorithm>
#include<cstring>
#include<cstdio>
using namespace std;
const int maxn(1e6+10);
char Str[maxn];
int minimalRepresentation(char *str)
{
    int n = strlen(str);
    int i = 0,j = 1, k = 0;
    while(i<n && j<n && k<n)
    {
        int t = str[(i+k)%n] - str[(j+k)%n] ;
        if(t == 0)
            k++;
        else
        {
            if(t>0)
                i+=k+1;
            else 
                j+=k+1;
            if(i==j)
                j++;
            k = 0;
        }
    }
    return i < j ? i : j;
}
int main()
{
    int T;scanf("%d",&T);while(T--)
    {
        scanf("%s",Str);printf("%d\n",minimalRepresentation(Str)+1);
    }
    return 0;
}