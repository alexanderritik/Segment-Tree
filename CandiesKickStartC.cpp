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

int seg1[800008];
int seg2[800008];
int a[200002];

// for building
void build(int idx , int start , int end)
{
	if (start == end)
	{
		if (start % 2 != 0)
			seg1[idx] = a[start] * 1;
		else
			seg1[idx] = a[start] * -1;
		return;
	}

	int mid = (start + end) / 2;
	build(idx * 2, start, mid);
	build(idx * 2 + 1, mid + 1 , end);
	seg1[idx] = seg1[idx * 2] + seg1[idx * 2 + 1];
}


void buildfor2(int idx , int start , int end)
{
	if (start == end)
	{
		if (start % 2 != 0)
			seg2[idx] = a[start] * start ;
		else
			seg2[idx] = a[start] * -start;
		return;
	}
	int mid = (start + end) / 2;
	buildfor2(idx * 2, start, mid);
	buildfor2(idx * 2 + 1, mid + 1 , end);
	seg2[idx] = seg2[idx * 2] + seg2[idx * 2 + 1];
}



int query(int idx , int start , int end , int qs , int qe)
{
	if (start > qe || end < qs)
		return 0;
	if (start >= qs && end <= qe) {
		return seg1[idx];
	}
	int mid = (start + end) / 2;
	int left = query(idx * 2 , start , mid , qs , qe);
	int right = query(idx * 2 + 1 , mid + 1 , end , qs , qe);
	return left + right;
}

int queryfor2(int idx , int start , int end , int qs , int qe)
{
	if (start > qe || end < qs) {
		return 0;
	}
	if (start >= qs && end <= qe) {
		return seg2[idx];
	}
	int mid = (start + end) / 2;
	int left = queryfor2(idx * 2 , start , mid , qs , qe);
	int right = queryfor2(idx * 2 + 1 , mid + 1 , end , qs , qe);
	return left + right;
}

void update(int idx, int start, int end , int pos)
{
	if (start == end)
	{
		seg1[idx] = a[start];
		return;
	}

	int mid = (start + end) / 2;
	if (pos <= mid) update(idx * 2 , start , mid , pos);
	else update(idx * 2 + 1 , mid + 1 , end, pos);

	seg1[idx] = seg1[idx * 2] + seg1[idx * 2 + 1];
	return;
}


void updatefor2(int idx, int start, int end , int pos)
{
	if (start == end)
	{
		seg2[idx] = a[start];
		return;
	}

	int mid = (start + end) / 2;
	if (pos <= mid) updatefor2(idx * 2 , start , mid , pos);
	else updatefor2(idx * 2 + 1 , mid + 1 , end, pos);

	seg2[idx] = seg2[idx * 2] + seg2[idx * 2 + 1];
	return;
}


int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	fastIO;
	int chcase = 1;
	TC(t)
	{
		int n, q , ans = 0;
		cin >> n >> q;
		memset(seg1 , 0 , sizeof(seg1));
		memset(seg2 , 0 , sizeof(seg2));
		memset(a , 0 , sizeof(a));

		for (int i = 1; i <= n; i++)
		{
			cin >> a[i];
		}

		build(1, 1, n);
		buildfor2(1, 1, n);


		char ch;
		int l, r;
		while (q--)
		{
			cin >> ch >> l >> r;

			if (ch == 'Q')
			{
				int ans1 = query(1, 1, n, l, r);
				int ans2 = queryfor2(1, 1, n, l, r);
				if (l % 2 == 0)
				{
					ans1 = ans1 * -1;
					ans2 = ans2 * -1;
				}

				int f = ans2 - (l - 1) * ans1;
				// cout << f << endl;

				ans += f;
			}

			else
			{
				if (l % 2 != 0) a[l] = r * l ;
				else a[l] = r * l * -1 ;
				updatefor2(1, 1, n, l);

				if (l % 2 != 0) a[l] = r * 1;
				else a[l] = r * -1 ;
				update(1, 1, n, l);
			}

		}
		cout << "Case #" << chcase++ << ": " << ans << endl;
	}



	return 0;
}