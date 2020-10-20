#include <bits/stdc++.h>

using namespace std;
char tu[100][100];
int nxt[][2]={0,1,1,0,0,-1,-1,0};
bool go(int x,int y)
{
    for(int i=0;i<4;i++){
        int nx=x+nxt[i][0],ny=y+nxt[i][1];
        if(tu[nx][ny]=='G')return false;
        if(tu[nx][ny]=='.')tu[nx][ny]='#';
    }
    return true;
}

int vis[100][100];

int dis[100][100];
void bfs(int n,int m)
{
    memset(vis,0,sizeof vis);
    queue<pair<int,int> > que;
    que.push(make_pair(n,m));
    
    vis[n][m]=1;
    while(!que.empty())
    {
        pair<int,int> u=que.front();que.pop();
        for(int i=0;i<4;i++){
            int nx=u.first+nxt[i][0];
            int ny=u.second+nxt[i][1];
            if(vis[nx][ny])continue;
            if(nx<=0||ny<=0||nx>n||ny>m)continue;
            if(tu[nx][ny]=='#')continue;
            vis[nx][ny]=1;
            //dis[nx][ny]=dis[u.first][u.second]+1;
            que.push({nx,ny});
        }
    }
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;cin>>n>>m;
        getchar();
        memset(tu,0,sizeof tu);
        for(int i=1;i<=n;i++){
            gets(tu[i]+1);
        }
        int f=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(tu[i][j]=='B')if(!go(i,j))f=1;;
            }
        }
        if(f){
            cout<<"NO"<<endl;continue;
        }
        memset(vis,0,sizeof vis);
        if(tu[n][m]!='#')bfs(n,m);
        
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(tu[i][j]=='G'){
                    if(vis[i][j]==0)f=1;
                }
            }
        }
        if(f){
            cout<<"NO"<<endl;
        }else {
            cout<<"YES"<<endl;
        }
    }
}