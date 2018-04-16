#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N = 2007;
const int INF = N + 7;

int n,a,b;
long long arr[N];
long long ans;
long long val;
bool used[N][N],state[N][N];
bool used2[N];
int state2[N];

bool recurse(int pos, int groups) {
    if(pos>n) return a<=groups && groups<=b;
    
    if(used[pos][groups]) return state[pos][groups];
    
    used[pos][groups]=true;

    int i;
    long long sum=0;

    for(i=pos;i<=n;i++) {
        sum+=arr[i];
        if((sum&val)==sum) if(recurse(i+1,groups+1)) return state[pos][groups]=true;
    }

    return state[pos][groups]=false;
}

int recurse2(int pos) {
    if(pos>n) return 0;

    if(used2[pos]) return state2[pos];

    long long sum=0;
    int i,ans=INF;

    for(i=pos;i<=n;i++) {
        sum+=arr[i];
        if((sum&val)==sum) ans=min(ans,recurse2(i+1)+1);
    }

    used2[pos]=true;
    return state2[pos]=ans;
}

bool can(long long x) {
    int i,j;

    val=x;

    if(a==1) {
        for(i=1;i<=n;i++) {
            used2[i]=false;
        }
        return recurse2(1)<=b;
    }
    
    for(i=1;i<=n;i++) {
        for(j=0;j<=n;j++) {
            used[i][j]=false;
        }
    }

    return recurse(1,0);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i;

    scanf("%d %d %d", &n, &a, &b);
    for(i=1;i<=n;i++) {
        scanf("%lld", &arr[i]);
    }

    ans=(1ll<<41)-1;

    for(i=40;i>=0;i--) {
        if(can(ans^(1ll<<i))) {
            ans^=(1ll<<i);
        }
    }

    printf("%lld\n", ans);
    
    return 0;
}
