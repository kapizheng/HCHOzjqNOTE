#include <bits/stdc++.h>
using namespace std;
struct _IO{_IO(){ios::sync_with_stdio(0);cin.tie(0);}}_io;
typedef long long ll; typedef long double db;
const int N = 2e6 + 5, M = 1e9 + 7;
  
int sa[N], rk[N], oldrk[N << 1], id[N], px[N], cnt[N];
// px[i] = rk[id[i]]（用于排序的数组所以叫 px）
  
bool cmp(int x, int y, int w) {
  return oldrk[x] == oldrk[y] && oldrk[x + w] == oldrk[y + w];
}
  
void da(int *s, int n, int m) {
    int i,p,w;
    for(int i=0;i<=n;i++)cnt[i]=0;
 for (i = 1; i <= n; ++i) ++cnt[rk[i] = s[i]];
  for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
  for (i = n; i >= 1; --i) sa[cnt[rk[i]]--] = i;
  
  for (w = 1; w < n; w <<= 1, m = p) {  // m=p 就是优化计数排序值域
    for (p = 0, i = n; i > n - w; --i) id[++p] = i;
    for (i = 1; i <= n; ++i)
      if (sa[i] > w) id[++p] = sa[i] - w;
    //memset(cnt, 0, sizeof(cnt));
    for(int i=0;i<=n;i++)cnt[i]=0;
    for (i = 1; i <= n; ++i) ++cnt[px[i] = rk[id[i]]];
    for (i = 1; i <= m; ++i) cnt[i] += cnt[i - 1];
    for (i = n; i >= 1; --i) sa[cnt[px[i]]--] = id[i];
    for(int i=0;i<=n;i++)oldrk[i]=rk[i];
    //memcpy(oldrk, rk, sizeof(rk));
    for (p = 0, i = 1; i <= n; ++i)
      rk[sa[i]] = cmp(sa[i], sa[i - 1], w) ? p : ++p;
  }
  
}
struct node
{
    int a,b,idx;
    bool operator<(const node&n)const{
        if(n.a==a)return b<n.b;
        else return a<n.a;
    }
}no[N];
char str[N];
int a[N];
int MP[3]={0};
int main()
{
    int n;
    while(~scanf("%d",&n)){
        scanf("%s",str);
        MP[0]=MP[1]=-1;
        for(int i=0;i<n;i++){
            if(str[i]=='a'&&MP[0]!=-1){
                a[i+1]=i+1-MP[0];
                MP[0]=i+1;
            }else if(str[i]=='b'&&MP[1]!=-1){
                a[i+1]=i+1-MP[1];
                MP[1]=i+1;
            }else if(str[i]=='a'){
                MP[0]=i+1;
                a[i+1]=1;
            }else if(str[i]=='b')
            {
                a[i+1]=1;
                MP[1]=i+1;
            }
        }
        a[n+1]=0;
        da(a,n,n);
        MP[0]=MP[1]=n+1;
        rk[n+1]=-1;
        rk[n+2]=-2;
        for(int i=n-1;i>=0;i--){
            if(str[i]=='a'){
                no[i].a=MP[1]-i,no[i].b=rk[MP[1]+1],no[i].idx=i+1;
                MP[0]=i+1;
            }else {
                no[i].a=MP[0]-i,no[i].b=rk[MP[0]+1],no[i].idx=i+1;
                MP[1]=i+1;
            }
        }
        sort(no,no+n);
        for(int i=0;i<n;i++){
            printf("%d ",no[i].idx);
        }
        puts("");
    }
}