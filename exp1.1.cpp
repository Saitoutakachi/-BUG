#include "iostream"
#include "cmath"
#include "iomanip"
using namespace std;

#define pi acos(-1.0)

// 面向对象
typedef struct node
{
    double x;
    double y;
    double r;
} circle; // 定义圆

double Area(circle a, circle b)
{
    double D = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    if (D >= a.r + b.r) // 判断是否相切和相离
        return 0;
    if (fabs(a.r - b.r) >= D) // 判断是否内含于
        return (a.r < b.r) ? (pi * a.r * a.r) : (pi * b.r * b.r);

    double ang1 = acos((a.r * a.r + D * D - b.r * b.r) / (2 * a.r * D)); // 圆a所对的圆心角
    double ang2 = acos((b.r * b.r + D * D - a.r * a.r) / (2 * b.r * D)); // 圆b所对的圆心角
    return ang1 * a.r * a.r + ang2 * b.r * b.r - a.r * D * sin(ang1);
}

int main()
{
    circle a, b;
    cout << "请输入圆A的坐标和半径:";
    cin >> a.x >> a.y >> a.r;
    cout << "请输入圆B的坐标和半径:";
    cin >> b.x >> b.y >> b.r;
    cout.setf(ios::fixed);
    cout << "两圆相交的面积为:" << setprecision(3) << Area(a, b);
    return 1;
}
