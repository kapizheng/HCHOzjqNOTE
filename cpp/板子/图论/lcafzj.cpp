#include <bits/stdc++.h>
using namespace std;
const int maxn=3e5+10;
struct node {
	int to,Next;
}Edge[maxn<<1];
int Head[maxn],cnt,lg[maxn],dp[maxn][30],dep[maxn],dis[maxn];
void Add(int from, int to) {
	Edge[cnt]={to,Head[from]};
	Head[from]=cnt++;
	Edge[cnt]={from,Head[to]};
	Head[to]=cnt++;
}
int LCA(int a, int b) {
	if (dep[a]<dep[b]) swap(a,b);
	while (dep[a]>dep[b]) {
		a=dp[a][lg[dep[a]-dep[b]]-1];	//LCA���٣�������a=dp[a][0] 
	}
	if (a==b) return a;
	for (int i=lg[dep[a]]-1; i>=0; --i) {
		if (dp[a][i]!=dp[b][i]) {
			a=dp[a][i];
			b=dp[b][i];
		}
	}
	return dp[a][0];
}

void dfs(int u, int fa) {
	if (fa==-1) dep[u]=0;
	else dep[u]=dep[fa]+1;
	dp[u][0]=fa;
	for (int i=1; i<lg[dep[u]]; ++i) {
		dp[u][i]=dp[dp[u][i-1]][i-1];
	}
	for (int i=Head[u]; ~i; i=Edge[i].Next) {
		int v=Edge[i].to;
		if (v==fa) continue;
		dis[v]=dis[u]+1;
		dfs(v,u);
	}
}
using namespace std;
int cs[maxn],f[maxn],st[25][maxn],dep[maxn];
int First[maxn],Next[maxn*2],v[maxn*2],num_edge;
 
 
void ins(int x , int y )
{
    v[++ num_edge] = y;
    Next[num_edge] = First[x];
    First[x] = num_edge;
}
int n,root;
void dfs(int x,int fa)
{
    f[x] = fa;
    for(int i = First[x]; i != -1 ; i = Next[i])
    {
        int to = v[i];
        if(to == fa)
            continue;
        dep[to] = dep[x] + 1;
        dfs(to,x);
    }
}
int get_lca(int x, int y)
{
    if(dep[x] < dep[y]) swap(x,y);
    for(int i = 20 ; i >= 0 ; i--)
    {
        if(dep[st[i][x]] >= dep[y])
        {
            x = st[i][x];
        }
    }
    if(x == y) return x;
    for(int i = 20 ; i >= 0; i--)
    {
        if(st[i][x] != st[i][y])
        {
            x = st[i][x];
            y = st[i][y];
        }
    }
    return f[x];
}
int main() {
	for (int i=1; i<maxn; ++i) {
		lg[i]=lg[i-1]+((1<<lg[i-1])==i);
	}
	int n;
	int t;
	scanf("%d",&t);
	while(t--){
		cnt=0;
		memset(Head,-1,sizeof(Head));
		int q;
		scanf("%d%d",&n,&q);
		for (int i=1; i<n; ++i) {
			int a,b;
			scanf("%d%d",&a,&b);
			Add(a,b);
		}
		dis[1]=0;
		dfs(1,-1);
		while (q--) {
			int a,b,c;scanf("%d%d%d",&a,&b,&c);
			
			int dis1=dis[c]+dis[b]-2*dis[LCA(c,b)];	
			if(dis1+dis[c]>dis[a]){
				printf("YES\n");
			}else if(dis1+dis[c]<dis[a]){
				printf("NO\n");
            }else {
                if(LCA(a,c)!=1){
				printf("YES\n");
                }else {
                    printf("NO\n");
                }
            }
		}	
	}
	
	return 0;
}
