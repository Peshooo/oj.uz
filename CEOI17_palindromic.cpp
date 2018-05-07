#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N = 1000007;
const unsigned long long B1 = 131, B2 = 137, MOD = (1e9) + 7;

struct rolling_hash {
  unsigned long long h1,h2;

  rolling_hash(): h1(0), h2(0) {}

  void append(char a) {
    h1*=B1;
    h1+=a-'a'+1;

    h2*=B2;
    h2+=a-'a'+1;
    h2%=MOD;
  }

  bool operator ==(const rolling_hash &a) const {
    return h1==a.h1 && h2==a.h2;
  }
};

int tests,current_case;
int n;
char a[N];
unsigned long long pw1[N],pw2[N];
rolling_hash ph[N];

rolling_hash get_hash(int l, int r) {
  rolling_hash hr=ph[r],hl=ph[l-1];

  hl.h1*=pw1[r-l+1];
  hl.h2*=pw2[r-l+1];
  hl.h2%=MOD;

  hr.h1-=hl.h1;
  hr.h2-=hl.h2;
  hr.h2+=MOD;
  hr.h2%=MOD;

  return hr;
}

int go(int l, int r) {
  if(l>r) return 0;

  for(int len=1;l+len-1<=n/2;len++) {
    if(get_hash(l,l+len-1)==get_hash(r-len+1,r)) return 2+go(l+len,r-len);
  }

  return 1;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i;
  rolling_hash h;

  pw1[0]=pw2[0]=1;
  for(i=1;i<N;i++) {
    pw1[i]=pw1[i-1]*B1;
    pw2[i]=pw2[i-1]*B2%MOD;
  }

  scanf("%d", &tests);
  for(current_case=1;current_case<=tests;current_case++) {
    scanf("%s", a+1);
    n=strlen(a+1);

    h=rolling_hash();
    for(i=1;i<=n;i++) {
      h.append(a[i]);
      ph[i]=h;
    }

    printf("%d\n", go(1,n));
  }

  return 0;
}
