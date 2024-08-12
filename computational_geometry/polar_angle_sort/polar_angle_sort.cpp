// https://atcoder.jp/contests/typical90/tasks/typical90_i

#include<algorithm>
#include<cstdio>
#include<cmath>
#include<vector>

typedef double number;
const int maxn=2e3+1;
const number pi = std::acos(-1.0);

struct point
{
    number x,y,angle;

    point() = default;
    point(number x,number y):x(x),y(y)
    {
        angle = atan2(y,x) * 180.0 / pi; // 计算极角，atan2有一定的精度误差
    }

    inline bool operator<(const point& other) const
    {
        return angle < other.angle;
    }

    inline void print()
    {
        printf("Point: (%lf, %lf), Angle = %lf\n",x,y,angle);
    }
}pa,pb,pc;

class polar_angle_sort
{
protected:
    std::vector<point> points; // 其实根据需求，不一定需要存储这些点的原始数据吧，可能存个角度就可以了

public:
    void init()
    {
        points.clear();
    }

    void add_point(point p)
    {
        points.push_back(p);
    }

    void sort()
    {
        std::sort(points.begin(),points.end());
    }

    std::vector<point>* data()
    {
        return &points;
    }
}solver;

// AI 测试用代码 余弦定理计算3个点形成的角度 pb是顶点
number angle(point pa, point pb, point pc) {
    // 向量 ab 和向量 cb
    number ab_x = pa.x - pb.x;
    number ab_y = pa.y - pb.y;
    number cb_x = pc.x - pb.x;
    number cb_y = pc.y - pb.y;
    
    // 点积
    number dot_product = ab_x * cb_x + ab_y * cb_y;
    
    // 向量的模
    number ab_len = std::sqrt(ab_x * ab_x + ab_y * ab_y);
    number cb_len = std::sqrt(cb_x * cb_x + cb_y * cb_y);
    
    // 计算余弦值
    number cos_theta = dot_product / (ab_len * cb_len);
    
    // 计算角度（弧度）
    number angle_radians = std::acos(cos_theta);
    
    // 转换为角度
    number angle_degrees = angle_radians * 180.0 / pi;
    
    return angle_degrees;
}

std::vector<point> original_points;

int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i+=1)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        original_points.push_back(point((number)x,(number)y));
    }

    number ans = 0;

    // 以下代码的主要功能，在N个点中，找到3个点，其形成的角度最大（180度以内）
    // 枚举每一个顶点，作为中心(0,0)
    for(int i=0;i<n;i+=1)
    {
        const point& center = original_points[i];
        solver.init();
        for(int j=0;j<n;j+=1)
        {
            if(i==j) continue;

            const point& target = original_points[j];
            // 将其他点的相对位置加进去
            solver.add_point(point(target.x-center.x,target.y-center.y));
        }

        solver.sort();

        std::vector<point> *data = solver.data();
        int l = 0, r = 0;
        number k = 0; // 注意，一开始这里想错了
        // 类似滑动窗口，l和r
        while(l < data->size())
        {
            number diff = 0;
            while(r < data->size() && (diff = (*data)[r].angle + k - (*data)[l].angle) <= 180.0)
            {
                // ans = std::max(ans, diff);
                if(diff > ans)
                {
                    ans = diff;
                    // 保存一下答案，调试用的
                    pa = point(center.x+(*data)[r].x,center.y+(*data)[r].y);
                    pb = center;
                    pc = point(center.x+(*data)[l].x,center.y+(*data)[l].y);
                }
                r += 1;
                // 注意！r应该是可以循环的，否则会缺少答案的情况
                if(r >= data->size()) r -= data->size(), k += 360;
            }
            l += 1;
        }
    }

    printf("%.10lf\n",ans);

    return 0;
}