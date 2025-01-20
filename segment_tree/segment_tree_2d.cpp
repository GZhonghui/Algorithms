/*

二维线段树，支持区间修改，区间查询
可以支持的修改：加减，修改为目标值（等）
可以支持的查询：最大值，最小值，和（等）
Lazy标记

代码年久失修 整理时未经测试 仅供参考

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;

namespace segment_tree_2d {

const int maxn=(1<<20)+100;
struct Line{
    int start,end; Line(int x,int y){this->start=x,this->end=y;}
    inline int Mid(){return (start+end)>>1;}
    inline int Len(){return end+1-start;}
    inline Line left_half(){ return Line(start,this->Mid()); }
    inline Line right_half(){ return Line(this->Mid()+1,end); }
    inline bool IncludePos(int x){ return start<=x&&x<=end; }
    inline bool InlcudeLine(Line x){ return start<=x.start&&x.end<=end; }
    inline bool Intersect(Line x){ return !(start>x.end||end<x.start); }
};
int N,Sum[maxn<<3],_row,_colum,delta;
Line q_row(0,0),q_colum(0,0);
bool avaliable[maxn<<3];
inline int get_son(int node){ return 4*node-2; }
void push_up(int node)
{
    Sum[node]=0;for(int i=0;i<4;i++) if(avaliable[get_son(node)+i]) Sum[node]+=Sum[get_son(node)+i];
}
void bulid(int node,Line row,Line colum)
{
    if(row.Len()<=0||colum.Len()<=0) {avaliable[node]=false; return;}
    avaliable[node]=true; if(row.Len()==1&&colum.Len()==1){ Sum[node]=0;return; }
    bulid(get_son(node)+0,row.left_half(),colum.left_half());
    bulid(get_son(node)+1,row.left_half(),colum.right_half());
    bulid(get_son(node)+2,row.right_half(),colum.left_half());
    bulid(get_son(node)+3,row.right_half(),colum.right_half());
    push_up(node);
}
void update(int node,Line row,Line colum)
{
    if(!avaliable[node]) return ;
    if(!row.IncludePos(_row)||!colum.IncludePos(_colum)) return;
    if(row.Len()==1&&colum.Len()==1){ Sum[node]+=delta; return; }
    if(avaliable[get_son(node)+0]) update(get_son(node)+0,row.left_half(),colum.left_half());
    if(avaliable[get_son(node)+1]) update(get_son(node)+1,row.left_half(),colum.right_half());
    if(avaliable[get_son(node)+2]) update(get_son(node)+2,row.right_half(),colum.left_half());
    if(avaliable[get_son(node)+3]) update(get_son(node)+3,row.right_half(),colum.right_half());
    push_up(node);
}
int ask(int node,Line row,Line colum)
{
    if(!avaliable[node]) return 0;
    if(!row.Intersect(q_row)||!colum.Intersect(q_colum)) return 0;
    if(q_row.InlcudeLine(row)&&q_colum.InlcudeLine(colum)) return Sum[node];
    int ans=0;if(avaliable[get_son(node)+0]) ans+=ask(get_son(node)+0,row.left_half(),colum.left_half());
    if(avaliable[get_son(node)+1]) ans+=ask(get_son(node)+1,row.left_half(),colum.right_half());
    if(avaliable[get_son(node)+2]) ans+=ask(get_son(node)+2,row.right_half(),colum.left_half());
    if(avaliable[get_son(node)+3]) ans+=ask(get_son(node)+3,row.right_half(),colum.right_half());return ans;
}

} // namespace segment_tree_2d