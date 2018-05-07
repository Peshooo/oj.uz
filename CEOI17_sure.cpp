#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N = 100007;

int n;
double a[N],b[N],ans;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i,j;

  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%lf %lf", &a[i], &b[i]);
  }

  sort(a+1,a+1+n);
  reverse(a+1,a+1+n);

  sort(b+1,b+1+n);
  reverse(b+1,b+1+n);

  for(i=1;i<=n;i++) {
    a[i]+=a[i-1];
    b[i]+=b[i-1];
  }

  ans=0.0;

  for(i=1;i<=n;i++) {
    j=(int)(lower_bound(b+1,b+1+n,a[i])-b);
    if(j>=1 && j<=n) ans=max(ans,min(a[i],b[j])-i-j);
  
    j=(int)(lower_bound(a+1,a+1+n,b[i])-a);
    if(j>=1 && j<=n) ans=max(ans,min(a[j],b[i])-i-j);
  }

  printf("%.4lf\n", ans);

  return 0;
}
