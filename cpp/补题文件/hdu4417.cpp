#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
int n, m;
#include <algorithm>
const int maxn = 1e5 + 10;
int sz[maxn];
int fa[maxn];
int dep[maxn];
int top[maxn], dfn[maxn], rnk[maxn];
struct node{int l, r, sum;} no[maxn << 5];
struct edge{int v, nxt;} e[maxn * 2];
int cnt = 0;
int head[maxn];
int son[maxn];
int a[maxn];
int tim;
void add(int u, int v){e[cnt] = {v, head[u]};head[u] = cnt++;}
void push_up(int v){no[v].sum = no[no[v].l].sum + no[no[v].r].sum;}
int tt;
int M;
void update(int &now, int pre, int l, int r, int k)
{
    now = ++tt;
    no[now] = no[pre];
    no[now].sum++;
    if (l == r)
    {
        return;
    }
    int m = (l + r) >> 1;
    if (k <= m){
        update(no[now].l, no[pre].l, l, m, k);}
    else{
        update(no[now].r, no[pre].r, m + 1, r, k);}
}
int hs[maxn];
int rt[maxn];

int T;
int query(int R, int L, int l, int r, int k)
{
    int m = (l + r) >> 1;
    if (l == r){
        return no[R].sum - no[L].sum;}
    else if (k <= r && k > m)
    {
        return no[no[R].l].sum - no[no[L].l].sum + query(no[R].r, no[L].r, m + 1, r, k);
    }
    else if (k <= m && k >= l){
        return query(no[R].l, no[L].l, l, m, k);}
    return 0;
}

int main()
{
    int n, m;
    int t;
    cin >> t;
    int cas=1;
    while (t--)
    {
        printf("Case %d:\n",cas++);
        scanf("%d%d", &n, &m);
        memset(head, -1, sizeof head);
        tt = 0;
        for (int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
            hs[i] = a[i];
        }
        sort(hs + 1, hs + 1 + n);
        M = unique(hs + 1, hs + 1 + n) - hs - 1;
        for (int i = 1; i <= n; i++)
        {
            int idx = lower_bound(hs + 1, hs + 1 + M, a[i]) - hs;
            update(rt[i], rt[i - 1], 1, M, idx);
        }
        for (int i = 1; i <= m; i++)
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            b++, a++;
            int idx = lower_bound(hs + 1, hs + 1 + M, c) - hs;
            if (hs[idx] != c){
                idx--;}
            printf("%d\n", query(rt[b], rt[a - 1], 1, M, idx));
        }
    }
}