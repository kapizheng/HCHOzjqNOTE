#include<cmath>
#include<queue>
#include<cstdio>
#include<cctype>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const double pi=acos(-1),eps=1e-10;
struct Point
{
    double x,y;
    Point(double x0=0,double y0=0) : x(x0) , y(y0) { }
    friend bool operator<(Point a,Point b)
    {
        return a.x!=b.x?a.x<b.x:a.y<b.y;
    }
    friend Point operator+(const Point &a,const Point &b)
    {
        return Point(a.x+b.x,a.y+b.y);
    }   
    friend Point operator-(const Point &a,const Point &b)
    {
        return Point(a.x-b.x,a.y-b.y);
    }
    friend Point operator*(const Point &a,double b)
    {
        return Point(a.x*b,a.y*b);
    }
    friend Point operator/(const Point &a,double b)
    {
        return Point(a.x/b,a.y/b);
    }
    friend bool operator==(const Point &a,const Point &b){
        return a.x==b.x&&a.y==b.y;
    }  
};
typedef Point Vector;
double dcmp(double x)//符号判断 
{
    if(fabs(x)<eps)return 0;
    else return x<0?-1:1;
}

double Dot(const Point &a,const Point &b)//点积 
{
    return a.x*b.x+a.y*b.y;
}
double Cross(const Point &a,const Point &b)//叉积 
{
    return a.x*b.y-a.y*b.x;
}
double Length(const Point &a)//求向量的长度 
{
    return sqrt(Dot(a,a));
}
double Angle(const Point &a,const Point &b)//求两个向量的夹角（余弦定理） 
{
    return acos(Dot(a,b)/Length(a)/Length(b));//A^B=|A|*|B|*cosC
}
Point Rotate(const Point &a,double rad)//逆时针旋转rad，r一个圆的rad为2pi
{
    return Point(a.x*cos(rad)-a.y*sin(rad),a.x*sin(rad)+a.y*cos(rad));
}
Point Normal(Point &v)//求单位长度的法向量 
{
    double L=Length(v);
    return Point(-v.y/L,v.x/L);
}
Point getLineIntersection(const Point &P,const Point &v,const Point &Q,const Point &w)//求两个线段交点//Pv和Qw
{
    Vector u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}
