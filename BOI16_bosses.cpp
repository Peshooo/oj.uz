#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
 
const int N = 5007;
 
int n,ans;
vector < int > v[N];
bool used[N];
int level[N];
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i;
 
    scanf("%d", &n);
    for(i=1;i<=n;i++) {
        int x;
        scanf("%d", &x);
        while(x--) {
            int y;
            scanf("%d", &y);
            v[y].push_back(i);
        }
    }
 
    ans=numeric_limits < int >::max();
 
    for(int root=1;root<=n;root++) {
        int cnt=0,curr=0;
        queue < int > q;
 
        memset(used,0,sizeof(used));
        used[root]=true;
        level[root]=1;
        q.push(root);
        
        while(!q.empty()) {
            int where=q.front();
            q.pop();
 
            ++cnt;
            curr+=level[where];
 
            for(i=0;i<(int)(v[where].size());i++) {
                if(!used[v[where][i]]) {
                    used[v[where][i]]=true;
                    level[v[where][i]]=level[where]+1;
                    q.push(v[where][i]);
                }
            }
        }
 
        if(cnt==n) ans=min(ans,curr);
    }
 
    printf("%d\n", ans);
 
    return 0;
}
