#include<bits/stdc++.h>

using namespace std;
const int maxn=1e6+10;
struct Node
{
    int ch[26];
    int len,fa;
    Node(){memset(ch,0,sizeof ch);len=0;}
}dian[maxn];
int las;
int tot;
void add(int c)
{
    int p=las;int np=las=++tot;
    dian[np].len=dian[p].len+1;
    for(;p&&dian[p].ch[c]==0;p=dian[p].fa)dian[p].ch[c]=np;
    if(!p){
        dian[np].fa=1;
    }else {
        int q=dian[p].ch[c];
        if(dian[q].len==dian[p].len+1)dian[np].fa=q;
        else {
            int now=++tot;
            dian[now]=dian[q];
            dian[q].fa=dian[np].fa=now;

            for(;p&&dian[p].ch[c]==q;p=dian[p].fa)dian[p].ch[c]=now;
        }
    }
}
int len[maxn];
int res[maxn];
void go(string str)
{
    int p=1;
    int ans=1;
    memset(len,0,sizeof len);
    for(int i=0;i<str.length();i++){
        int c=str[i]-'a';
        if(dian[p].ch[c]){
            ans++;p=dian[p].ch[c];
        }else {
            for(;p&&dian[p].ch[c]==0;p=dian[p].fa);
            if(!p){
                ans=0;p=1;
            }else {
                ans=dian[p].len+1;p=dian[p].ch[c];
            }
        }
        len[p]=max(len[p],ans);
    }
    for(int i=1;i<=tot;i++){
        res[i]=min(len[i],res[i]);
    }
} 

int main()
{
    string str;cin>>str;
    tot=1;
    for(int i=0;i<str.length();i++){
            add(str[i]-'a');
        }
    memset(res,0x3f,sizeof res);
    while(cin>>str)
    {
        go(str);
    }
    int ans=0;
    for(int i=1;i<=tot;i++){
        ans=max(ans,res[i]);
    }
    cout<<ans<<endl;
}