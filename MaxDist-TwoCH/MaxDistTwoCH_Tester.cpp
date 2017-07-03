double tester(vector <Point> p, vector <Point> q)
{
    int n1= p.size();
    int n2 = q.size();
    double maxd = 0;
    for(int i=0;i<n1;i++)
    {
        for(int j=0;j<n2;j++)
        {
            if(dist_points(p[i],q[j]) > maxd)
                maxd = dist_points(p[i],q[j]);
        }
    }
    //cout << maxd << endl;
    printf("Tester Output: %.9lf\n", maxd);
}
