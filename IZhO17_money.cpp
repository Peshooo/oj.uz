#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
 
const int N = 1000007;
 
int n,a[N],it[N],ans;
 
void update(int pos, int val) {
    for(;pos<N;pos+=pos&(-pos)) it[pos]+=val;
}
 
int query(int pos) {
    int ans=0;
    for(;pos>=1;pos-=pos&(-pos)) ans+=it[pos];
    return ans;
}
 
int query(int l, int r) {
    return l>r ? 0 : query(r)-query(l-1);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i,j;
 
    scanf("%d", &n);
    for(i=1;i<=n;i++) {
        scanf("%d", &a[i]);
    }
 
    for(i=1;i<=n;) {
        ++ans;
 
        j=i;
        while(j+1<=n && a[j]<=a[j+1] && query(a[i]+1,a[j+1]-1)==0) {
            ++j;
        }
 
        for(;i<=j;i++) {
            update(a[i],1);
        }
    }
 
    printf("%d\n", ans);
    
    return 0;
}
