#include <bits/stdc++.h>
 
using namespace std;
 
long long a,b;
bool used[22][2][10][10][2][2];
long long state[22][2][10][10][2][2];
int d[22],cnt;
 
int get_digits(long long n) {
    cnt=0;
    while(n) d[cnt++]=n%10,n/=10;
    reverse(d,d+cnt);
}
 
long long recurse(int pos, int f, int before_last, int last, int has_before_last, int has_last) {
    if(pos==cnt) return has_last;
    if(used[pos][f][before_last][last][has_before_last][has_last]) return state[pos][f][before_last][last][has_before_last][has_last];
    long long ans=0;
    int i;
    for(i=0;i<10;i++) {
        if(f || i<=d[pos]) if(!has_last || last!=i) if(!has_before_last || before_last!=i) {
            ans+=recurse(pos+1,f|(i<d[pos]),last,i,has_last,has_last|(i>0));
        }
    }
    used[pos][f][before_last][last][has_before_last][has_last]=true;
    state[pos][f][before_last][last][has_before_last][has_last]=ans;
    return ans;
}
 
long long f(long long n) {
    get_digits(n);
    memset(used,0,sizeof(used));
    return 1+recurse(0,0,0,0,0,0);
}
 
int main() {
    scanf("%lld %lld", &a, &b);
    printf("%lld\n", f(b)-((a==0) ? 0 : f(a-1)));
}
