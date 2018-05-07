#include <bits/stdc++.h>
#define endl '\n'
#define time lkahgkljahkgjkghajahkjg

using namespace std;

const int N = 100007;
const int LOG = 17;

struct edge {
  int to,idx,from_which,to_which;
  
  edge(){}
  edge(int a, int b, int c, int d): to(a), idx(b), from_which(c), to_which(d) {}
};

int n,m;
pair < int, int > e[N];
vector < pair < int, int > > v[N];
vector < edge > k[N];
bool is_bridge[N];
int parent[N],time[N],current_time,low[N];
bool used[N];
int comp[N];
int components_count;
int level[N],jump[N][LOG];
int cntu[N],cntd[N];
int p;
char answer[N];

void dfs1(int node) {
  used[node]=true;
  low[node]=time[node]=++current_time;
  
  int i;

  for(i=0;i<(int)(v[node].size());i++) if(v[node][i].first!=parent[node]) {
    if(!used[v[node][i].first]) {
      parent[v[node][i].first]=node;
      dfs1(v[node][i].first);
      if(low[v[node][i].first]>time[node]) is_bridge[v[node][i].second]=true;
      low[node]=min(low[node],low[v[node][i].first]);
    }
    else {
      low[node]=min(low[node],time[v[node][i].first]);
    }
  }
}

void dfs2(int node, int where) {
  used[node]=true;
  comp[node]=where;

  int i;

  for(i=0;i<(int)(v[node].size());i++) if(!used[v[node][i].first] && !is_bridge[v[node][i].second]) {
    dfs2(v[node][i].first,where);
  }
}

void dfs3(int node) {
  used[node]=true;

  int i;

  for(i=0;i<(int)(k[node].size());i++) if(!used[k[node][i].to]) {
    parent[k[node][i].to]=node;
    level[k[node][i].to]=level[node]+1;
    dfs3(k[node][i].to);
  }
}

void walk_up(int &node, int lvl) {
  for(int i=16;level[node]>lvl;i--) if(level[jump[node][i]]>=lvl) node=jump[node][i];
}

int get_lca(int a, int b) {
  walk_up(a,level[b]);
  walk_up(b,level[a]);

  if(a==b) return a;

  for(int i=16;i>=0;i--) if(jump[a][i]!=jump[b][i]) {
    a=jump[a][i];
    b=jump[b][i];
  }

  return parent[a];
}

void dfs4(int node) {
  used[node]=true;

  int i,to,idx;

  for(i=0;i<(int)(k[node].size());i++) {
    to=k[node][i].to;
    idx=k[node][i].idx;

    if(used[to]) continue;

    dfs4(to);

    cntu[node]+=cntu[to];
    cntd[node]+=cntd[to];

    if(cntu[to]) {
      if(e[idx]==make_pair(k[node][i].to_which,k[node][i].from_which)) {
        answer[idx]='R';
      }
      else {
        answer[idx]='L';
      }
    }
    else if(cntd[to]) {
      if(e[idx]==make_pair(k[node][i].from_which,k[node][i].to_which)) {
        answer[idx]='R';
      }
      else {
        answer[idx]='L';
      }
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i,j,x,y,lca;

  scanf("%d %d", &n, &m);
  for(i=1;i<=m;i++) {
    scanf("%d %d", &e[i].first, &e[i].second);
    v[e[i].first].push_back(make_pair(e[i].second,i));
    v[e[i].second].push_back(make_pair(e[i].first,i));
    answer[i]='B';
  }

  for(i=1;i<=n;i++) if(!used[i]) {
    dfs1(i);
  }

  fill(used+1,used+1+n,false);
  for(i=1;i<=n;i++) if(!used[i]) {
    dfs2(i,++components_count);
  }

  for(i=1;i<=m;i++) {
    if(is_bridge[i]) {
      k[comp[e[i].first]].push_back(edge(comp[e[i].second],i,e[i].first,e[i].second));
      k[comp[e[i].second]].push_back(edge(comp[e[i].first],i,e[i].second,e[i].first));
    }
  }

  fill(used+1,used+1+n,false);
  for(i=1;i<=n;i++) if(!used[i]) {
    parent[i]=0;
    level[i]=1;
    dfs3(i);
  }

  for(i=1;i<=n;i++) {
    jump[i][0]=parent[i];
  }
  for(j=1;j<17;j++) {
    for(i=1;i<=n;i++) {
      jump[i][j]=jump[jump[i][j-1]][j-1];
    }
  }

  scanf("%d", &p);
  for(i=1;i<=p;i++) {
    scanf("%d %d", &x, &y);
    
    if(comp[x]==comp[y]) continue;

    lca=get_lca(comp[x],comp[y]);

    ++cntu[comp[x]];
    ++cntd[comp[y]];
    --cntu[lca];
    --cntd[lca];
  }

  fill(used+1,used+1+n,false);
  for(i=1;i<=components_count;i++) if(!used[i]) {
    dfs4(i);
  }

  for(i=1;i<=m;i++) {
    printf("%c", answer[i]);
  }

  printf("\n");

  return 0;
}
