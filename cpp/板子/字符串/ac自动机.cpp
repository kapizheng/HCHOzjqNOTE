#include <bits/stdc++.h>


using namespace std;
const int N=100006*4;
vector<int> v[N];
struct node
{
    int ch[N][26];
    int fail[N];
    int tot;
    int cnt[N];
    void init(){
        memset(ch[0],0,sizeof ch[0]);
        tot=0;fail[0]=cnt[0]=0;tot++;v[0].clear();
    }
    void ins(char *str)
    {
        int L=strlen(str);
        int rt=0;
        for(int i=0;i<L;i++){
            int c=str[i]-'a';
            if(!ch[rt][c]){
                memset(ch[tot],0,sizeof ch[tot]);
                ch[rt][c]=tot;fail[tot]=0;cnt[tot]=0;tot++;v[tot-1].clear();
            }rt=ch[rt][c];
        }
        cnt[rt]=1;
    }
    void build()
    {
        queue<int> que;
        for(int i=0;i<26;i++)if(ch[0][i])que.push(ch[0][i]),fail[ch[0][i]]=0;
        while(!que.empty())
        {
            int u=que.front();que.pop();
            cnt[u]|=cnt[fail[u]];
            for(int i=0;i<26;i++){
                if(!ch[u][i]){
                    ch[u][i]=ch[fail[u]][i];
                }else {
                    fail[ch[u][i]]=ch[fail[u]][i];
                    que.push(ch[u][i]);
                }
            }
        }
    }
}ac;
char s[N];
int dis[N];
int A[N];
int main()
{
    int n;
    while(~scanf("%d",&n))
    {
        ac.init();
        for(int i=1;i<=n;i++){
            scanf("%s",s);
            ac.ins(s);
        }
        ac.build();
        queue<int> que;
        memset(dis,-1,sizeof dis);
        for(int i=0;i<ac.tot;i++){
            if(ac.cnt[i])que.push(i),dis[i]=0;
            for(int j=0;j<26;j++){
                v[ac.ch[i][j]].push_back(i);
            }
        }
        while(!que.empty()){
            int u=que.front();que.pop();
            for(int i=0;i<v[u].size();i++){
                int nx=v[u][i];
                if(dis[nx]==-1){
                    que.push(nx);dis[nx]=dis[u]+1;
                }
            }
        }

        scanf("%s",s);
        int len=strlen(s);
        int t=0;
        int rt=0;
        printf("%d\n",dis[0]);
        memset(A,0,sizeof A);
        for(int i=0;i<len;i++){
            if(s[i]=='-'){
                if(t)t--;
                printf("%d\n",dis[A[t]]);
            }else {
                rt=ac.ch[A[t]][s[i]-'a'];
                A[++t]=rt;
                printf("%d\n",dis[A[t]]);
            }
        }
    }
   
}