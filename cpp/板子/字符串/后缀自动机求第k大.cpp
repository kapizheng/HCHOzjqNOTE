#include<bits/stdc++.h>

using namespace  std;
const int maxn=900500;
struct node
{
    int len,fa;
    int ch[30];
    node(){
        len=0;fa=0;
        memset(ch,0,sizeof ch);
    }
}no[maxn<<1];
int las,tot;
void add(int c)
{
    c-='a';
    int p=las,now=las=++tot;
    no[now].len=no[p].len+1;
    for(;p&&no[p].ch[c]==0;p=no[p].fa)no[p].ch[c]=now;
    if(!p){
        no[now].fa=1;return ;
    }
    int q=no[p].ch[c];
    if(no[q].len==no[p].len+1){
        no[now].fa=q;
    }else {
        int sta=++tot;
        no[sta]=no[q];
        no[sta].len=no[p].len+1;
        no[now].fa=no[q].fa=sta;
        for(;p&&no[p].ch[c]==q;p=no[p].fa)no[p].ch[c]=sta;
    }
}

int b[maxn];
int id[maxn<<1];
int f[maxn];
int len[maxn<<1];
int res[maxn];
int n;
void sort()
{
    for(int i=1;i<=tot;i++)b[no[i].len]++;//要排序，让长度短的在前面
    for(int i=1;i<=n;i++)b[i]+=b[i-1];
    for(int i=1;i<=tot;i++)id[b[no[i].len]--]=i;
}
char str[maxn];
void find()
{
    int p=1;
    int ans=0;
    memset(len,0,sizeof len);
    int N=strlen(str);
    int RES=0;
    for(int i=0;i<N;i++){
        if(no[p].ch[str[i]-'a']){
            p=no[p].ch[str[i]-'a'],ans++;
        }else {
            for(;p&&!no[p].ch[str[i]-'a'];p=no[p].fa);
            if(p==0){
                ans=0;p=1;
            }else {
                ans=no[p].len+1;p=no[p].ch[str[i]-'a'];
            }
        }
        RES=max(ans,RES);
    }
    cout<<RES<<endl;
}
struct edge
{
    int v,nxt,w;
}e[maxn<<4];
int cnt;
int head[maxn<<1];
void add_edge(int u,int v,int w)
{
    e[cnt].v=v;e[cnt].nxt=head[u];e[cnt].w=w;
    head[u]=cnt++;
}//边
int Cnt[maxn<<1];
void dfs(int u,int f)
{
    if(Cnt[u])return ;
    Cnt[u]=1;
    for(int i=0;i<26;i++){
        int v=no[u].ch[i];
        if(v==0)continue;
        dfs(v,u);
        Cnt[u]+=Cnt[v];
    }
}
string S;
void Find(int p,int k){
    if(k==0)return ;
    for(int i=0;i<26;i++){
        if(!no[p].ch[i])continue;
        int num=Cnt[no[p].ch[i]];
        if(k<=num){
            p=no[p].ch[i];
            S+=char(i+'a');
            Find(p,k-1);break;
        }else k-=num;
    }
}

int main()
{
    cin>>str;
    las=tot=1;
    n=strlen(str);
    memset(head,-1,sizeof head);
    for(int i=0;i<n;i++){
        add(str[i]);
    }
    for(int i=2;i<=tot;i++){
        add_edge(no[i].fa,i,0);
    }
    dfs(1,0);
    int t;cin>>t;
    while(t--){
        S="";
        int k;scanf("%d",&k);
        Find(1,k);
        cout<<S<<endl;
    }

}