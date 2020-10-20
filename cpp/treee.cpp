#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5 + 100;
struct edge
{
    int v, nxt, w;
} e[maxn << 4];
int cnt;
int head[maxn];
void add_edge(int u, int v, int w)
{
    e[cnt].v = v;
    e[cnt].nxt = head[u];
    e[cnt].w = w;
    head[u] = cnt++;
} //边
template <class T>
void read(T &res)
{
    res = 0;
    char c = getchar();
    T f = 1;
    while (c < '0' || c > '9')
    {
        if (c == '-')
            f = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9')
    {
        res = res * 10 + c - '0';
        c = getchar();
    }
    res *= f;
}
int d[maxn];
int fa[maxn];
int sz[maxn];
int son[maxn];
int hs[maxn];
int dfn[maxn];
int rnk[maxn];
int top[maxn];
int M; //M表示离散，tot表示
struct node
{
    int l, r, sum;
    int L, R;
} no[maxn << 4];
int tt;
void build(int &v, int l, int r)
{
    v = ++tt;
    no[v].l = l, no[v].r = r;
    no[v].sum = 0;
    if (l == r)
    {
        return;
    }
    int m = (l + r) >> 1;
    build(no[v].L, l, m);
    build(no[v].R, m + 1, r);
}
void update(int &now, int pre, int l, int r, int pos)
{
    now = ++tt;
    no[now] = no[pre];
    no[now].l = l, no[now].r = r;
    no[now].sum++;
    if (l == r)
        return;
    int m = (l + r) >> 1;
    if (pos <= m)
        update(no[now].L, no[pre].L, l, m, pos);
    else
        update(no[now].R, no[pre].R, m + 1, r, pos);
}
int ans;
int query(int v, int l, int r)
{
    int LL = no[v].l, RR = no[v].r;
    if(no[v].sum==0)return 0;
    if (l == LL && RR == r)
    {
        return no[v].sum;
    }
    int m = (no[v].r + no[v].l) >> 1;
    if (r <= m)
        return query(no[v].L, l, r);
    else if (m < l)
        return query(no[v].R, l, r);
    else
    {
        return query(no[v].L, l, m) + query(no[v].R, m + 1, r);
    }
}

void dfs(int u, int f)
{
    fa[u] = f;
    d[u] = d[f] + 1;
    sz[u] = 1;
    for (int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == f)
            continue;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[son[u]] < sz[v])
            son[u] = v;
    }
}
int val[maxn];
int rt[maxn];
int tim;
void dfs2(int u, int f)
{
    update(rt[u], rt[f], 1, M, lower_bound(hs + 1, hs + M, val[u]) - hs);
    if (son[u])
    {
        dfn[son[u]] = ++tim;
        rnk[tim] = son[u];
        top[son[u]] = top[u];
        dfs2(son[u], u);
    }
    for (int i = head[u]; ~i; i = e[i].nxt)
    {
        int v = e[i].v;
        if (v == f)
            continue;
        if (v == son[u])
            continue;
        dfn[v] = ++tim;
        rnk[tim] = v;
        top[v] = v;
        dfs2(v, u);
    }
}
int asklca(int a, int b)
{
    int ta = top[a], tb = top[b];
    while (ta != tb)
    {
        if (d[ta] < d[tb])
            swap(ta, tb), swap(a, b);
        a = fa[ta], ta = top[a];
    }
    if (d[a] > d[b])
        return b;
    else
        return a;
}

bool check(int m, int a, int b, int c, int z)
{

    int lca = asklca(a, b);
    int all = d[a] + d[b] - 2 * d[lca];
    int top = lower_bound(hs + 1, hs + M, m + c) - hs;
    int down = lower_bound(hs + 1, hs + M, c - m) - hs;
    if (top > M)
        top = M;
    // if(hs[down]!=c-m)down--;
    // if(down==0)down=1;
    ans = 0;
    ans += query(rt[a], down, top);
    ans += query(rt[b], down, top);
    ans -= 2 * query(rt[lca], down, top);
    all -= ans;
    // cout<<all<<endl;
    return all <= z;
}
int A[maxn], B[maxn], C[maxn];
inline int read()
{
    char ch = getchar();
    int x = 0, f = 1;
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while ('0' <= ch && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline void write(int x)
{
    if (x < 0)
        x = ~x + 1, putchar('-');
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

void solve()
{
    int n, m;
    memset(head, -1, sizeof head);
    read(n), read(m);
    cnt = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        int a, b, c;read(a), read(b), read(c);
        son[i] = 0;
        A[i] = a, B[i] = b, C[i] = c;
        hs[i] = c;
        add_edge(a, b, c);
        add_edge(b, a, c);
    }
    hs[n] = 2e9, hs[n + 1] = -2e9;
    son[n] = 0;
    sort(hs + 1, hs + n + 2);
    M = unique(hs + 1, hs + n + 2) - hs - 1;
    tt = 0;
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
    {
        int a = A[i], b = B[i];
        if (d[a] > d[b])
            val[a] = C[i];
        else
            val[b] = C[i];
    }
    rnk[1] = dfn[1] = top[1] = 1, tim = 1;
    build(rt[0], 1, M);

    dfs2(1, 0);
    for (int i = 1; i <= m; i++)
    {
        int a, b, c, d;
        int Ans = 0x3f3f3f3f;
        read(a), read(b), read(c), read(d);
        int l = 0, r = 2e9 + 10;
        while (l <= r)
        {
            int m = l + (r - l + 1) / 2;
            if (!check(m, a, b, c, d))
            {
                l = m + 1;
            }
            else
            {
                Ans = min(Ans, m);
                r = m - 1;
            }
        }
        write(Ans);
        puts("");
    }
}

int main()
{
    int t;
    read(t);
    while (t--)
    {
        solve();
    }
}