#include<bits/stdc++.h>
using namespace std;
int n,a,b,c,st[18][100005],cost[100005],level[100005], gcd[18][100005];
vector<pair<int,int> >g[100005];
void dfs(int s,int p) {
    // cout<<gcd[0][s]<<" "<<s<<" -----\n";
    for(int i=0; i<(int)g[s].size(); i++) {
        if(g[s][i].first!=p) {
            level[g[s][i].first]=level[s]+1;
            cost[g[s][i].first]=cost[s]+g[s][i].second;
            st[0][g[s][i].first]=s;
            gcd[0][g[s][i].first]=g[s][i].second;
            dfs(g[s][i].first,s);
        }
    }
    return;
}
int lca(int x,int y, int &g) {
    if(level[x]<level[y])swap(x,y);
    g=0;
    for(int i=17; i>=0; i--) {
        if((level[x]-(1<<i))>=level[y]) {
            g=__gcd(g, gcd[i][x]);
            x=st[i][x];
        }
    }
    // cout<<g<<" x "<<x<<" g\n";
    if(x==y)return x;
    for(int i=17; i>=0; i--) {
        if(st[i][x]!=-1 && st[i][x]!=st[i][y]) {
            g=__gcd(g, gcd[i][x]);
            g=__gcd(g, gcd[i][y]);
            // cout<<g<<" -g\n";
            x=st[i][x];
            y=st[i][y];
        }
    }
    g=__gcd(g, gcd[0][x]);
    g=__gcd(g, gcd[0][y]);
    return st[0][x];
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int q;
    cin>>n>>q;
    for(int i=1; i<n; i++) {
        cin>>a>>b>>c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    memset(st,-1,sizeof(st));
    dfs(1,-1);
    for(int i=1; (1<<i)<n; i++) {
        for(int j=1; j<=n; j++) {
            if(st[i-1][j]!=-1) {
                st[i][j]=st[i-1][st[i-1][j]];
                gcd[i][j]=__gcd(gcd[i-1][st[i-1][j]], gcd[i-1][j]);
            }
        }
    }
    while(q--) {
        cin>>a>>b;
        int l=lca(a, b, c);
        // cout<<c<<"\n";
        int tcost = cost[a]+cost[b]-2*cost[l];
        cout<<c<<" "<<tcost/c<<"\n";
    }
    return 0;
}