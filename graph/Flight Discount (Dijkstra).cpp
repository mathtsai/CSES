#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define vi vector<int>
#define vl vector<long long>
#define pii pair<int,int>
#define PQ priority_queue
#define N 200001
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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n,m;
    cin>>n>>m;

    //init graph
    vector<pii> g[n+1];
    while(m--)
    {
        int u,v,d;
        cin>>u>>v>>d;
        g[u].pb({v,d});
    }

    //init dis,vis
    ll dis[n+1][2];
    bool vis[n+1][2];
    memset(vis,false,sizeof(vis));
    for(int i=1; i<=n; i++) dis[i][0]=dis[i][1]=LLONG_MAX;

    dis[1][1]=0;
    using p=pair<ll,pii>;
    PQ<p,vector<p>,greater<>> pq;
    pq.push({0,{1,1}});

    //Dijkstra
    while(!pq.empty())
    {
        const auto [val,state] = pq.top(); pq.pop();
        const auto &[u,coupon] = state;

        if(vis[u][coupon]) continue;
        vis[u][coupon] = true;

        for(const auto &[v,w]: g[u])
        {
            //using coupon
            if(coupon)
            {
                if(val+w/2 < dis[v][0])
                {
                    dis[v][0] = val+w/2;
                    pq.push({dis[v][0], {v,0}});
                }
            }
            //not using coupon
            if(val+w < dis[v][coupon])
            {
                dis[v][coupon] = val+w;
                pq.push({dis[v][coupon], {v,coupon}});
            }
        }
    }
    cout<<min(dis[n][0],dis[n][1])<<'\n';
}
