#include<iostream>
#include<vector>

using namespace std;

int n;
vector<int>a;
vector<pair<int,int> >adj;
void solve(int i,int j)
{
    if(i == j)return;
    int m = i;
    for(int k = i;k<j;k++)
    {
        if(a[m] > a[k])m = k;
    }
    int J = j;
    for(int k = m + 1;k < j;k++)
    {
        if(a[J] > a[k])J = k;
    }
    adj.push_back(make_pair(a[m],a[J]));
    solve(m + 1, j);
    /*
    J = i;
    for(int k = m - 1;k > i;k--)
    {
        if(a[J] > a[k])J = k;
    }
    int f = 1;
    if(a[J] < a[J+1] && J != m)
    { 
        f = 0;
        adj.push_back(make_pair(a[m],a[J]));
    }
    */
    while(i<=j)
    {
        int M = i;
        if(i == m)return;
        for(int k = i;k<m;k++)
        {
            if(a[M] < a[k])M = k;
        }
        //cout<<i<<" "<<j<<" "<<M<<endl;
        int J = M;
        for(int k = J - 1;k>=i;k--)
        {
            if(a[k] < a[J])J = k;
        }
        adj.push_back(make_pair(a[m],a[J]));
        solve(i,M);
        i = M + 1;
    }
}
int main()
{
    cin>>n;
    a.resize(n);
    for(int i = 0;i<n;i++)cin>>a[i];
    for(int i= 0;i<n;i++)a[i]--;
    a.push_back(n);
    n++;
    int i =0 ;
    solve(0,n - 1);
    for(auto& x: adj)
    {
        cout<<x.first<<" "<<x.second<<endl;
    }
}