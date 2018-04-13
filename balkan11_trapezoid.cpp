#include <bits/stdc++.h>
#define endl '\n'
 
#define left aklhgjqghkqkj
#define right ajklvhajkvhajk
#define prev aioghajga
#define next ioyhjhfajasj
#define y0 iuadoghasdgj
#define y1 taklahgjkla
#define remainder pogjuakllhga
#define pow pajklgaklha
#define pow10 iopuioadjlgkah
#define div aljghajkghak
#define distance gkuftgjasgfjh
#define uppercase ifyhasjkhakjfas
#define tm aogqjgklqjgqklgjqlkq
 
//#define floor hjakjhaja
//#define time ashjlahjka
//#define double_t double
 
using namespace std;
 
const int N = 400007;
const int MOD = 30013;
 
struct item {
    int value,cnt;
    item(): value(0), cnt(1) {}
};
 
struct coordinate {
    int where,idx,type;
    bool operator <(const coordinate &a) const {
        return where<a.where;
    }
};
 
struct trapezoid {
    int a,b,c,d;
};
 
int n;
trapezoid a[N];
coordinate arr[N];
int p[N],sz,arr_sz;
map < int, int > code;
item ans;
item dp[N],it[N];
int all;
 
item merge(item a, item b) {
    if(a.value>b.value) return a;
    if(a.value<b.value) return b;
    if(a.value>0) {
        a.cnt+=b.cnt;
        a.cnt%=MOD;
    }
    return a;
}
 
void update(int pos, item value) {
    for(;pos<=all;pos+=pos&(-pos)) {
        it[pos]=merge(it[pos],value);
    }
}
 
item query(int pos) {
    item ans;
    for(;pos>=1;pos-=pos&(-pos)) {
        ans=merge(ans,it[pos]);
    }
    return ans;
}
 
void add(int where, int type, int idx) {
    ++arr_sz;
    arr[arr_sz].where=where;
    arr[arr_sz].idx=idx;
    arr[arr_sz].type=type;
}
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int i;
 
    scanf("%d", &n);
    for(i=1;i<=n;i++) {
        scanf("%d %d %d %d", &a[i].a, &a[i].b, &a[i].c, &a[i].d);
        
        p[++sz]=a[i].a;
        p[++sz]=a[i].b;
        p[++sz]=a[i].c;
        p[++sz]=a[i].d;
    }
 
    sort(p+1,p+1+sz);
    code[p[1]]=1;
    for(i=2;i<=sz;i++) {
        if(p[i]!=p[i-1]) {
            code[p[i]]=code[p[i-1]]+1;
        }
    }
    all=code[p[sz]];
    
    for(i=1;i<=n;i++) {
        a[i].a=code[a[i].a];
        a[i].b=code[a[i].b];
        a[i].c=code[a[i].c];
        a[i].d=code[a[i].d];
        
        add(a[i].a,0,i);
        add(a[i].b,1,i);
    }
 
    sort(arr+1,arr+1+arr_sz);
 
    for(i=1;i<=arr_sz;i++) {
        if(arr[i].type==0) { //It's of type A
            dp[arr[i].idx]=query(a[arr[i].idx].c-1);
            dp[arr[i].idx].value+=1;
            ans=merge(ans,dp[arr[i].idx]);
        }
        else if(arr[i].type==1) { //It's of type B
            update(a[arr[i].idx].d,dp[arr[i].idx]);
        }
    }
 
    printf("%d %d\n", ans.value, ans.cnt);
 
    return 0;
}
