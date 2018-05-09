#include <bits/stdc++.h>
#define endl '\n'
#define time akghahgahgkahjgaj

using namespace std;

const int N = 100007;

struct dsu {
  int n,parents[N];

  void initialize(int k) {
    n=k;
    for(int i=1;i<=n;i++) {
      parents[i]=i;
    }
  }

  int find(int x) {
    while(x!=parents[x]) {
      parents[x]=parents[parents[x]];
      x=parents[x];
    }
    return x;
  }
} uf1, uf2;

int n,m;
int time[N],low[N],current_time;
vector < int > v[N];

void dfs(int node, int from=-1) {
  low[node]=time[node]=++current_time;

  int i;

  for(i=0;i<(int)(v[node].size());i++) if(v[node][i]!=from) {
    if(time[v[node][i]]==0) {
      dfs(v[node][i],node);
      if(low[v[node][i]]>time[node]) if(uf2.find(node)!=uf2.find(v[node][i])) {
        printf("%d %d\n", node, v[node][i]);
      }
      low[node]=min(low[node],low[v[node][i]]);
    }
    else {
      low[node]=min(low[node],time[v[node][i]]);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i,x,y,fx,fy;

  scanf("%d %d", &n, &m);

  uf1.initialize(n);
  uf2.initialize(n);

  for(i=1;i<=m;i++) {
    scanf("%d %d", &x, &y);

    fx=uf1.find(x);
    fy=uf1.find(y);

    if(fx!=fy) {
      uf1.parents[fx]=fy;
      v[x].push_back(y);
      v[y].push_back(x);
    }
    else {
      fx=uf2.find(x);
      fy=uf2.find(y);

      if(fx!=fy) {
        uf2.parents[fx]=fy;
        v[x].push_back(y);
        v[y].push_back(x);
      }
    }
  }

  for(i=1;i<=n;i++) if(time[i]==0) {
    dfs(i);
  }

  return 0;
}
