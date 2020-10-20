#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=1000010;
struct KMP
{
    char strA[maxn],strB[maxn];
    int next[maxn];
    void init(){ strA[1]=strB[1]=0; }
    void getText(){ scanf("%s",strA+1); }
    void getTarget(){ scanf("%s",strB+1); }
    void calcNext()
    {
        int p=0;
        for(int i=2;strB[i];i++)
        {
            while(p>0&&strB[p+1]!=strB[i]) p=next[p];
            if(strB[p+1]==strB[i]) p++; next[i]=p;
        }
    }
    int find()
    {
        vector<int> ans;
        int p=0;
        for(int i=1;strA[i];i++)
        {
            while(p>0&&strB[p+1]!=strA[i]) p=next[p];
            if(strB[p+1]==strA[i]) p++;
            if(!strB[p+1])
            {
                ans.push_back(i+1-p);
                p=next[p];
            }
        }
        return ans.size();
    }
};
int main()
{
    return 0;
}