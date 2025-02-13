/*

最小表示法 minimal representation
字符串 S 的最小表示为：与 S 循环同构的所有字符串中字典序最小的字符串
字符串 S 的循环同构为：将字符串 S 头尾相接成环 能形成相同环的字符串都是循环同构

代码年久失修 未经测试

*/
#include <algorithm>
#include <cstring>

int minimalRepresentation(char *str) // str is 0-indexed
{
    int n = strlen(str);
    int i = 0, j = 1, k = 0;
    while(i<n && j<n && k<n)
    {
        int t = str[(i+k)%n] - str[(j+k)%n];
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
