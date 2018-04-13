#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1<<19;
 
int n;
pair < int, int > a[N];
long long ans;
map < int, int > cntx,cnty;
 
int main() {
    int i;
 
    scanf("%d", &n);
    for(i=1;i<=n;i++) {
        scanf("%d %d", &a[i].first, &a[i].second);
        ++cntx[a[i].first];
        ++cnty[a[i].second];
    }
    for(i=1;i<=n;i++) {
        ans+=(cntx[a[i].first]-1)*(cnty[a[i].second]-1);
    }
    printf("%lld\n", ans);
 
    return 0;
}
