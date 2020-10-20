#include<bits/stdc++.h>

using namespace std;

const int N=200006;
const int maxn=200006;

struct node
{
    int ch[10];int len,fa,left;
    int val;//left表示该状态串出现的最左边的点？
}no[N];

int las,tot;
void add_no(int u,int val)
{
    int p=las,np=las=++tot;
    no[np].len=no[p].len+1;
    for(;p&&!no[p].ch[u];p=no[p].fa)no[p].ch[u]=np;
    if(!p){
        no[np].fa=1;return ;
    }

    int q=no[p].ch[u];//表示对应那个点
    if(no[q].len==no[p].len+1)no[np].fa=q;//表示不存在a|ba|ba这种情况
    else {
        int nq=++tot;
        no[nq]=no[q];//nq表示只+1的结点，且他的父亲还是+n的结点的父亲
        no[nq].len=no[p].len+1;//是要链接长度只+1的结点的
        no[np].fa=no[q].fa=nq;//插入的点是让Len+1的点
        for(;p&&no[p].ch[u]==q;p=no[p].fa)
            no[p].ch[u]=nq;//把原本链接到q
    }
};
//性质:防止忘记:不同子串个数等于dian[las].len-dian[dian[las].fa].len
//当前sta最短的长度为no[no[i].fa].len+1
int n;
int b[maxn],id[maxn];
void sort()
{
    int Len=n;
    // for(int p=1,i=0;i<Len;i++)p=no[p].ch[str[i]-'a'],r[p]++;
    for(int i=1;i<=tot;i++)b[no[i].len]++;//要排序，让长度短的在前面
    for(int i=1;i<=n;i++)b[i]+=b[i-1];
    for(int i=1;i<=tot;i++)id[b[no[i].len]--]=i;
    // for(int i=tot;i>=1;i--)r[no[id[i]].fa]=r[id[i]];
}//拓扑排序.jpg

int main()
{
    int t;cin>>t;int kk=1;
    memset(no,0,sizeof no);
    tot=las=1;
    while(t--){
        string str;
        cin>>str;
        int n=str.length();
        for(int i=0;i<n;i++){
            add_no(str[i]-'0',str[i]-'0');
        }
        
    }
    int ans=0;
    for(int i=2;i<=tot;i++){
            ans=(ans+no[i].val)%2012;
        }
        cout<<ans<<endl;
    
}