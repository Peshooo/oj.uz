#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N = 44;

int n,n2;
long long ans,m,a[N];
vector < long long > v;

void recurse1(int pos, long long sum) {
  if(pos>n2) {
    v.push_back(sum);
    return;
  }

  recurse1(pos+1,sum);
  recurse1(pos+1,sum+a[pos]);
}

void recurse2(int pos, long long sum) {
  if(pos>n) {
    ans+=(int)(upper_bound(v.begin(),v.end(),m-sum)-v.begin());
    return;
  }

  recurse2(pos+1,sum);
  recurse2(pos+1,sum+a[pos]);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i;

  scanf("%d %lld", &n, &m);
  for(i=1;i<=n;i++) {
    scanf("%lld", &a[i]);
  }

  n2=n/2;

  recurse1(1,0);
  sort(v.begin(),v.end());
  recurse2(n2+1,0);

  printf("%lld\n", ans);

  return 0;
}
