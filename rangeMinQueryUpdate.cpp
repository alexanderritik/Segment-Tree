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
vector<ll>  seg(800008);
vector<ll>  a(200001);


void build(ll idx , ll start , ll end)
{
	//base case when there is only one element available
	if (start == end)
	{
		seg[idx] = a[start];
		return;
	}

	ll mid = (start + end) / 2;
	build(idx * 2 , start , mid);
	build(idx * 2 + 1 , mid + 1, end);

	seg[idx] = min(seg[idx * 2] , seg[idx * 2 + 1]);
	return;

}

ll query(ll idx , ll start , ll end , ll qs , ll qe)
{
	if (qs > end || qe < start)
		return INT_MAX;

	if (start >= qs && end <= qe)
		return seg[idx];

	ll mid = (start + end) / 2;
	ll l = query(idx * 2 , start , mid, qs, qe);
	ll r = query(idx * 2 + 1 , mid + 1 , end, qs, qe);

	return min(l, r);
}

// this is a point update
void update(ll idx, ll start , ll end , ll newPos)
{
	if (start == end)
	{
		seg[idx] = a[start];
		return ;
	}

	ll mid = (start + end) / 2;

	if (newPos <= mid) update(idx * 2 , start , mid, newPos);
	else update(idx * 2 + 1 , mid + 1 , end, newPos);

	seg[idx] = min(seg[idx * 2 + 1], seg[idx * 2]);

	return;
}



int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	fastIO;

	ll n, q;
	cin >> n >> q;

	// Insert the given array
	for (ll i = 1; i <= n; ++i)
	{
		cin >> a[i];
	}

	build(1, 1, n);

	while (q--)
	{
		ll ch , l , r;
		cin >> ch ;
		if (ch == 2) {
			cin >> l >> r;
			cout << query(1, 1, n, l, r) << endl;
		}
		else {
			ll pos, val;
			cin >> pos >> val;
			a[pos] = val;
			update(1, 1, n, pos);

		}
	}



	return 0;
}