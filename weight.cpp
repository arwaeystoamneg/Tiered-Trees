#include<iostream> 
#include<vector> 
using namespace std; 
int main() {     
    int n;     
    cin>>n;     
    vector<int>a(n + 1);     
    for(int i= 1;i<n + 1;i++)cin>>a[i];     
    a.push_back(n + 1);     
    a.push_back(0);     
    a[0] = n + 2;     
    int ans = 0;     
    for(int x= 1;x<n + 1;x++) {         
        // determine i, the index of the nondescent, x         
        int i= 0;         
        for(;i<a.size();i++) {             
            if(a[i] == x)break;         
        }         
        if(a[i] > a[i+1])continue;         
        // determine j, the first number after i that is less than i (?)         
        int j = i + 1;         
        for(;j<a.size();j++) {             
            if(a[j] < a[i])break;         
        }         
        // determine m, the largest number between i and j inclusive (guaranteed not          
        // to be i because i is not a descent and not j because j is less than i)         
        int m = i;         
        for(int k = i;k<=j;k++) {             
            if(a[m] < a[k])m = k;         
        }         
        // m is guaranteed to be a descent and the right cutoff of i will be immedietly right of m                  
        // j will create a cutoff at m iff there isnt a cutoff between j and m prior to j and that          
        // is only possible if a bigger number created a cutoff there but that would require a cutoff at m (?)                  
        // it is guaranteed nothing smaller than i is between i and m because otherwise j would be that point         
        // even if that index is a descent, it would be followed by a number smaller which would be j         
        // as a result, the right end of i's tree will be to m (?)                  
        // determine M, the first number to the right of m (and i) that is greater than m         
        // we claim the left cutoff of i is at M OR it is at a previously deleted node         
        int M = m;         
        for(;M >= 0;M--) {             
            if(a[M] > a[m] || a[M] < a[i])break;         
        }        
        for(int k = M + 1;k<=m;k++) {             
            ans += (a[k] > a[k+1]);         
        }     
    }     
    cout<<ans - n<<endl; 
}