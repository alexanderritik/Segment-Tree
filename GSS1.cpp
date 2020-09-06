/*
    Author  : <<grenade24>>
    Email   : << rakeshkusrivastav@gmail.com >>
    Date    : 2020-06-07 01:48:11
*/

//#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <bitset>
#include <string>
#include <utility>
#include <iterator>
#include <fstream>
#include <sstream>
#include <numeric>
#include <functional>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cctype>
#include <climits>
#include <ctime>
#include <cassert>


using namespace std;


/* typedef starts */

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef long long      ll;
typedef pair<int, int> ii;
typedef pair<ii, int>  iii;
typedef vector<int>    vi;
typedef vector<ii>     vii;
typedef vector<iii>    viii;
/* typedef ends */

/* macro starts */


#define mp             make_pair
#define pb             push_back
#define eb             emplace_back
#define fi             first
#define se             second
#define sz(x)          (int)((x).size())
#define fill(x, y)     memset(x, y, sizeof(x))
#define all(x)         (x).begin(), (x).end()
#define sci(x)         int x;       scanf("%d", &x);
#define scii(x, y)     int x, y;    scanf("%d %d", &x, &y);
#define sciii(x, y, z) int x, y, z; scanf("%d %d %d", &x, &y, &z);
#define TC(x)          sci(x); while(x --)
#define eprintf(...)   fprintf(stderr, __VA_ARGS__)
#define debug(x)       { cerr << #x << " = " << x << endl; }
#define rep(i, x, y)   for (int i = x; i <= y; i ++)
#define repi(i, x, y)  for (int i = x; i >= y; i --)
#define fore(itr, x)   for (auto itr:x)
#define forei(itr, x)  for (__typeof(x.end()) itr = x.end() - 1; itr != x.begin() - 1; itr --)

#define PI acos(-1.0)
#define EPS 1e-9
#define fastIO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
#define sinD(degree) sin((degree * PI) / 180.0)
#define cosD(degree) cos((degree * PI) / 180.0)
#define tanD(degree) tan((degree * PI) / 180.0)
#define cotD(degree) (1.0 / tanD(degree))
#define secD(degree) (1.0 / cosD(degree))
#define cosecD(degree) (1.0 / sinD(degree))
#define asinD(value) (asin(value) * 180.0) / PI
#define acosD(value) (acos(value) * 180.0) / PI
#define atanD(value) (atan(value) * 180.0) / PI
#define value_at_index(x) find_by_order(x)
#define index_of(x) order_of_key(x)
#define endl '\n'
/* macro ends */

/* function starts */

/// calculates n-th (0-based) Gray Code
template<typename dataType>
dataType nthGrayCode(dataType n)
{
	return (n ^ (n >> 1));
}

/// generates all possible subsets for the given set
template<typename dataType>
void generateAllSubset(vector<dataType> &data)
{
	int i, j, n;
	n = data.size();

	for (i = 0; i < (1 << n); i++) {
		for (j = 0; j < n; j++) {
			if (i & (1 << j)) {
				cout << data[j] << " ";
			}
		}
		cout << "\n";
	}
}

/* function ends */

struct data
{
	ll ans, suff , pref , sum;
};

int a[10001];
vector<data> seg(40005);

data make_data( int val)
{
	data res;
	res.sum = val;
	res.pref = res.suff = res.ans = val;
	return res;
}

data combine(data l , data r)
{
	data res;
	res.sum = l.sum + r.sum;
	res.pref = max(l.pref , l.sum + r.pref);
	res.suff = max(r.suff , l.suff + r.sum);
	res.ans = max(l.suff + r.pref , max(l.ans, r.ans));
	return res;
}

void build(int idx, int start , int end)
{
	if (start == end)
	{
		seg[idx] = make_data(a[start]);
		return;
	}

	int mid = (start + end) / 2;
	build(idx * 2 , start , mid);
	build(idx * 2 + 1, mid + 1 , end);

	seg[idx] = combine(seg[idx * 2], seg[idx * 2 + 1]);


	return;
}

data query (int v, int tl, int tr, int l, int r) {
	if (l == tl && tr == r)
		return seg[v];
	int tm = (tl + tr) / 2;

	if (r <= tm)
		return query (v * 2, tl, tm, l, r);
	if (l > tm)
		return query (v * 2 + 1, tm + 1, tr, l, r);
	return combine (
	           query (v * 2, tl, tm, l, tm),
	           query (v * 2 + 1, tm + 1, tr, tm + 1, r)
	       );
}

void pointUpdate(int idx, int start , int end , int pos)
{
	if (start == end)
	{
		seg[idx] = make_data(a[start]);
		return;
	}
	int mid = (start + end) / 2;

	if (pos <= mid)
		pointUpdate(idx * 2 , start , mid , pos);
	else
		pointUpdate(idx * 2 + 1 , mid + 1 , end , pos);

	seg[idx] = combine(seg[idx * 2] , seg[idx * 2 + 1]);

}


int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	fastIO;
	int t;
	cin >> t;
	while (t--)
	{
		seg.clear();
		int n;
		cin >> n;
		for (int i = 1; i <= n; ++i)
		{
			cin >> a[i];
		}


		build(1, 1, n);

		int q;
		cin >> q;
		while (q--)
		{
			int x1, y1 , x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			int total;
			// cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
			if (x2 == y1)
			{
				total = query(1, 1, n, x1, y1).ans;
			}
			else if (x2 > y1 )
			{

				total = query(1, 1, n, x1, y1).suff;
				total += query(1, 1, n, x2, y2).pref;

				if (y1 + 1 <= x2 - 1)
					total += query(1, 1, n, y1 + 1, x2 - 1).sum;
			}
			else
			{
				total = query(1, 1, n, x2, y1).ans;
				int t1 = ( (query(1, 1, n, x1, x2 - 1).suff) + (query(1, 1, n, x2, y2).pref));
				int t2 = (query(1, 1, n, x1, y1).suff) + (query(1, 1, n, y1 + 1, y2).pref);
				total = max( total, max( t1  , t2 )  );
			}
			cout << total << endl;
		}

	}




	return 0;
}