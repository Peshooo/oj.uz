#include <bits/stdc++.h>
#include "network.h"
 
#define endl '\n'
 
using namespace std;
 
const int N = 1024;
 
int n,a,b;
int da[N],db[N];
int min_dist;
int shortest,path[N],path_sz;
bool used[N];
vector < int > v[N];
 
/*void travelTo(int x) {
}
 
int ping(int a, int b) {
    
}*/
 
int ask(int a, int b) {
    if(a==b) return 0;
    return 1+ping(a,b);
}
 
bool cmp(int a, int b) {
    return da[a]<da[b];
}
 
void findRoute(int N, int A, int B) {
    int i,j;
    
    n=N;
    a=A;
    b=B;
 
    shortest=ask(a,b);
    da[a]=0;
    da[b]=shortest;
    db[a]=shortest;
    db[b]=0;
    path_sz=0;
 
    for(i=0;i<=n;i++) v[i].clear();
 
    for(i=1;i<=n;i++) if(i!=a && i!=b) {
        db[i]=ask(i,b);
        v[db[i]].push_back(i);
    }
 
    int where=a;
    for(j=shortest-1;j>=1;j--) {
        for(i=0;i<(int)(v[j].size());i++) {
            int curr=v[j][i];
            da[curr]=ask(curr,where);
            if(da[curr]==1) {
                travelTo(curr);
                where=curr;
                break;
            }
        }
    }
    travelTo(b);
}
 
/*int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
 
 
    return 0;
}*/
