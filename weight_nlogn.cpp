#include<iostream> 
#include<vector> 
#include<cmath>
using namespace std; 
template<int t>class st{
    //type 0 is min, type 1 is max
    struct T{
        int x;
        T(){
            if(t == 0)
                x = 100000;
            else
                x = -100000;
        }
        T(int y){
            x = y;
        }
        T operator+(const T& y)const {
            if(t == 0)
                return T(min(x,y.x));
            return T(max(x,y.x));
        }
        int val(){
            if(x == -100000)return -1;
            if(x == 100000) return 1000;
            return x;
        }
    };
    int h;
    public:vector<T> tree;
    // init(0,0,MAXN - 1)
    public:void init(int n){
        h = log2(n + 1) + 1;
        tree.resize((1<<h + 1) - 1);
        init(0,0,(1<<h) - 1);
    }
    void init(int i,int tl,int tr){
        if(tl == tr){
            tree[i] = T();
            return;
        }
        int mid = (tl + tr)/2;
        init(2*i+1,tl,mid);
        init(2*i+2,mid+1,tr);
        tree[i] = tree[2*i+1]+tree[2*i+2];
    }
    public:int query(int l,int r){
        return query(0,0,(1<<h) -1,l,r).val();
    }
    T query(int i,int tl,int tr,int l,int r){
        if(tl > r || tr < l)return T();
        if(tl >= l && r >= tr){
            return tree[i];
        }
        int mid = (tl + tr)/2;
        return query(2*i+1,tl,mid,l,r) + query(2*i+2,mid+1,tr,l,r);
    }
    public:void update(int p,int x){
        update(0,0,(1<<h) - 1,p,x);
    }
    void update(int i,int tl,int tr,int p,int x){
        if(tl > p || tr < p)return;
        if(tl == tr){
            tree[i] = T(x);
            return;
        }
        int mid = (tl + tr)/2;
        update(2*i+1,tl,mid,p,x);
        update(2*i+2,mid+1,tr,p,x);
        tree[i] = tree[2*i+1]+tree[2*i+2];
    }
};
int fw(int n, vector<int>&a)
{    
    vector<int>idx(n);
    for(int i =0 ;i<n;i++)idx[a[i]] = i;
    vector<int>ps_desc(n + 1);
    for(int i= 0;i<n;i++)ps_desc[i+1] = ps_desc[i] + (i != n - 1 && a[i] > a[i+1]);
    int ans = 0;     
    vector<int>ra(n);//less and right
    vector<int>lb(n);//more and left
    vector<int>la(n);//less and left
    st<0>r;
    r.init(n);
    st<1>l;
    l.init(n);
    st<1>ma;
    ma.init(n);
    for(int i= 0;i<n;i++)ma.update(i,a[i]);
    for(int i= 0;i<n;i++){
        la[a[i]] = l.query(0,a[i]);
        lb[a[i]] = l.query(a[i],n);
        l.update(a[i],i);
    }
    for(int i= n - 1;i>=0;i--){
        ra[a[i]] = r.query(0,a[i]);
        r.update(a[i],i);
    }
    for(int x= 1;x<n;x++) {           
        int i = idx[x];
        if(a[i] > a[i+1])continue;
        int j = ra[a[i]];
        int m = idx[ma.query(i, j)];
        int M = lb[a[m]];
        M = max(M, la[a[i]]);
        ans += ps_desc[m + 1] - ps_desc[M + 1];
    }     
    return ans - n + 3;
}
int main() {     
    int n;     
    cin>>n;     
    vector<int>a(n + 1);     
    for(int i= 1;i<n + 1;i++)cin>>a[i];   
    a.push_back(n + 1);  
    a.push_back(0);     
    a[0] = n + 2;      
    n = a.size();
    cout<<fw(n,a)<<endl;
}