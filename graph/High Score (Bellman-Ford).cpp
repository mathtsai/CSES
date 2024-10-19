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
vector<pair<pii,int>> g;
ll dis[N];
bool vis[N];

void dfs(int u)
{
    vis[u] = true;
    for(auto &v: gt[u])
    {
        if(!vis[v]) dfs(v);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin>>n>>m;

    //init
    for(int i=1; i<=n; i++)
    {
        dis[i] = 4e16;
        vis[i] = false;
    }
    while(m--)
    {
        int u,v,w;
        cin>>u>>v>>w;
        g.pb({{u,v},-w});
        //reverse g
        gt[v].pb(u);
    }
    //mark all vertices can be reach from vertex n
    dfs(n);
    //Bellman-Ford
    dis[1]=0;
    for(int i=0; i<n-1; i++)
    {
        for(auto &[vertex,w]: g)
        {
            auto &[u,v] = vertex;
            if(dis[u]+w < dis[v])
                dis[v] = dis[u]+w;
        }
    }
    //vertex u can be reached from vertex 1 and n, and it is in an negative cycle
    for(auto &[vertex,w]: g)
    {
        auto &[u,v] = vertex;
        if(vis[u] && dis[u]<2e16 && dis[u]+w < dis[v])
        {
            cout<<"-1\n";
            return 0;
        }
    }

    cout<<-dis[n]<<'\n';
}
