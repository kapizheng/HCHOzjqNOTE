#include<bits/stdc++.h>
using namespace std;

struct pt {
  int x, y, id;
};

struct cmp_x {
  bool operator()(const pt& a, const pt& b) const {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
  }
};

struct cmp_y {
  bool operator()(const pt& a, const pt& b) const { return a.y < b.y; }
};

int n;
vector<pt> a;
double mindist;
int ansa, ansb;

inline void upd_ans(const pt& a, const pt& b) {
  double dist =
      sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y) + .0);
  if (dist < mindist) mindist = dist, ansa = a.id, ansb = b.id;
}

void rec(int l, int r) {
  if (r - l <= 3) {
    for (int i = l; i <= r; ++i)
      for (int j = i + 1; j <= r; ++j) upd_ans(a[i], a[j]);
    sort(a + l, a + r + 1, &cmp_y);
    return;
  }

  int m = (l + r) >> 1;
  int midx = a[m].x;
  rec(l, m), rec(m + 1, r);
  static pt t[MAXN];
  merge(a + l, a + m + 1, a + m + 1, a + r + 1, t, &cmp_y);
  copy(t, t + r - l + 1, a + l);

  int tsz = 0;
  for (int i = l; i <= r; ++i)
    if (abs(a[i].x - midx) < mindist) {
      for (int j = tsz - 1; j >= 0 && a[i].y - t[j].y < mindist; --j)
        upd_ans(a[i], t[j]);
      t[tsz++] = a[i];
    }
}

void use()
{
    sort(a, a + n, &cmp_x);
    mindist = 1E20;
    rec(0, n - 1);
}