#include <bits/stdc++.h>
#define endl '\n'
#define prev alkhjgajghgkjagjhk

using namespace std;

const int N = 1007;

int n,m;
bool has[N][N];
vector < int > v[N];
vector < int > comp;
bool used[N];
int dist[N],prev[N];

void dfs(int node, int chosen) {
  used[node]=true;

  if(has[node][chosen]) {
    comp.push_back(node);
    return;
  }

  for(int i=0;i<(int)(v[node].size());i++) if(!used[v[node][i]]) {
    dfs(v[node][i],chosen);
  }
}

void restore(int from, int to, int chosen) {
  int i,curr;
  queue < int > q;

  for(i=1;i<=n;i++) {
    used[i]=false;
  }

  used[from]=true;
  dist[from]=0;
  q.push(from);

  while(!q.empty()) {
    curr=q.front();
    q.pop();

    for(i=0;i<(int)(v[curr].size());i++) if(!used[v[curr][i]] && (v[curr][i]==to || !has[v[curr][i]][chosen])) {
      used[v[curr][i]]=true;
      dist[v[curr][i]]=dist[curr]+1;
      prev[v[curr][i]]=curr;
      q.push(v[curr][i]);
    }
  }

  curr=to;
  while(curr) {
    printf("%d ", curr);
    curr=prev[curr];
  }

  printf("%d\n", chosen);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i,j,z,t,x,y;

  scanf("%d %d", &n, &m);
  for(i=1;i<=m;i++) {
    scanf("%d %d", &x, &y);
    has[x][y]=true;
    has[y][x]=true;
    v[x].push_back(y);
    v[y].push_back(x);
  }

  for(i=1;i<=n;i++) {
    has[i][i]=true;

    for(j=1;j<=n;j++) {
      used[j]=false;
    }

    for(j=1;j<=n;j++) if(!used[j] && i!=j && !has[i][j]) {
      comp.clear();
      
      dfs(j,i);
      
      for(z=0;z<(int)(comp.size());z++) for(t=z+1;t<(int)(comp.size());t++) {
        if(!has[comp[z]][comp[t]]) {
          restore(comp[z],comp[t],i);
          return 0;
        }
      }
    }
  }

  printf("no\n");

  return 0;
}
