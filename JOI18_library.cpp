#include <bits/stdc++.h>
#include "library.h"
#ifdef skeleta
    #include "grader.cpp"
#endif

using namespace std;

const int MAXN = 1007;

int n;
vector < int > qry;
int edges_count;
vector < int > v[MAXN];
bool used[MAXN];
vector < pair < int, int > > edges;

int count_them(int l, int r) {
    int i,ans=0;

    for(i=0;i<(int)(edges.size());i++) {
        if(l<=edges[i].first && edges[i].second<=r) {
            ++ans;
        }
    }

    return ans;
}

int ask(int l, int r) { //Returns the number of new connections among books with numbers l, l+1, ..., r
    int i;
    
    for(i=0;i<n;i++) qry[i]=0;
    for(i=l;i<=r;i++) qry[i-1]=1;
    return r-l+1-Query(qry)-count_them(l,r);
}

void add_edge(int x, int y) {
    ++edges_count;
    edges.push_back(make_pair(min(x,y),max(x,y)));
    v[x].push_back(y);
    v[y].push_back(x);
}

void return_answer() {
    int i;
    vector < int > ans;
    queue < int > q;

    for(i=1;i<=n;i++) if(v[i].size()==1) {
        used[i]=true;
        q.push(i);
        break;
    }

    while(!q.empty()) {
        int curr=q.front();
        q.pop();
        ans.push_back(curr);

        for(i=0;i<(int)(v[curr].size());i++) if(!used[v[curr][i]]) {
            used[v[curr][i]]=true;
            q.push(v[curr][i]);
        }
    }

    Answer(ans);
}

void Solve(int NN) {
    int i,last=0;
    n=NN;

    if(n==1) {
        vector < int > ans = { 1 };
        Answer(ans);
        return;
    }

    qry.assign(n,0);

    while(edges_count<n-1) {
        int qans,left=last,right=n,middle;
        
        while(right-left>1) {
            middle=(left+right)>>1;
            qans=ask(1,middle);
            if(qans>0) right=middle;
            else left=middle;
        }

        last=right;
        
        left=1;
        right=last;

        while(right-left>1) {
            middle=(left+right)>>1;
            qans=ask(middle,last);
            if(qans>0) left=middle;
            else right=middle;
        }

        add_edge(left,last);

        --last;
    }

    return_answer();
}
