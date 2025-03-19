/*

## suffix_automaton
后缀自动机

后缀数组 & LCP数组

*/

#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxlen=1e5+10;
struct Node
{
    int len,link;
    int next[26];
    Node(int len=0,int link=0)
    {
        this->len=len,this->link=link;
    }
};
Node SAM[maxlen<<1];
int SAM_Size=0,last=0;
void SAM_Init()
{
    SAM[0].len=0;SAM[0].link=-1;
    SAM_Size=1;last=0;
    memset(SAM[0].next,0,sizeof(int)*26);
}
void SAM_Push(char x)
{

}
int main()
{

    return 0;
}