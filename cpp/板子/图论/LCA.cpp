#include<bits/stdc++.h>

using namespace std;
const int maxn=1e6+10;
int lg[maxn];
int dep[maxn];
int dp[maxn][25];
int val[maxn][25];

struct edge
{
    int v,nxt,val;
}e[maxn*2];
struct node
{
    int u,v,val;
    bool operator<(const node &n)const{
        return val<n.val;
    }
}no[maxn];

int cnt;
int head[maxn];
void add_edge(int u,int v,int w)
{
    e[cnt].val=w;
    e[cnt].v=v;e[cnt].nxt=head[u];
    head[u]=cnt++;
}
void dfs(int u,int fa,int vv)
{
    
    if(fa==-1)dep[u]=0;
    else dep[u]=dep[fa]+1;
    if(fa!=-1)
    dp[u][0]=fa;
    else dp[u][0]=0;
    val[u][0]=vv;

    for(int i=1;i<lg[dep[u]];i++){
        dp[u][i]=dp[dp[u][i-1]][i-1];
        val[u][i]=min(val[u][i-1],val[dp[u][i-1]][i-1]);
    }
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;if(v==fa)continue;
        dfs(v,u,e[i].val);
    }
}
int LCA(int a,int b)
{
    if(dep[a]<dep[b])swap(a,b);
    int ans=0x3f3f3f3f;
    while(dep[a]>dep[b]){
        ans=min(ans,val[a][lg[dep[a]-dep[b]]-1]);
        a=dp[a][lg[dep[a]-dep[b]]-1];
    }
    if(a==b)return ans;
    for(int i=lg[dep[a]]-1;i>=0;i--){
        if(dp[a][i]!=dp[b][i]){
            ans=min(ans,val[a][i]);
            ans=min(ans,val[b][i]);
            a=dp[a][i];b=dp[b][i];
        }
    }
    if(dp[a][0]==-1){
        return ans;
    }
    return min(ans,min(val[a][0],val[b][0]));
}
int fa[maxn];
int get(int x)
{
    if(x==fa[x])return x;
    else return fa[x]=get(fa[x]);
}

int main()
{
    int n,m;  for(int i=1;i<maxn;i++){
        lg[i]=lg[i-1]+((1<<lg[i-1])==i);
    }
    while(cin>>n>>m)
    {
        cnt=0;
      
        memset(val,0x3f,sizeof val);
        memset(head,-1,sizeof head);
        memset(dep,-1,sizeof dep);
        for(int i=1;i<=n;i++){
            fa[i]=i;
        }
        for(int i=1;i<=m;i++){
            int a,b,c;
            scanf("%d%d%d",&a,&b,&c);
            no[i].u=a,no[i].v=b;no[i].val=c;
        }
        sort(no+1,no+1+m);
        for(int i=m;i>=1;i--){
            int ul=no[i].u,vl=no[i].v;
            int u=get(ul),v=get(vl);
            if(u!=v){
                fa[u]=v;
                add_edge(ul,vl,no[i].val);
                add_edge(vl,ul,no[i].val);
            }
        }
        
        dfs(1,-1,0x3f3f3f3f);
        int t;
        cin>>t;
        while(t--){
            int a,b;scanf("%d%d",&a,&b);
            int ans=LCA(a,b);
            if(get(a)!=get(b)){
                cout<<-1<<endl;continue;
            }
            if(ans==0x3f3f3f3f){
                cout<<-1<<endl;
            }else {
            cout<<ans<<endl;
            }
        }
    }
    
}