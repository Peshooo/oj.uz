#include <bits/stdc++.h>
 
using namespace std;
 
const int N = (2e5) + 7;
 
int n,a[N],b[N];
int up,down;
bool used[N];
 
void go_up() {
    while(used[up]) --up;
    used[up]=true;
}
 
void go_down() {
    while(used[down]) ++down;
    used[down]=true;
}
 
int main() {
    int tests,current_case;
    int i;
 
    tests=1;
    //scanf("%d", &tests);
    for(current_case=1;current_case<=tests;current_case++) {
        scanf("%d", &n);
        for(i=1;i<=n;i++) {
            scanf("%d", &b[i]);
        }
        memset(used,0,sizeof(used));
        down=0;
        up=2*n;
        used[down]=used[up]=true;
        a[1]=b[1];
        used[b[1]]=true;
        for(i=2;i<=n;i++) {
            if(b[i]==b[i-1]) {
                go_up();
                a[2*(i-1)]=up;
                go_down();
                a[2*(i-1)+1]=down;
            }
            else if(b[i]>b[i-1]) {
                if(!used[b[i]]) {
                    used[b[i]]=true;
                    a[2*(i-1)]=b[i];
                    go_up();
                    a[2*(i-1)+1]=up;
                }
                else {
                    go_up();
                    a[2*(i-1)]=up;
                    go_up();
                    a[2*(i-1)+1]=up;
                }
            }
            else {
                if(!used[b[i]]) {
                    used[b[i]]=true;
                    a[2*(i-1)]=b[i];
                    go_down();
                    a[2*(i-1)+1]=down;
                }
                else {
                    go_down();
                    a[2*(i-1)]=down;
                    go_down();
                    a[2*(i-1)+1]=down;
                }
            }
        }
    }
    for(i=1;i<2*n;i++) {
        if(i>1) printf(" ");
        printf("%d", a[i]);
    }
 
    return 0;
}
