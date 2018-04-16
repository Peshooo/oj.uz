
#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
 
const int N = 100002;
const int K = 202;
 
struct convex_hull_trick {
    struct line {
        long long a, b;
        int idx;
 
        line(){}
        line(long long x, long long y, int z): a(x), b(y), idx(z) {}
        
        template < class T >
        T eval(T x) {
            return a*x+b;
        }
    };
 
    deque < line > v;

    void clear() {
        v.clear();
    }
 
    double crossx(line l1, line l2) {
        double x=(double)(l2.b-l1.b)/(double)(l1.a-l2.a);
        return x;
    }
 
    double crossy(line l1, line l2) {
        double x=(double)(l2.b-l1.b)/(double)(l1.a-l2.a);
        return l1.eval(x);
    }
 
    void add_line(long long a, long long b, int idx) {
        line l(a,b,idx);
 
        while(v.size()>=2 && crossy(l,v[v.size()-2])>=crossy(v[v.size()-1],v[v.size()-2])) {
            v.pop_back();
        }
 
        v.push_back(l);
    }
 
    long long get(long long x, int &idx) {
        if(v.empty()) return numeric_limits < long long >::min();
 
        long long ans=v[0].eval(x),curr;
        idx=v[0].idx;

        while(v.size()>=2 && (curr=v[1].eval(x))>=ans) {
            v.pop_front();
            ans=curr;
            idx=v[0].idx;
        }

        return ans;
    }
};
 
int n,k,a[N],s[N],all_s;
long long dp[2][K];
int best[N][K];
convex_hull_trick cht[K];
vector < int > path;
 
void restore(int pos, int groups) {
    if(groups==1) return;
    path.push_back(best[pos][groups]-1);
    restore(best[pos][groups],groups-1);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i,j;
 
    scanf("%d %d", &n, &k);
    for(i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        s[i]=a[i]+s[i-1];
    }
 
    all_s=s[n];
 
    for(i=n;i>=1;i--) {
        for(j=min(k+1,n-i+1);j>1;j--) {
            dp[i&1][j]=cht[j-1].get(s[i-1],best[i][j])-s[i-1]*1ll*all_s-s[i-1]*1ll*s[i-1];
            cht[j].add_line(2*s[i-1],s[i-1]*1ll*all_s-s[i-1]*1ll*s[i-1]+dp[i&1][j],i);
        }
 
        dp[i&1][1]=(s[n]-s[i-1])*1ll*(all_s-s[n]+s[i-1]);
        cht[1].add_line(2*s[i-1],s[i-1]*1ll*all_s-s[i-1]*1ll*s[i-1]+dp[i&1][1],i);
    }
 
    printf("%lld\n", dp[1][k+1]/2);
    restore(1,k+1);
    for(i=0;i<(int)(path.size());i++) {
        if(i>0) printf(" ");
        printf("%d", path[i]);
    }
    printf("\n");
 
    return 0;
}
