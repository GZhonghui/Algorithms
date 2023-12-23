#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int maxlen=1024;
struct Manacher
{
    char input[maxlen],proced[maxlen<<1];
    int proc()
    {
        proced[0]='$',proced[1]='#';
        int index=0,put=1;
        while(input[index]){
            proced[++put]=input[index++];proced[++put]='#';
        }
        int _size=put+1,mx=0,id=0,resLen=0,resCenter=0;
        vector<int> p(_size,0);
        for(int i=1;i<_size;i++)
        {
            p[i]=mx>i?min(p[2*id-i],mx-i):1;
            while(proced[i+p[i]]==proced[i-p[i]]) ++p[i];
            if(mx<i+p[i])
                mx=i+p[i],id=i;
            if(resLen<p[i])
                resLen=p[i],resCenter=i;
        }
        return resLen-1;
    }
};
int main()
{
    return 0;
}
