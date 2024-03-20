#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
class PA
{
private:
    static const int N = 100010;
    struct Node
    {
        int len;
        int ptr[26], fail;
        Node(int len = 0) : len(len), fail(0) { memset(ptr, 0, sizeof(ptr)); }
    }nd[N];
    int size, cnt;
    int cur;
    char s[N];
    int getfail(int x)
    {
        while (s[size - nd[x].len - 1] != s[size])
        {
            x = nd[x].fail;
        }
        return x;
    }
public:
    PA() : size(0), cnt(0), cur(0)
    {
        nd[cnt] = Node(0);
        nd[cnt].fail = 1;
        nd[++cnt] = Node(-1);
        nd[cnt].fail = 0;
        s[0] = '$';
    }
    void extend(char c)
    {
        s[++size] = c;
        int now = getfail(cur);
        if (!nd[now].ptr[c - 'a'])
        {
            int tmp = ++cnt;
            nd[tmp] = Node(nd[now].len + 2);
            nd[tmp].fail = nd[getfail(nd[now].fail)].ptr[c - 'a'];
            nd[now].ptr[c - 'a'] = tmp;
        }
        cur = nd[now].ptr[c - 'a'];
    }
    int qlen()
    {
        return nd[cur].len;
    }
}A, B;
const int maxn=3e5+10;
char str[maxn];
int main()
{
    scanf("%d",str+1);
    for(int i=1;str[i];i+=1) A.extend(str[i]);
    printf("%d",A.qlen());
    
    return 0;
}