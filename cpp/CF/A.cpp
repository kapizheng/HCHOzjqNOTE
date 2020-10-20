#include<bits/stdc++.h>
using namespace std;
const int maxn=250010;
// int trie[maxn][6],num[maxn];
// int tot,ans=0,n,m,L;
// bitset<1001>vis[maxn];//请用bitset 不然会被卡空间
// char s[1005],str[505];
// int ark(char c)//将字符处理为各个数字
// {
//     if(c=='A') return 0;
//     if(c=='G') return 1;
//     if(c=='T') return 2;
//     if(c=='C') return 3;
//     if(c=='?') return 4;
//     return 5;
// }
// void make_trie(char sa[505])//建trie树
// {
//     int now=0,len=strlen(sa);
//     for(int i=0;i<len;i++){
//         int next=ark(sa[i]);
//         if(!trie[now][next]){
//             trie[now][next]=++tot;
//         }
//         now=trie[now][next];
//     }
//     num[now]++;//因为可能有重复字符串，所以这里是++，而不是赋为1
// }
// void dfs(int x,int now)
// {
//     if(x==L)//如果匹配成功（一定为模式串结尾 ）
//     {
//         ans+=num[now];
//         num[now]=0;//记得清0 不然就重复算了
//         return;
//     }
//     if(vis[now][x])//记搜
//     {
//         return;
//     }
//     vis[now][x]=1;//赋初值
//     if(ark(s[x])==4)//如果当前字符为？
//     {
//         for(int i=0;i<=3;i++){
//             if(trie[now][i]){
//                 dfs(x+1,trie[now][i]);//将？当成任意一个字符匹配
//             }
//         }
//     }
//     if(ark(s[x])==5)//如果当前字符为*
//     {
//         dfs(x+1,now);//不匹配*
//         for(int i=0;i<=3;i++)
//         {
//             if(trie[now][i])
//             {
//                 dfs(x+1,trie[now][i]);
//                 dfs(x,trie[now][i]);
//             }
//         }
//     }
//     if(trie[now][ark(s[x])])//如果当前字符为字母
//     {
//         dfs(x+1,trie[now][ark(s[x])]);
//     }
// }
// int dp[2006][2006];//走到b的第i个，a的j个需要多少操作
long long ksm(long long a,long long b){
    long long ans=1;
    while(b--){
        ans*=a;
    }
    return ans;
}
int a[1005];
int dp[1005][2*20004];
int main()
{
    int n;
    scanf("%d",&n);
    int maxv=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        maxv=max(a[i],maxv);
    }
    
    for(int i=0;i<=2*maxv;i++){
        dp[0][i]=1;
    }
    int ans=0;
    const int mod=998244353;
    for(int i=1;i<=n;i++){
        for(int j=1;j<i;j++){
            dp[i][a[i]-a[j]+maxv]+=dp[j][a[i]-a[j]+maxv]+1;
            dp[i][a[i]-a[j]+maxv]%=mod;
            ans+=dp[j][a[i]-a[j]+maxv]+1;
            ans%=mod;
        }
    }
    
    cout<<(ans+n)%mod<<endl;
}