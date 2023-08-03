#include<iostream>
#include<vector>

using namespace std;

int n;
vector<int>a;
vector<pair<int,int> >adj;// adjacency list
void solve(int i,int j)
{
    //create the tree correswponding to the permutation between index i and j
    // max weight tree 
    // i <= j because i-j is the tree's range
    if(i == j)return;
    int m = i;
    // make m the index of the minimum between i and j
    for(int k = i;k<=j;k++)
    {
        if(a[m] > a[k])m = k;
    }
    // do the right side (pi_R)
    int J = j;
    // find J, the index max descent between m + 1 and j and create an edge between m and J
    for(int k = m + 1;k < j;k++)
    {
        if(a[k] > a[k+1])
        {
            if(a[J] < a[k])J = k;
        }
    }
    adj.push_back(make_pair(a[m],a[J]));
    solve(m + 1, j);
    // do the left side (pi_L)

    while(i<=j)
    {
        int M = i;
        // M is index of biggest from i to j
        if(i == m)return;  //nothing left on the left
        for(int k = i;k<m;k++)
        {
            if(a[M] < a[k])M = k;
        }
        //cout<<i<<" "<<j<<" "<<M<<endl;
        int J = M;
        for(int k = J - 1;k>=i;k--)
        {
            if (a[k] > a[k + 1])
            {
                if(a[k] > a[J])J = k;
            }
        }
        adj.push_back(make_pair(a[m],a[J]));
        solve(i,M);
        i = M + 1;
    }
}
int main()
{
    // input n and a
    // n is the size and a is the permutation indexed at 1
    cin>>n;
    a.resize(n);
    for(int i = 0;i<n;i++)cin>>a[i];
    // shift 1-index to 0-index
    for(int i = 0;i<n;i++)a[i]--;
    // add n to the back to commplete the permutation. shift n to match the size of the vector
    a.push_back(n);
    n++;
    int i =0 ;
    solve(0,n - 1);
    for(auto& x: adj)
    {
        cout<<x.first<<" "<<x.second<<endl;
    }
}