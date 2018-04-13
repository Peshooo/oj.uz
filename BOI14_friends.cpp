#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
 
const int N = 1<<21;
const unsigned long long B1 = 139, B2 = 137, MOD = (1e9) + 696969;
 
struct rolling_hash {
    unsigned long long h1,h2;
    void initialize() {
        h1=0;
        h2=0;
    }
    void append(char a) {
        h1*=B1;h1+=a-'A'+1;h1%=MOD;
        h2*=B2;h2+=a-'A'+1;h2%=MOD;
    }
    bool operator ==(const rolling_hash &a) const {
        return h1==a.h1 && h2==a.h2;
    }
    bool operator <(const rolling_hash &a) const {
        return ((h1==a.h1) ? h2<a.h2 : h1<a.h2);
    }
};
 
int tests,current_case;
int n;
unsigned long long pw1[N],pw2[N];
rolling_hash ph[N];
int ans[N],sz;
rolling_hash h1,h2;
char a[N];
rolling_hash h;
int cnt;
set < rolling_hash > s;
 
void message(int current_case) {
    //cerr<<"Case "<<current_case<<" solved!"<<endl;
    fprintf(stderr, "Case %d solved!\n", current_case);
}
 
rolling_hash merge_hashes(rolling_hash a, rolling_hash b, int length) {
    a.h1*=pw1[length];
    a.h1+=b.h1;
    a.h1%=MOD;
    a.h2*=pw2[length];
    a.h2+=b.h2;
    a.h2%=MOD;
    return a;
}
 
rolling_hash get_hash(int l, int r) {
    rolling_hash hl=ph[l-1],hr=ph[r];
    hl.h1*=pw1[r-l+1];
    hl.h1%=MOD;
    hl.h2*=pw2[r-l+1];
    hl.h2%=MOD;
    hr.h1-=hl.h1;
    hr.h1+=MOD;
    hr.h1%=MOD;
    hr.h2-=hl.h2;
    hr.h2+=MOD;
    hr.h2%=MOD;
    return hr;
}
 
int main() {
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    int i;
 
    pw1[0]=1;
    pw2[0]=1;
    for(i=1;i<N;i++) pw1[i]=pw1[i-1]*B1%MOD,pw2[i]=pw2[i-1]*B2%MOD;
 
    tests=1;
    //scanf("%d", &tests);
    //cin>>tests;
    for(current_case=1;current_case<=tests;current_case++) {
        s.clear();
        scanf("%d", &n);
        scanf("%s", a+1);
        h.initialize();
        ph[0]=h;
        for(i=1;i<=n;i++) h.append(a[i]),ph[i]=h;
        if(!(n&1)){
            printf("NOT POSSIBLE\n");
            goto MESSAGE;
        }
        sz=0;
        for(i=1;i<=n;i++) {
            if(i>n/2) h1=get_hash(1,n/2);
            else h1=merge_hashes(get_hash(1,i-1),get_hash(i+1,n/2+1),n/2+1-(i+1)+1);
            if(i<n-n/2+1) h2=get_hash(n-n/2+1,n);
            else h2=merge_hashes(get_hash(n-n/2,i-1),get_hash(i+1,n),n-i);
            if(h1==h2) ans[++sz]=i,s.insert(h1);
        }
        sz=(int)(s.size());
        if(sz==0) {
            printf("NOT POSSIBLE\n");
            goto MESSAGE;
        }
        else if(sz>1) {
            printf("NOT UNIQUE\n");
            goto MESSAGE;
        }
        cnt=0;
        for(i=1;cnt<n/2;i++) {
            if(i==ans[1]) continue;
            ++cnt;
            printf("%c", a[i]);
        }
        printf("\n");
 
        MESSAGE:
        message(current_case);
    }
 
    return 0;
}
