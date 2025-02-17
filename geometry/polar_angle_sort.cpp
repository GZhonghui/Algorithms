/*

# 极角排序 偏角ソート polar_angle_sort

- **极角排序** https://www.cnblogs.com/kingwz/p/16151120.html

## 什么是极角？
> 极角，指的就是以x轴正半轴为始边，逆时针转过的角，这个角的范围是[0,2π]。极角排序就是按极角大小排序...

## 基本思路
atan2计算出极角，再根据极角的大小排序即可

## 例题
- https://atcoder.jp/contests/typical90/tasks/typical90_i 从N个点中，找到3个点，使其组成的角度最大

*/

#include "computational_geometry.h"

namespace polar_angle_sort {
using namespace computational_geometry;

class PointWithAngle : public Point2f
{
public:
    f64 angle;

    PointWithAngle() = default;
    PointWithAngle(f64 x, f64 y) : Point2f(x, y) {
        angle = atan2(y, x) * 180.0 / pi; // 计算极角，atan2有一定的精度误差
    }

    inline bool operator<(const PointWithAngle& other) const {
        return angle < other.angle;
    }
}pa, pb, pc;

class polar_angle_sort
{
protected:
    std::vector<PointWithAngle> points; // 其实根据需求，不一定需要存储这些点的原始数据吧，可能存个角度就可以了

public:
    void init()
    {
        points.clear();
    }

    void add_point(PointWithAngle p)
    {
        points.push_back(p);
    }

    void sort()
    {
        std::sort(points.begin(),points.end());
    }

    std::vector<PointWithAngle>* data()
    {
        return &points;
    }
}solver;

// AI 测试用代码 余弦定理计算3个点形成的角度 pb是顶点
f64 angle(PointWithAngle pa, PointWithAngle pb, PointWithAngle pc) {
    // 向量 ab 和向量 cb
    f64 ab_x = pa.x - pb.x;
    f64 ab_y = pa.y - pb.y;
    f64 cb_x = pc.x - pb.x;
    f64 cb_y = pc.y - pb.y;
    
    // 点积
    f64 dot_product = ab_x * cb_x + ab_y * cb_y;
    
    // 向量的模
    f64 ab_len = std::sqrt(ab_x * ab_x + ab_y * ab_y);
    f64 cb_len = std::sqrt(cb_x * cb_x + cb_y * cb_y);
    
    // 计算余弦值
    f64 cos_theta = dot_product / (ab_len * cb_len);
    
    // 计算角度（弧度）
    f64 angle_radians = std::acos(cos_theta);
    
    // 转换为角度
    f64 angle_degrees = angle_radians * 180.0 / pi;
    
    return angle_degrees;
}

std::vector<Point2f> original_points;

void toolkit()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i+=1)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        original_points.push_back(Point2f((f64)x,(f64)y));
    }

    f64 ans = 0;

    // 以下代码的主要功能，在N个点中，找到3个点，其形成的角度最大（180度以内）
    // 枚举每一个顶点，作为中心(0,0)
    for(int i=0;i<n;i+=1)
    {
        const Point2f& center = original_points[i];
        solver.init();
        for(int j=0;j<n;j+=1)
        {
            if(i==j) continue;

            const Point2f& target = original_points[j];
            // 将其他点的相对位置加进去
            solver.add_point(PointWithAngle(target.x-center.x,target.y-center.y));
        }

        solver.sort();

        std::vector<PointWithAngle> *data = solver.data();
        int l = 0, r = 0;
        f64 k = 0; // 注意，一开始这里想错了
        // 类似滑动窗口，l和r
        while(l < data->size())
        {
            f64 diff = 0;
            while(r < data->size() && (diff = (*data)[r].angle + k - (*data)[l].angle) <= 180.0)
            {
                // ans = std::max(ans, diff);
                if(diff > ans)
                {
                    ans = diff;
                    // 保存一下答案，调试用的
                    pa = PointWithAngle(center.x+(*data)[r].x,center.y+(*data)[r].y);
                    pb = PointWithAngle(center.x,center.y);
                    pc = PointWithAngle(center.x+(*data)[l].x,center.y+(*data)[l].y);
                }
                r += 1;
                // 注意！r应该是可以循环的，否则会缺少答案的情况
                if(r >= data->size()) r -= data->size(), k += 360;
            }
            l += 1;
        }
    }

    printf("%.10lf\n",ans);
}

} // namespace polar_angle_sort