#include<bits/stdc++.h>
using namespace std;
#define N 300003
#define inf 0x3f3f3f3f
#define ll long long
#define p 998244353
vector<int> adj[N];
int n,m,cnt;
int depth[N],son[N],s[N][51],sz[N];
int id[N],top[N],fa[N];
inline int power(int a,int t){
    int res = 1;
    while(t){
        if(t&1) res = (ll)res*a%p;
        a = (ll)a*a%p;
        t >>= 1;
    }
    return res;
}
inline void read(int &x){
    x = 0;
    char c = getchar();
    while(!isdigit(c)) c = getchar();
    while(isdigit(c)){
        x = (x<<3)+(x<<1)+c-'0';
        c = getchar();
    }
}
void print(int x){
    if(x>9) print(x/10);
    putchar(x%10+'0');
}
void dfs1(int u,int f){
    depth[u] = depth[f]+1;
    for(int i=0;i<=50;++i){
        s[u][i] = s[f][i]+power(depth[u]-1,i);
        s[u][i] %= p;
    }
    fa[u] = f;
    sz[u] = 1;
    int v,t = -1,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i];
        if(v==f) continue;
        dfs1(v,u);
        sz[u] += sz[v];
        if(sz[v]>t){
            t = sz[v];
            son[u] = v;
        }
    }
}
void dfs2(int u,int f){
    id[u] = ++cnt;
    top[u] = f;
    if(son[u]==0) return;
    dfs2(son[u],f);
    int v,l = adj[u].size();
    for(int i=0;i<l;++i){
        v = adj[u][i];
        if(v==fa[u]||v==son[u]) continue;
        dfs2(v,v);
    }
}
inline int lca(int u,int v){
    int t;
    while(top[u]!=top[v]){
        if(depth[top[u]]<depth[top[v]]){
            t = u;
            u = v;
            v = t;
        }
        u = fa[top[u]];
    }
    if(depth[u]<depth[v]) return u;
    return v;
}
int main(){
    int u,v,k,f,ans;
    read(n);
    for(int i=1;i<n;++i){
        read(u),read(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(1,1);
    read(m);
    ++m;
    while(--m){
        read(u),read(v),read(k);
        f = lca(u,v);
        ans = (s[u][k]+s[v][k])%p;
        ans -= (s[f][k]+s[fa[f]][k])%p;
        ans = (ans+p)%p;
        print(ans);
        putchar(10);
    }
    return 0;
}
