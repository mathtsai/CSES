#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define vi vector<int>
#define vl vector<long long>
#define pii pair<int,int>
#define PQ priority_queue
#define N 2501
using namespace std;
const int mod = 1e9+7;
//const int mod = 998244353;

/*class Int
{
public:
    ll val;
    Int(ll b=0)
    {
        val = b%mod;
        if(val<0) val+=mod;
    }
    Int& operator+=(Int const &b)
    {
        val = (val+b.val)%mod;
        return *this;
    }
    Int& operator-=(Int const &b)
    {
        val = (val-b.val)%mod;
        if(val<0) val+=mod;
        return *this;
    }
    Int& operator*=(Int const &b)
    {
        val = (val*b.val)%mod;
        return *this;
    }
    friend Int Pow(Int a, int b);
    friend Int inv(Int a);
    friend Int operator+(Int a, Int const b) { return a += b; }
    friend Int operator-(Int a, Int const b) { return a -= b; }
    friend Int operator-(Int const a) { return 0 - a; }
    friend Int operator*(Int a, Int const b) { return a *= b; }
    friend bool operator != (Int a, Int b) {return a.val!=b.val;}
    friend std::ostream& operator<<(std::ostream& os, Int const& a) {return os << a.val;}
};

Int factor[N];

Int Pow(Int a, int b)
{
    Int res=1;
    while(b)
    {
        if(b&1) res*=a;
        a*=a;
        b>>=1;
    }
    return res;
}

Int inv(Int a)
{
    return Pow(a,mod-2);
}

Int C(int m, int n)
{
    if(n>m || n<0) return 0;
    if(n==0 || n==m) return 1;
    return factor[m]*inv(factor[m-n]*factor[n]);
}*/

vi gt[N];
vector<pii> g[N];
ll dis[N];
bool mark[N], vis[N];

bool dfs(int u)
{
    if(mark[u]) return true;
    vis[u]=true;
    bool ok = false;
    for(auto &v: gt[u])
    {
        if(!vis[v]) ok |= dfs(v);
    }
    return ok;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin>>n>>m;

    //init graph
    for(int i=1; i<=n; i++)
    {
        dis[i] = 1e18;
        mark[i] = false;
        vis[i] = false;
    }
    //input g
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g[u].pb({v,-w});
    }
    //Bellman-Ford
    dis[1]=0;
    for(int i=0; i<n-1; i++)
    {
        for(int j=1; j<=n; j++)
        {
            for(auto &[v,w]: g[j])
            {
                if(dis[j]+w < dis[v])
                    dis[v] = dis[j]+w;
            }
        }
    }
    //mark vertices can be reached from vertex 1, and in a negative cycle
    for(int i=1; i<=n; i++)
    {
        bool in = false;
        for(auto &[v,w]: g[i])
        {
            if(dis[i]<1e18 && dis[i]+w < dis[v]) in = true;
        }
        mark[i] = in;
    }
    //gt = reverse(g)
    for(int i=1; i<=n; i++)
    {
        for(auto &[v,w]: g[i])
            gt[v].pb(i);
    }
    //if vertex n can be reached from mark vertices, return -1
    if(dfs(n)) cout<<"-1\n";
    else cout<<-dis[n]<<'\n';
}
