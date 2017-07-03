#include<bits/stdc++.h>
#define pb push_back
#define mp make_pair
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

vector < pair<Point,Point> > APP(vector <Point> p)
{
    vector < pair <Point, Point> > app;
    int n= p.size();
    int i=n-1,j=0,k=1;
    while(abs(crossp(p[j],p[i], p[k+1]) >
              abs(crossp(p[j],p[i],p[k]))))
    {
        k++;
    }
    i=0,j=k;
    while(i<=k && j<n)
    {
        app.pb(mp(p[i],p[j]));
        while(j<n-1 && abs(crossp(p[i+1],p[i],p[j+1]) >
                  abs(crossp(p[i+1],p[i],p[j]))))
        {
            j++;
            app.pb(mp(p[i],p[j]));
        }
        i++;
    }
    return app;
}

int main()
{
    int N, cnt=0;
    cin>>N;
    Point Z;
    set <Point> sp;
    vector <Point> p;
    while(cin>>Z)
        cnt++, sp.insert(Z);

    for(set <Point> ::iterator it = sp.begin();it!=sp.end();it++)
        p.pb((*it));

    if(cnt<2)
    {
        return 0;
    }


    vector <Point> ans;
    ans = hull(p);


    if(ans.size()<2)
    {
        cout<< 0.0 <<endl;
        return 0;
    }

    else if(ans.size()==2)
    {
        double temp;
        temp = dist_points(ans[0], ans[1]);
        printf("%.9lf\n", temp);
        return 0;
    }
    vector < pair<Point,Point> > app;

    app = APP(ans);


    double maxx=0.0;
    for(int i=0;i<app.size();i++)
    {
        if(maxx < dist_points(app[i].first, app[i].second))
            maxx = dist_points(app[i].first, app[i].second);
    }

    printf("%.9lf\n", maxx);
    return 0;
}

