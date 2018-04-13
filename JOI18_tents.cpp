#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
 
const int N = 3007;
const int MOD = (1e9) + 7;
 
int n,m;
bool used[N][N];
int state[N][N];
 
int choose(int n, int k) {
    if(k==0) return 1;
    if(k==1) return n;
    return n*(n-1)/2;
}
 
int ways(int k) {
    if(k==0) return 1;
    if(k==1) return 4;
    return 1;
}
 
int recurse(int n, int m) {
    if(n==0 || m==0) return 1;
 
    if(used[n][m]) return state[n][m];
    
    long long ans=0;
 
    //1) There is a tent in (1,1) and no other tents in row 1 or column 1
    ans+=4ll*recurse(n-1,m-1);
 
    //2) There is a tent in (1,1) and a tent in (1,x)
    if(m>=2) ans+=(m-1)*1ll*recurse(n-1,m-2);
 
    //3) There is a tent in (1,1) and a tent in (x,1)
    if(n>=2) ans+=(n-1)*1ll*recurse(n-2,m-1);
 
    int row,col;
 
    for(row=0;row<=2 && row+1<=n;row++) {
        for(col=0;col<=2 && col+1<=m;col++) {
            ans+=choose(n-1,row)*1ll*choose(m-1,col)*ways(row)*ways(col)%MOD*recurse(n-1-row,m-1-col);
            
            int rows_left=n-1-row,cols_left=m-1-col;
 
            if(row==1 && cols_left>=1) ans+=choose(n-1,row)*1ll*choose(m-1,col)*cols_left*ways(col)%MOD*recurse(rows_left,cols_left-1);
            if(col==1 && rows_left>=1) ans+=choose(n-1,row)*1ll*choose(m-1,col)*ways(row)*rows_left%MOD*recurse(rows_left-1,cols_left);
            if(row==1 && col==1 && rows_left>=1 && cols_left>=1) ans+=choose(n-1,row)*1ll*choose(m-1,col)*rows_left*cols_left%MOD*recurse(rows_left-1,cols_left-1);
        }
    }
 
    used[n][m]=true;
    return state[n][m]=ans%MOD;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
    scanf("%d %d", &n, &m);
    printf("%d\n", (recurse(n,m)-1+MOD)%MOD);
    
    return 0;
}
