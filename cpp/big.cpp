#include<bits/stdc++.h>

using namespace std;
const int maxn=2e6+10;
struct node
{
    int fa,ch[12],len;
}no[maxn<<1];
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
int rt[maxn];
int L[maxn];
int main()
{
    int n,m;
    scanf("%s",str);
    n=strlen(str);
    stack<int>s;
    s.push(0);
    for(int i=1;i<=n;i++){
        while(s.size()>1&&str[s.top()-1]<str[i-1]){
            s.pop();
        }
        L[s.top()]=1;
        s.push(i);
    }
    int now=1;
    rt[0]=1;tot=1;
    for(int i=n-1;i>=0;i--){
        
        if(L[i]){ 
            rt[now]=add_no(str[i]-'a',1);
            
            char maxv=str[i];
            cout<<maxv;
            for(int j=i+1;j<n;j++){
                rt[now]=add_no((maxv=max(maxv,str[j]))-'a',rt[now]);
                cout<<maxv;
            }now++;
            cout<<endl;
        }
    }
    int ans=0;
    for(int i=2;i<=tot;i++){
        ans+=no[i].len-no[no[i].fa].len;
    }
    cout<<ans<<endl;

}