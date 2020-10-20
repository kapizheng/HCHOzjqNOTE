#include <bits/stdc++.h>

using namespace std;
const int maxn=3200005;
struct node{int l,r,sum,lazy;}no[maxn*4];
int sz[maxn],top[maxn],fa[maxn],son[maxn],d[maxn],head[maxn];
struct Tire
{
    int ch[maxn][2];
    int sz;
    void init()
    {
        memset(ch[0],0,sizeof ch[0]);sz=1;
    }
    void insert(int x)
    {
        int rt=0;
        for(int i=1<<30;i;i>>=1){
            bool tmp=x&i;
            if(ch[rt][tmp]==0){
                memset(ch[sz],0,sizeof ch[sz]);
                ch[rt][tmp]=sz++;
            }
            rt=ch[rt][tmp];
        }
    }
    int find(int x)
    {
        int ans=0;
        int rt=0;
        for(int i=1<<30;i;i>>=1){
            bool tmp=x&i;
            if(ch[rt][tmp^1])
            rt=ch[rt][tmp^1],ans+=i;
            else rt=ch[rt][tmp];
        }
        return ans;
    }
    
}tire;
struct edge
{
    int v,nxt,val;
}e[maxn];
int cnt=0;
void add_edge(int u,int v,int val)
{
    e[cnt]={v,head[u],val};head[u]=cnt++;
}
int ans=0;
int dis[maxn];
void dfs(int u,int fl){
    for(int i=head[u];~i;i=e[i].nxt){
        int v=e[i].v;if(v==fl)continue;
        dis[v]=dis[u]^e[i].val;
        dfs(v,u);
    }
}
string W[20],I[20],N[20],G[20];

int dp[10][10][10];
string D[205][205];



int main()
{
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    map<char,int> mp;
    mp['W']=1;
    mp['I']=2;
    mp['N']=3;
    mp['D']=4;
    string str;
    for(int i=1;i<=a;i++){
        cin>>str;
        dp[mp[str[0]]][mp[str[1]]][mp['W']]=1;
    }
    for(int i=1;i<=b;i++){
        cin>>str;
        dp[mp[str[0]]][mp[str[1]]][mp['I']]=1;
    }
    for(int i=1;i<=c;i++){
        cin>>str;
        dp[mp[str[0]]][mp[str[1]]][mp['N']]=1;
    }
    for(int i=1;i<=d;i++){
        cin>>str;
        dp[mp[str[0]]][mp[str[1]]][mp['D']]=1;
    }
    map<int,char> mpp;
    mpp[1]='W';mpp[2]='I';mpp[3]='N';mpp[4]='D';
    cin>>str;
    int n=str.length();
    // solve();
    for(int i=0;i<n;i++){
        D[i][i]=str[i];
    }
    for(int len=2;len<=n;len++){
        for(int i=0;i+len-1<n;i++){
            int j=i+len-1;
            for(int k=i;k<j;k++){
                if(D[i][k].size()==1&&D[k+1][j].size()==1){
                    int L=mp[D[i][k][0]],R=mp[D[k+1][j][0]];
                    for(int kind=1;kind<=4;kind++){
                        if(dp[L][R][kind]){
                            D[i][j]=mpp[kind];break;
                        }
                    } 
                }
                if(D[i][j]!=""){
                    continue;
                }
                else {D[i][j]=D[i][k]+D[k+1][j];}
            }
        }
    }
    int f=1;
    for(int i=0;i<D[0][n-1].size();i++){
        int idx=mp[D[0][n-1][i]];
        if(idx==0){
            f=0;break;
        }
    }
    if(f&&D[0][n-1]!=""){
        int cnt[5]={0};
        for(int i=0;i<D[0][n-1].size();i++){
            cnt[mp[D[0][n-1][i]]]++;
        }
        for(int i=1;i<=4;i++){
            for(int j=0;j<cnt[i];j++){
                cout<<mpp[i];
            }
        }
    }
    else cout<<"The name is wrong!"<<endl;
    return 0;
}