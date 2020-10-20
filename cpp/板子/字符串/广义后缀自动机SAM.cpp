#include<bits/stdc++.h>

using namespace std;
const int maxn=6e5+10;
struct node
{
    int fa,ch[26],len;
}no[maxn];
int tot;
int add_no(int u,int last)
{
    if(no[last].ch[u]&&no[no[last].ch[u]].len==no[last].len+1)
        return no[last].ch[u];

    int p=last,np=++tot;
    int now;
    no[np].len=no[last].len+1;
    for(;p&&!no[p].ch[u];p=no[p].fa)no[p].ch[u]=np;
    int flag=0;
    if(!p)no[np].fa=1;
    else {
        int q=no[p].ch[u];
        if(no[q].len==no[p].len+1)no[np].fa=q;
        else {
            if(no[np].len==no[p].len+1)flag=1;//什么时候放后面的呢？
            now=++tot;memcpy(no[now].ch,no[q].ch,sizeof(no[now].ch));

            no[now].fa=no[q].fa;
            no[now].len=no[p].len+1;
            no[np].fa=no[q].fa=now;
            for(;p&&no[p].ch[u]==q;p=no[p].fa)no[p].ch[u]=now;
        }
    }
    return flag?now:np;
}

char str[maxn];
int b[maxn];
int id[maxn];
int rt[maxn];
int fa[maxn];
int cnt[maxn];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    scanf("%s",str);
    tot=1;
    rt[1]=add_no(str[0]-'A',1);
    for(int i=2;i<=n;i++){
        int x;
        scanf("%d",&x);
        fa[i]=x;
        rt[i]=add_no(str[i-1]-'A',rt[fa[i]]);
    }
    // cout<<endl;
    for(int i=1;i<=n;i++)cnt[rt[i]]++;
    for(int i=0;i<=tot;i++)b[i]=0;
    for(int i=1;i<=tot;i++)b[no[i].len]++;
    for(int i=1;i<=tot;i++)b[i]+=b[i-1];
    for(int i=1;i<=tot;i++)id[b[no[i].len]--]=i;
    for(int i=tot;i>=1;i--){
        int u=id[i];
        cnt[no[u].fa]+=cnt[u];
        // cout<<cnt[u]<<endl;
    }
    while(m--){
        int a,b;
        scanf("%d%d",&a,&b);
        int p=rt[a];
        while(no[no[p].fa].len>=b){
            p=no[p].fa;
        }
        printf("%d\n",cnt[p]);
    }

}