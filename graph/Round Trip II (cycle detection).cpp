#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define vi vector<int>
#define vl vector<long long>
#define pii pair<int,int>
#define PQ priority_queue
#define N 100001
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

vi g[N], cycle;
int ans[N], vis[N];
bool ok=false;

void dfs(int u)
{
    vis[u]=1;
    for(auto &v: g[u])
    {
        if(ok) break;
        if(vis[v]==-1)
        {
            ans[v]=u;
            dfs(v);
        }
        else if(vis[v]==1)
        {
            while(u!=v)
            {
                cycle.pb(u);
                u=ans[u];
            }
            cycle.pb(u);
            ok=true;
        }
    }
    vis[u]=2;
}

int main()
{
    //ios::sync_with_stdio(false);
    //cin.tie(0);

    int n,m,t=0;
    cin>>n>>m;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        g[u].pb(v);
    }
    for(int i=1; i<=n; i++)
        vis[i]=ans[i]=-1;

    for(int i=1; i<=n && !ok; i++)
        if(vis[i]==-1) dfs(i);

    if(cycle.empty()) cout<<"IMPOSSIBLE\n";
    else
    {
        int k=cycle.size();
        cout<<k+1<<'\n';
        cout<<cycle[0]<<' ';
        for(int i=k-1; i>=0; i--) cout<<cycle[i]<<' ';
        cout<<'\n';
    }
}
