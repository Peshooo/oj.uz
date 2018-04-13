#include <bits/stdc++.h>
 
using namespace std;
 
const int N = 1<<17;
const int TREE_SIZE = N<<2;
const int INF = (1e9) + 7;
 
struct tree_node {
    int min,max,sum;
    tree_node() {
        min=0;
        max=0;
        sum=0;
    }
};
 
int n;
tree_node tree[TREE_SIZE];
tree_node q;
 
tree_node merge_them(tree_node a, tree_node b) {
    tree_node ans;
    ans.sum=a.sum+b.sum;
    ans.min=min(b.min,b.sum+a.min);
    ans.max=max(b.max,b.sum+a.max);
    return ans;
}
 
void update_tree(int a, int b, int pos, int node, int value) {
    if(a>b || a>pos || b<pos) return;
    if(a==b) {
        tree[node].sum+=value;
        tree[node].min=tree[node].max=tree[node].sum;
        return;
    }
    update_tree(a,(a+b)>>1,pos,node<<1,value);
    update_tree(((a+b)>>1)+1,b,pos,(node<<1)|1,value);
    tree[node]=merge_them(tree[node<<1],tree[(node<<1)|1]);
}
 
int main() {
    int i,x,y;
 
    scanf("%d", &n);
    for(i=1;i<=n;i++) {
        scanf("%d %d", &x, &y);
        if(y==1) update_tree(1,n,x,1,1);
        else update_tree(1,n,x,1,-1);
        q=tree[1];
        if(q.min>=0 && q.max>0) printf(">\n");
        else if(q.min<0 && q.max<=0) printf("<\n");
        else printf("?\n");
    }
 
    return 0;
}