bool SegmentProperIntersection(const Point &a1,const Point &b1,const Point &a2,const Point &b2)//两线段规范相交、即每条线段的端点分别在另一条一段的两侧 
{
    double c1=Cross(b1-a1,a2-a1),c2=Cross(b1-a1,b2-a1);
    double c3=Cross(b2-a2,a1-a2),c4=Cross(b2-a2,b1-a2);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
bool unnorm_Inter(const Point &a1,const Point &b1,const Point &a2,const Point &b2)//不规范相交
{
    return
    max( a1.x , b1.x )>=min( a2.x , b2.x )&&
    max( a2.x , b2.x )>=min( a1.x , b1.x )&&
    max( a1.y , b1.y )>=min( a2.y , b2.y )&&
    max( a2.y , b2.y )>=min( a1.y , b1.y )&&
    dcmp(Cross((a2-b1),(a1-b1)))*dcmp(Cross((b2-b1),(b1-b1)))<=0&&
    dcmp(Cross((a1-b2),(a2-b2)))*dcmp(Cross((b1-b2),(a2-b2)))<=0;
}

bool IsPointOnSegment(Point p,Point a1,Point a2)//点在线段上/直线
{
    return dcmp(Cross(p-a1,p-a2))==0 && dcmp(Dot(p-a1,p-a2))<0;
    //线上两点与待定点的差积为0，且点积小于0，两线段表示反方向，去掉第二个判断条件就是在直线上
}
double getDistToLine(const Point &P, const Point &A, const Point &B)//点到直线的有向距离（距离加绝对值） 
{
    Vector AB = B-A, AP = P-A;
    return Cross(AB, AP) / Length(AB);
}
double Area2(Point A, Point B, Point C){//计算BA,CA所构成的平行四边形的有向面积
    return Cross(B-A, C-A);
}
bool ToLeftTest(Point a, Point b, Point c){//判断ab在bc的顺时针方向
    return Cross(b - a, c - b) > 0;
}
Point GetLineProjection(Point P, Point A, Point B){//点P在直线AB上的投影点
    Vector v = B-A;
    return A+v*(Dot(v, P-A)/Dot(v, v));
}
//========================//
int ConvexHull(Point *p,int n,Point *ch)//构造逆时针凸包 //Andrew法，先求上凸包，再求下凸包
{
    sort(p+1,p+n+1);//先按照横坐标再按照纵坐标排序 
    int m=0;
    for(int i=1;i<=n;i++)
    {
        while(m>1 && Cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
        ch[++m]=p[i];
    }
    int k=m;
    for(int i=n-1;i;i--)
    {
        while(m>k && Cross(ch[m]-ch[m-1],p[i]-ch[m-1])<=0)m--;
        ch[++m]=p[i];
    }
    if(n>1)m--;
    return m;
}
double PolygonArea(Point *p,int n)//求逆时针构成的多边形（可不凸）面积 
{
    double ret=0;
    for(int i=2;i<n;i++)//第一个点是p[1],所以这样循环 
        ret+=Cross(p[i]-p[1],p[i+1]-p[1]);
    return ret/2;
}

bool isPointInPolygon(Point p,Point *poly,int n)//点在凸多边形内的判定 
{
    int wn=0;
    poly[n+1]=poly[1];
    for(int i=1;i<=n;i++)
    {
        if(IsPointOnSegment(p,poly[i],poly[i+1]))return -1;
        int k=dcmp(Cross(poly[i+1]-poly[i],p-poly[i]));
        int d1=dcmp(poly[i].y-p.y);
        int d2=dcmp(poly[i+1].y-p.y);
        if(k>0 && d1<=0 && d2>0)wn++;
        if(k<0 && d2<=0 && d1>0)wn--;
    }
    if(wn!=0)return 1;
    return 0;
}
void update(int a,int b){}
int findDiameter(Point *p,int n)//旋转卡壳求直径（Diatmeter：直径）
{
    int mx=0,j=2;
    p[n+1]=p[1];
    for(int i=1;i<=n;i++)
    {
        while(dcmp(Cross(p[i+1]-p[i],p[j+1]-p[j]))>0)
        {
            j++;
            j=(j-1)%n+1;
        }
        update(i,j);
        update(i+1,j);
        update(i,j+1);
        update(i+1,j+1);
    }
    return mx;
}
struct Line
{
    Point P;Vector v;
    double ang;
    Line() {}
    Line(Point P,Vector v):P(P),v(v){ang=atan2(v.y,v.x);}
    Point point(double t){
        return v+(P-v)*t;
    }
    friend bool operator<(Line a,Line b)
    {
        return  a.ang<b.ang;
    }
};
Point GetIntersection(Line a,Line b)//交点，要保证两直线相交，不然出现除数为0的情况
{
    Vector u=a.P-b.P;
    double t=Cross(b.v,u)/Cross(a.v,b.v);
    return a.P+a.v*t;
}
double DistanceToSegment(Point P, Point A, Point B){//点到线段的距离
    if(A == B)
        return Length(P-A);
    Vector v1 = B-A, v2 = P-A, v3 = P-B;
    if(dcmp(Dot(v1, v2)) < 0)
        return Length(v2);
    if(dcmp(Dot(v1, v3)) > 0)
        return Length(v3);
    return getDistToLine(P, A, B);
}
bool OnLeft(Line L,Point p)//暂时不懂什么意思，要推一下
{
    return Cross(L.v,p-L.P)>=0;
}
int HalfplaneIntersection(Line *L,int n,Point *poly)//半平面交 ，输入向量要逆时针输入，要是wa了可以把向量方向反下
{
    sort(L+1,L+n+1);//极角排序
    int first,last;
    Point *p=new Point[n+10];
    Line *q=new Line[n+10];
    q[first=last=0]=L[1];
    for(int i=2;i<=n;i++)
    {
        while(first<last && !OnLeft(L[i],p[last-1]))last--;
        while(first<last && !OnLeft(L[i],p[first]))first++;
        q[++last]=L[i];
        if(fabs(Cross(q[last].v,q[last-1].v))<eps)
        {
            last--;
            if(OnLeft(q[last],L[i].P))q[last]=L[i];
        }
        if(first<last)p[last-1]=GetIntersection(q[last-1],q[last]);
    }
    while(first<last && !OnLeft(q[first],p[last-1]))last--;
    if(last-first<=1)return 0;
    p[last]=GetIntersection(q[last],q[first]);
    int m=0;
    for(int i=first;i<=last;i++)poly[++m]=p[i];
    return m;
}
bool OK(Point A,Point B,Point C,Point D)
{
    int a=Cross(A-C,D-C)>0;
    int b=Cross(B-C,D-C)>0;
    if(a!=b)return true;
    else return false;
}
struct Circle{
    Point c;
    double r;
    Circle(Point c, double r):c(c), r(r) {}
    Point point(double a){//通过圆心角求坐标
        return Point(c.x + cos(a)*r, c.y + sin(a)*r);
    }
};
int getLineCircleIntersection(Point A,Point B, Circle C, double& t1, double& t2, vector<Point>& sol){//求圆与直线交点
    double a = A.x, b = B.x - C.c.x, c = A.y, d = B.y - C.c.y;
    double e = a*a + c*c, f = 2*(a*b + c*d), g = b*b + d*d - C.r*C.r;
    double delta = f*f - 4*e*g;//判别式
    if(dcmp(delta) < 0)//相离
        return 0;
    if(dcmp(delta) == 0){//相切
        t1 = -f /(2*e);
        t2 = -f /(2*e);
        sol.push_back(Point(A.x+(B.x-A.x)*t1,A.y+(B.y-A.y)*t1));//sol存放交点本身
        return 1;
    }
    //相交
    t1 = (-f - sqrt(delta))/(2*e);
    sol.push_back(Point(A.x+(B.x-A.x)*t1,A.y+(B.y-A.y)*t1));
    t2 = (-f + sqrt(delta))/(2*e);
    sol.push_back(Point(A.x+(B.x-A.x)*t2,A.y+(B.y-A.y)*t2));
    return 2;
}
double AreaOfOverlap(Point c1, double r1, Point c2, double r2){//两个圆相交所构成的两个扇形面积和减去其构成的筝形的面积
    double d = Length(c1 - c2);
    if(r1 + r2 < d + eps)
        return 0.0;
    if(d < fabs(r1 - r2) + eps){
        double r = min(r1, r2);
        return pi*r*r;
    }
    double x = (d*d + r1*r1 - r2*r2)/(2.0*d);
    double p = (r1 + r2 + d)/2.0;
    double t1 = acos(x/r1);
    double t2 = acos((d - x)/r2);
    double s1 = r1*r1*t1;
    double s2 = r2*r2*t2;
    double s3 = 2*sqrt(p*(p - r1)*(p - r2)*(p - d));
    return s1 + s2 - s3;
}

Point getcircle(Point p1,Point p2)//求以p1,p2为弦的圆心
{
    Point mid = Point((p1.x+p2.x)/2,(p2.y+p1.y)/2);
    double angle = atan2(p2.y-p1.y,p2.x-p1.x);
    double d = sqrt(1.0-Length(p1-mid)*Length(p1-mid));
    return Point(mid.x+d*sin(angle),mid.y-d*cos(angle));
}//n^2log(n)这个类似扫描线的做法，以每一个点为圆心化圆，枚举与其相交得圆，保存交点和角度，按角度排序后，扫一遍。

//过三点求圆心坐标
//3种做法
//====================//
Point waixin(Point a,Point b,Point c)//这个需要先判断是不是在同一条线上，必要的时候可以把除法去掉，如下面另外一个板子的做法
{
  double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1*a1 + b1*b1)/2;
  double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2*a2 + b2*b2)/2;
  double d = a1*b2 - a2*b1;//为0的话，三点共线特判一下
  
  return Point(a.x + (c1*b2 - c2*b1)/d, a.y + (a1*c2 -a2*c1)/d);
}

