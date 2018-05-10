#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

const int N = 100007;

int n;
char a[N],ans[N];
int pos[N];

bool can(int l, int r) {
  stack < char > s;
  int i;

  for(i=l;i<=r;i++) {
    if(!s.empty() && s.top()==a[i]) s.pop();
    else s.push(a[i]);
  }

  return s.empty();
}

void solve(int l, int r) {
  if(l>r) return;
  if(a[l]==a[r]) {
    ans[l]='(';
    ans[r]=')';
    solve(l+1,r-1);
    return;
  }
  
  int where=pos[r];

  while(a[l]!=a[where-1]) {
    where=pos[where-1];
  }

  assert(where>l);
  
  if(l<where-1) {
    ans[l]='(';
    ans[where-1]=')';
  }

  solve(l+1,where-2);
  solve(where,r);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i,where;

  scanf("%s", a+1);
  n=strlen(a+1);

  if(!can(1,n)) {
    printf("-1\n");
    return 0;
  }

  pos[1]=0;
  for(i=2;i<=n;i++) {
    where=i-1;
    while(where>0 && a[where]!=a[i]) where=pos[where]-1;
    pos[i]=max(where,0);
  }

  solve(1,n);
  for(i=1;i<=n;i++) {
    printf("%c", ans[i]);
  }
  printf("\n");

  return 0;
}
