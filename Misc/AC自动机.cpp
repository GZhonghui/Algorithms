#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1e5+10;
int ans[maxn],cnt[maxn];
char str[maxn];
struct acmation
{
    int ch[maxn][26],end[maxn],fail[maxn],node;
    void init()
    {
        node=0;
        memset(ch,0,sizeof(ch));
        memset(end,0,sizeof(end));
        memset(fail,0,sizeof(fail));
    }
    void add(int s,int t,int num)
    {
        int x=0;
        for(int i=s;i<=t;i++)
        {
            if(!ch[x][str[i]-'a']) ch[x][str[i]-'a']=++node;
            x=ch[x][str[i]-'a'];
        }
        end[x]=num;
    }
    void build()
    {
        queue<int> Q;
        for(int i=0;i<26;i++) if(ch[0][i]) Q.push(ch[0][i]);
        while(!Q.empty())
        {
            int x=Q.front();Q.pop();
            for(int i=0;i<26;i++)
                if(ch[x][i]) fail[ch[x][i]]=ch[fail[x]][i],Q.push(ch[x][i]);
                else ch[x][i]=ch[fail[x]][i];
        }
    }
    void query(char *str)
    {
        int x=0;
        for(int i=1;str[i];i++)
        {
            x=ch[x][str[i]-'a'];
            for(int p=x;p&&~end[p];p=fail[p])
            {
                if(!end[p]) continue;
                cnt[end[p]]+=1;
            }
        }
    }
};
int main()
{
    return 0;
}