typedef long long ll;
struct node
{
    ll x,y,d;
};
node circle_center(const Point a,const Point b,const Point c)
{
    node center;
    ll a1 = b.x-a.x,b1=b.y-a.y,c1=(a1*a1+b1*b1);
    ll a2 = c.x-a.x,b2=c.y-a.y,c2=(a2*a2+b2*b2);
    center.d=a1*b2-a2*b1;
    if(center.d==0){//判断3点共线
        center.x=1e18;
        return center;
    }
    center.x=c1*b2-c2*b1;
    center.y=a1*c2-a2*c1;

    return center;
}//求圆心
void Cir(double ax,double ay,double bx,double by,double cx,double cy,double &x,double &y)
{
     double a1=atan2(by-ay,bx-ax)+acos(-1.)/2;
     double a2=atan2(cy-by,cx-bx)+acos(-1.)/2;
     ax=(ax+bx)/2,ay=(ay+by)/2;
     bx=(cx+bx)/2,by=(cy+by)/2;
     double r=(sin(a2)*(ax-bx)+cos(a2)*(by-ay))/(sin(a1)*cos(a2)-sin(a2)*cos(a1));
     x=ax+r*cos(a1),y=ay+r*sin(a1);
}

//三角形面积，海伦公式：sqrt(p*(p-a)*(p-b)*(p-c)),p=(a+b+c)/2
//a*b*sinC/2
//外心（板子有了）三边中垂线交点，到三角形三个顶点距离相同
//内心：角平分线的交点，到三角形三边的距离相同，先求向量的角度，然后用rotate求两个线段，再求交点
//垂心：三条高线的交点，对两条边旋转90°，之后求交点
//重心：三条中线的交点，到三角形三顶点距离的平方和最小的点，三角形内到三边距离之积最大的点
//任意凸多边形外角和均为360°、
// 任意凸多边形内角和为(n−2)180°
//pick定理：2*S=2*a+b-2,S表示多边形面积，a表示多边形内部点数，b表示多边形边界上的点数
//
/*tan和atan接受的输出都是弧度需要转换
前者接受的是一个正切值（直线的斜率）得到夹角，但是由于正切的规律性本可以有两个角度的但它却只返回一个
因为atan的值域是从-90~90也就是它只处理一四象限，所以一般不用它。第二个atan2(double y,double x) 其中y代表已知点的Y坐标 
同理x 返回值是此点与远点连线与x轴正方向的夹角，这样它就可以处理四个象限的任意情况了，它的值域相应的也就是-180~180了。
*/
//================================//
Point p[100000];
int main()
{
    int n;
	cin>>n;
	
    return 0;
}