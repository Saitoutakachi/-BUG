#include "iostream"
#include "cmath"
#include "iomanip"
using namespace std;

#define pi acos(-1.0)

// �������
typedef struct node
{
    double x;
    double y;
    double r;
} circle; // ����Բ

double Area(circle a, circle b)
{
    double D = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
    if (D >= a.r + b.r) // �ж��Ƿ����к�����
        return 0;
    if (fabs(a.r - b.r) >= D) // �ж��Ƿ��ں���
        return (a.r < b.r) ? (pi * a.r * a.r) : (pi * b.r * b.r);

    double ang1 = acos((a.r * a.r + D * D - b.r * b.r) / (2 * a.r * D)); // Բa���Ե�Բ�Ľ�
    double ang2 = acos((b.r * b.r + D * D - a.r * a.r) / (2 * b.r * D)); // Բb���Ե�Բ�Ľ�
    return ang1 * a.r * a.r + ang2 * b.r * b.r - a.r * D * sin(ang1);
}

int main()
{
    circle a, b;
    cout << "������ԲA������Ͱ뾶:";
    cin >> a.x >> a.y >> a.r;
    cout << "������ԲB������Ͱ뾶:";
    cin >> b.x >> b.y >> b.r;
    cout.setf(ios::fixed);
    cout << "��Բ�ཻ�����Ϊ:" << setprecision(3) << Area(a, b);
    return 1;
}
