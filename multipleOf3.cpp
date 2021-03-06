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




struct tri
{
	int arr[3];
};

vector<tri>  seg(400004);
vector<int>  lazy(400004);

void shift(int si)
{
	int a = seg[si].arr[2];
	seg[si].arr[2] = seg[si].arr[1];
	seg[si].arr[1] = seg[si].arr[0];
	seg[si].arr[0] = a;
}

void build(int idx , int start , int end)
{
	if (start == end)
	{
		seg[idx].arr[0] = 1;
		seg[idx].arr[1] = 0;
		seg[idx].arr[2] = 0;
		return;
	}

	int mid = (start + end) / 2;
	build(idx * 2 , start, mid);
	build(idx * 2 + 1 , mid + 1 , end);

	seg[idx].arr[0] = seg[idx * 2].arr[0] + seg[idx * 2 + 1].arr[0];
	seg[idx].arr[1] = seg[idx * 2].arr[1] + seg[idx * 2 + 1].arr[1];
	seg[idx].arr[2] = seg[idx * 2].arr[2] + seg[idx * 2 + 1].arr[2];
}




void update(int idx, int start , int end , int qs , int qe)
{
	if (lazy[idx])
	{
		int dx = lazy[idx];
		lazy[idx] = 0;
		int val = dx;

		if (start != end)
		{
			lazy[idx * 2] += val;
			lazy[idx * 2 + 1] += val;
		}
		dx = dx % 3;
		for (int i = 0; i < dx; i++)
		{
			shift(idx);
		}
	}

	if (start > qe || end < qs) return;

	if (start >= qs && end <= qe)
	{
		shift(idx);
		if (start != end)
		{
			lazy[2 * idx] += 1;
			lazy[2 * idx + 1] += 1;
		}
		return;
	}

	int mid = (start + end) / 2;
	update(idx * 2 , start , mid , qs , qe);
	update(idx * 2 + 1 , mid + 1 , end , qs, qe);

	seg[idx].arr[0] = seg[2 * idx].arr[0] + seg[2 * idx + 1].arr[0];
	seg[idx].arr[1] = seg[2 * idx].arr[1] + seg[2 * idx + 1].arr[1];
	seg[idx].arr[2] = seg[2 * idx].arr[2] + seg[2 * idx + 1].arr[2];
	return;
}


int query(int idx, int start, int end, int qs, int qe)
{
	if (lazy[idx])
	{
		int dx = lazy[idx];
		lazy[idx] = 0;
		int val = dx;
		if (start != end)
		{
			lazy[idx * 2] += val;
			lazy[idx * 2 + 1] += val;
		}

		dx %= 3;

		for (int i = 0; i < dx; i++)
		{
			shift(idx);
		}
	}

	if (qe < start || qs > end)
		return 0;

	if (start >= qs && end <= qe)
	{
		return seg[idx].arr[0];
	}

	int mid = (start + end) / 2;

	int left = query(idx * 2 , start , mid , qs, qe);
	int right = query(idx * 2 + 1 , mid + 1 , end , qs, qe);
	return left + right;
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	fastIO;

	int n , q;
	cin >> n >> q;



	build(1, 1, n);



	while (q--)
	{
		int ch, a, b;
		cin >> ch >> a >> b;
		if (ch == 0)
			update(1, 1, n, a + 1, b + 1);
		else {
			// cout << a + 1 << " " << b + 1 << endl;
			cout  << query(1, 1, n, a + 1, b + 1) << endl;
		}
	}





	return 0;
}