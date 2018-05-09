#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N = 10007;
const int MOD = (1e6) + 7;

int n,a[N],pos,cnt;
int dp[2][N];
int state_cnt[N],state_coef[N];
long long ans;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i;

  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &a[i]);
  }

  ans=1;

  cnt=1;
  for(pos=2;pos<=n;pos++) {
    if(a[pos]>cnt) {
      state_cnt[pos]=cnt;
      state_coef[pos]=cnt;
      
      ++cnt;
    }
    else {
      state_cnt[pos]=cnt;
      state_coef[pos]=a[pos]-1;
    }
  }

  for(cnt=0;cnt<=n;cnt++) {
    dp[(n+1)&1][cnt]=1;
  }
  for(pos=n;pos>=2;pos--) {
    ans+=dp[(pos+1)&1][state_cnt[pos]]*1ll*state_coef[pos]%MOD;
    for(cnt=1;cnt<pos;cnt++) {
      dp[pos&1][cnt]=(dp[(pos+1)&1][cnt+1]+dp[(pos+1)&1][cnt]*1ll*cnt)%MOD;
    }
  }
  
  ans%=MOD;
  printf("%lld\n", ans);

  return 0;
}
