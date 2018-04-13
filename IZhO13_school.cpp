#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
 
const int N = 300007;
 
int n,m,s;
pair < int, int > a[N];
long long curr,ans;
 
bool cmp(pair < int, int > a, pair < int, int > b) {
    return a.first==b.first ? a.second>b.second : a.first<b.first;
}
 
struct cmpm {
    bool operator () (const int &x, const int &y) const {
        return a[x].second-a[x].first==a[y].second-a[y].first ? x<y : a[x].second-a[x].first>a[y].second-a[y].first;
    }
};
 
struct cmps {
    bool operator () (const int &x, const int &y) const {
        return a[x].second==a[y].second ? x<y : a[x].second<a[y].second;
    }
};
 
set < int, cmpm > setm;
set < int, cmps > sets;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i;
 
    scanf("%d %d %d", &n, &m, &s);
    for(i=1;i<=n;i++) {
        scanf("%d %d", &a[i].first, &a[i].second);
    }
    sort(a+1,a+1+n);
   
    for(i=n;i>=n-m+1;i--) {
        setm.insert(i);
        curr+=a[i].first;
    }
 
    for(i=1;i<n-m+1;i++) {
        sets.insert(i);
        curr+=a[i].second;
    }
 
    while((int)sets.size()>s) {
        curr-=a[*sets.begin()].second;
        sets.erase(sets.begin());
    }
 
    ans=curr;
 
    for(i=n-m;i>=1;i--) {
        if(sets.find(i)!=sets.end()) {
            curr-=a[i].second;
            sets.erase(i);
        }
        setm.insert(i);
        curr+=a[i].first;
 
        while((int)setm.size()>m) {
            curr-=a[*setm.begin()].first;
            curr+=a[*setm.begin()].second;
            sets.insert(*setm.begin());
            setm.erase(setm.begin());
        }
 
        while((int)sets.size()>s) {
            curr-=a[*sets.begin()].second;
            sets.erase(sets.begin());
        }
 
        ans=max(ans,curr);
    }
 
    printf("%lld\n", ans);
    
    return 0;
}
