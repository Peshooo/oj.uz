#include <bits/stdc++.h>
#define endl '\n'
 
using namespace std;
 
const int N = 100007;
const double EPS = 0.0000001;

struct dynamic_convex_hull_trick {
  struct line {
    long long a,b;
    
    line(){}
    line(long long x, long long y): a(x), b(y) {}
 
    bool operator <(const line &x) const {
      return a==x.a ? b<x.b : a<x.a;
    }
  };
 
  struct cross_t {
    double x;
    line l;

    cross_t(){}
    cross_t(double a, line b): x(a), l(b) {}

    bool operator <(const cross_t &a) const {
      return fabs(x-a.x)<=EPS ? false : x<a.x;
    }
  };

  set < line > s;
  set < cross_t > cross_set;

  long long eval(line l, long long x) {
    return l.a*x+l.b;
  }
 
  double cross_x(line l1, line l2) {
    return (double)(l2.b-l1.b)/(double)(l1.a-l2.a);
  }

  void erase_line(set < line >::iterator it) {
    if(it!=s.begin()) {
      cross_set.erase(cross_t(cross_x(*it,*prev(it)),*it));
    }
    if(next(it)!=s.end()) {
      cross_set.erase(cross_t(cross_x(*next(it),*it),*next(it)));
    }
    if(it!=s.begin() && next(it)!=s.end()) {
      cross_set.insert(cross_t(cross_x(*next(it),*prev(it)),*next(it)));
    }
    s.erase(it);
  }

  void erase_line2(set < line >::iterator it) {
    if(prev(it)!=s.begin()) {
      cross_set.erase(cross_t(cross_x(*it,*prev(prev(it))),*it));
    }
    if(next(it)!=s.end()) {
      cross_set.erase(cross_t(cross_x(*next(it),*it),*next(it)));
    }
    if(prev(it)!=s.begin() && next(it)!=s.end()) {
      cross_set.insert(cross_t(cross_x(*next(it),*prev(prev(it))),*next(it)));
    }
    s.erase(it);
  }

  void insert_line(set < line >::iterator it) {
    if(it!=s.begin() && next(it)!=s.end()) {
      cross_set.erase(cross_t(cross_x(*next(it),*prev(it)),*next(it)));
    }
    if(it!=s.begin()) {
      cross_set.insert(cross_t(cross_x(*it,*prev(it)),*it));
    }
    if(next(it)!=s.end()) {
      cross_set.insert(cross_t(cross_x(*next(it),*it),*next(it)));
    }
  }

  void add_line(line l) {
    if(s.find(l)!=s.end()) return;
 
    set < line >::iterator it=s.insert(l).first,it1,it2;

    if(it!=s.begin()) {
      it1=prev(it);
      if(it1->a==it->a) {
        s.erase(it);
        return;
      }
    }

    if(it!=s.end()) {
      it2=next(it);
      if(it->a==it2->a) {
        erase_line2(it2);
      }
    }

    insert_line(it);

    if(it!=s.begin() && it!=s.end()) {
      it1=prev(it);
      it2=next(it);
 
      if(it2!=s.end()) {
        if(cross_x(*it2,*it1)>=cross_x(*it,*it1)) {
          erase_line(it);
          return;
        }
      }
    }
 
    while(it!=s.begin()) {
      it1=prev(it);
      if(it1==s.begin()) break;
      it2=prev(it1);
 
      if(cross_x(*it2,*it)>=cross_x(*it2,*it1)) {
        erase_line(it1);
        it=s.find(l);
      }
      else {
        break;
      }
    }
 
    while(it!=s.end()) {
      it1=next(it);
      if(it1==s.end()) break;
      it2=next(it1);
      if(it2==s.end()) break;
 
      if(cross_x(*it2,*it)>=cross_x(*it1,*it)) {
        erase_line(it1);
        it=s.find(l);
      }
      else {
        break;
      }
    }
  }
 
  long long get(long long x) {
    long long ans=eval(*s.begin(),x);

    set < cross_t >::iterator it=cross_set.lower_bound(cross_t(x,line(0,0)));
    if(it!=cross_set.end()) {
      ans=min(ans,eval(it->l,x));
      if(next(it)!=cross_set.end()) ans=min(ans,eval(next(it)->l,x));
    }
    if(it!=cross_set.begin()) {
      ans=min(ans,eval(prev(it)->l,x));
    }

    return ans;
  }
};
 
int n,h[N],w[N];
long long s[N];
dynamic_convex_hull_trick cht;
long long dp[N];
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int i;
 
  scanf("%d", &n);
  for(i=1;i<=n;i++) {
    scanf("%d", &h[i]);
  }
  for(i=1;i<=n;i++) {
    scanf("%d", &w[i]);
    s[i]=s[i-1]+w[i];
  }
 
  dp[n]=0;
  for(i=n-1;i>=1;i--) {
    cht.add_line(dynamic_convex_hull_trick::line(-2ll*h[i+1],s[i]+h[i+1]*1ll*h[i+1]+dp[i+1]));
    dp[i]=h[i]*1ll*h[i]-s[i]+cht.get(h[i]);
  }

  printf("%lld\n", dp[1]);
 
  return 0;
}
