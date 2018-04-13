#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
 
const int N = 1<<18;
const long long INF = 1000000000000000007;
 
struct edge {
    int to,w;
    edge(){}
    edge(int a, int b) {
        to=a;
        w=b;
    }
};
 
struct el {
    int vertex;
    long long cost;
    el(){}
    el(int a, long long b) {
        vertex=a;
        cost=b;
    }
    bool operator <(const el &a) const {
        return cost>a.cost;
    }
};
 
int n,k,m,important[8];
vector < edge > v[N];
long long int dist[1<<5][N];
char buff[(1<<24) + 7],*buffp=buff;
bool used[N];
 
void read(int &res) {
    res=0;
    while(*buffp<48) ++buffp;
    while(*buffp>47) res=(res<<3)+(res<<1)+*buffp++-48;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fread(buff,1,sizeof(buff),stdin);
    int x,y,z;
    int j; int i;
 
    read(n);
    read(k);
    read(m);
    for(i=1;i<=k;i++) {
        read(important[i]);
    }
 
    for(i=1;i<=m;i++) {
        read(x);
        read(y);
        read(z);
        v[x].push_back(edge(y,z));
        v[y].push_back(edge(x,z));
    }
 
    for(i=0;i<(1<<k);i++) for(j=1;j<=n;j++) dist[i][j]=INF;
 
    for(i=0;i<k;i++) {
        dist[1<<i][important[i+1]]=0;
    }
 
    for(i=1;i<=n;i++) {
        dist[0][i]=0;
    }
 
    for(int mask=1;mask<(1<<k);mask++) {
        priority_queue < el > q;
 
        for(int submask1=0;submask1<mask;submask1++) if((mask|submask1)==mask) {
            int submask2=(mask^submask1);
            if(submask2>submask1) continue;
            for(i=1;i<=n;i++) {
                long long current_distance=dist[submask1][i]+dist[submask2][i];
                if(current_distance<dist[mask][i]) {
                    dist[mask][i]=current_distance;
                }
            }
        }
 
        for(i=1;i<=n;i++) if(dist[mask][i]!=INF) q.push(el(i,dist[mask][i]));
 
        fill(used+1,used+1+n,false);
 
        while(!q.empty()) {
            el curr=q.top();
            q.pop();
 
            if(used[curr.vertex]) continue;
            used[curr.vertex]=true;
            
            for(i=0;i<(int)(v[curr.vertex].size());i++) {
                long long current_distance=v[curr.vertex][i].w+curr.cost;
                if(current_distance<dist[mask][v[curr.vertex][i].to]) {
                    dist[mask][v[curr.vertex][i].to]=current_distance;
                    q.push(el(v[curr.vertex][i].to,current_distance));
                }
            }
        }
    }
 
    long long ans=INF;
    for(i=1;i<=n;i++) {
        ans=min(ans,dist[(1<<k)-1][i]);
    }
 
    printf("%lld\n", ans);
 
    return 0;
}
