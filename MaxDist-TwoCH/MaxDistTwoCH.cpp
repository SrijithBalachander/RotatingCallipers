#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define INF 1e+20
using namespace std;

struct Point{
    double x, y;

    Point operator = (Point p){
        x = p.x; y=p.y;
        return *this;
    }
    Point operator - (Point p)
    {
        x-=p.x; y-=p.y;
        return *this;
    }
    bool operator < (const Point &p) const{
        return (x < p.x || (x == p.x && y < p.y));}

    bool operator == (const Point &p) const{
        return (x == p.x && y==p.y);}

    bool operator != (const Point &p) const{
        return (x!=p.x || y!=p.y);
    }

    friend ostream& operator << (ostream& s, Point& p){
        s << p.x <<" " << p.y << endl;
        return s;}
    friend istream & operator >> (istream& s, Point& p){
        s >> p.x >> p.y;
        return s;}
};

double crossp(const Point &O, const Point &A, const Point &B){
    return ((A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x));
}

double dist_points(Point X, Point Y)
{
    double x = (Y.x-X.x)*(Y.x-X.x);
    double y = (Y.y-X.y)*(Y.y-X.y);
    return sqrt(x+y);
}

vector <Point> revch(vector<Point> X)
{
    vector <Point> Y;
    int n=X.size();
    for(int i=0;i<n;i++)
        Y.pb(X[n-i-1]);

    return Y;
}

vector <Point> hull(vector <Point> P){
    int n=P.size(), k=0;
    vector<Point> X(2*n);
    sort(P.begin(), P.end());
    for(int i=0;i<n;i++)
    {
        while(k>=2)
        {
            if(crossp(X[k-2], X[k-1], P[i]) <= 0)
                k--;

            else
                break;
        }
        X[k++] = P[i];
    }

    for(int i=n-2, t=k+1;i>=0;i--)
    {
        while(k>=t)
        {
            if(crossp(X[k-2], X[k-1], P[i]) <= 0)
                k--;
            else
                break;
        }
        X[k++] = P[i];
    }
    X.resize(k);
    X = revch (X); //for clockwise arrangement*/
    X.resize(k-1);
    return X;
}

vector < pair<Point,Point> > APP(vector <Point> p, vector <Point> q)
{
    vector < pair <Point, Point> > app;
    int n1= p.size();
    int n2 = q.size();

    int i, j, k;
    double miny=INF, maxy=-INF;

    for(int x=0;x<n2;x++)
    {
        if(miny > p[x].y)
            miny = p[x].y, k=x;
    }
    for(int x=0;x<n1;x++)
    {
        if(maxy < q[x].y)
            maxy = q[x].y, i=x;
    }
    j=k;
    while(i<2*n1 && j<n2+k)
    {
        //res=max(distPoint(p[i],p[j]),res);
        app.pb(mp(p[i%n1],q[j%n2]));
        //cout << "pairs: " << p[i%n1] << q[j%n2];
        while(j<n2-1+k && abs(crossp(p[(i+1)%n1],p[i%n1],q[(j+1)%n2]) >
                  abs(crossp(p[(i+1)%n1],p[i%n1],q[j%n2]))))
        {
            j++;
            //res=max(distPoint(p[i],p[j]),res);
            app.pb(mp(p[i%n1],q[j%n2]));
        }
        i++;
    }
    return app;
}


int main()
{
    freopen("MaxDistTwoCH_Testcases.txt", "r", stdin);
    //freopen("MaxDistTwoCH_Testcases.out", "w", stdout);
    int N1, N2, cnt=0;
    while(cin>>N1)
    {
        Point Z;

        vector <Point> p, q;
        for(int i=0;i<N1;i++)
        {
            cin>>Z;
            p.pb(Z);
        }
        cin>>N2;
        for(int i=0;i<N2;i++)
        {
            cin>>Z;
            q.pb(Z);
        }

        vector <Point> ch1, ch2;
        ch1 = hull(p);
        ch2 = hull(q);

        vector < pair<Point,Point> > app;
        app = APP(ch1, ch2);

        double maxx=0.0;
        for(int i=0;i<app.size();i++)
        {
            if(maxx < dist_points(app[i].first, app[i].second))
                maxx = dist_points(app[i].first, app[i].second);
        }

        printf("Program Output: %.9lf\n", maxx);
        //tester(ch1, ch2);
    }
    return 0;
}

