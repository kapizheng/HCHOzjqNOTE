#include<bits/stdc++.h>

using namespace std;
const int maxn=1e5+10;

int p[maxn];
    int m;
int cap[202][202];
int liu[202][202];
int n;
int pre[maxn];
void bfs(int s,int t)
{
    queue<int>que;
    que.push(s);
    memset(p,0,sizeof p);
    memset(pre,0,sizeof pre);
    p[s]=0x3f3f3f3f;
    while(!que.empty()){
        int u=que.front();que.pop();
        for(int i=1;i<=m;i++){
            if(p[i]==0&&liu[u][i]<cap[u][i]){
                p[i]=min(p[u],cap[u][i]-liu[u][i]);
                pre[i]=u;
                que.push(i);
            }
        }
    }
}

void find(int s,int t)
{
    int ed=t;
    while(pre[t]){
        liu[pre[t]][t]+=p[ed];
        liu[t][pre[t]]-=p[ed];
        t=pre[t];
    }
}

void EK(int s,int t)
{
    long long ans=0;
    int z=0;
    while(1){
        bfs(s,t);
        if(p[t]==0)break;
        ans+=p[t];
        find(s,t);
    }
    cout<<ans<<endl;
}


int main()
{
    cin>>n>>m;

    for(int i=1;i<=n;i++){
        int a,b,c,d;
        cin>>a>>b>>c>>d;
        cap[a][b]+=c;
		
    }
    EK(1,m);
}