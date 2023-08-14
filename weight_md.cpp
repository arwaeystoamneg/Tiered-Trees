#include<iostream>
#include<vector>

using namespace std;
int n;
vector<int>a;
// directed edges
vector<vector<int> >adj;
int ans;
int fw(int i){
    if(adj[i].size() == 0)return 1;
    int d = 0;
    for(int x: adj[i]){
        d+= fw(x);
    }
    ans += d;
    return d;
}
void mdt(int i, int j){
    //cout<<i<<" "<<j<<endl;
    if(i==j)return;
    //find min in [i,j]
    int m= i;
    for(int k = i + 1;k<=j;k++){
        if(a[m] > a[k])m = k;
    }
    //do right
    int m1 = m + 1;
    for(int k = m + 2;k<=j;k++){
        if(a[m1]>a[k])m1 = k;
    }
    //cout<<"l "<<m<<" "<<m1<<endl;
    adj[a[m]].push_back(a[m1]);
    mdt(m+1,j);
    int i1 = i;
    while(i1!=m){
        int M = i1;
        for(int k = i1+1;k<=m;k++){
            if(a[M]<a[k])M=k;
        }
        int m1 = i1;
        for(int k = i1+1;k<=M;k++){
            if(a[m1]>a[k])m1=k;
        }
        adj[a[m]].push_back(a[m1]);
        mdt(i1,M);
        i1=M+1;
    }
}

int main(){
    cin>>n;
    a.resize(n);
    // input n and a, indexed at 1
    for(int i= 0;i<n;i++)cin>>a[i],a[i]--;
    a.push_back(n);
    n++;
    //construct mindecomp tree
    adj.resize(n);
    mdt(0, n - 1);
    //compute weight from md tree
    fw(0);
    cout<<ans-n+1<<endl;
    //for(int i=0;i<n;i++){
    //    cout<<i<<endl;
    //    for (auto x:adj[i])cout<<x<<" ";
    //    cout<<endl;
    //}
}