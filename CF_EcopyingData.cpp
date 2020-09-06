#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const ll maxs = 1e6 + 5;

ll tree[maxs];

void build(ll n, ll l , ll r)
{
	if (l == r)
	{
		tree[n] = -1;
		return ;
	}
	ll mid = (l + r) / 2;
	build(n * 2, l, mid);
	build(n * 2 + 1, mid + 1, r);
	tree[n] = -1;
}

void update(ll n, ll x, ll y, ll l, ll r, ll id)
{
	if (l > y || r < x)
		return ;
	if (l >= x && r <= y)
	{
		tree[n] = id;
		return ;
	}
	ll mid = (l + r) / 2;

	update(n * 2, x, y, l, mid, id);

	update(n * 2 + 1, x, y, mid + 1, r, id);
}


ll query(ll n, ll l, ll r, ll x)
{
	if (x > r || l > x)
		return -1;
	if (l == r)
	{
		return tree[n];

	}
	ll mid = (l + r) / 2;
	ll a = query(n * 2, l, mid, x);
	ll b = query(n * 2 + 1, mid + 1, r, x);
	return max(a, max(tree[n], b));

}
int main()
{
	ll n, i, x, y, t, op;
	cin >> n >> t;
	ll arr[maxs];
	ll str[maxs];
	for (i = 1; i <= n; i++)
		cin >> arr[i];
	for (i = 1; i <= n; i++)
		cin >> str[i];
	vector<pair<ll, pair<ll, ll>>>q;
	build(1, 1, n);

	ll cnt = 0;
	while (t--)
	{
		cin >> op;
		if (op == 2)
		{
			cin >> x;
			ll f = query(1, 1, n, x);
			if (f == -1)
				cout << str[x] << endl;
			else
			{
				ll l = q[f].first, r = q[f].second.first, k = q[f].second.second;
				ll id = x - r + l;
				cout << arr[id] << endl;
			}
		}
		else
		{
			ll k;
			cin >> x >> y >> k;
			update(1, y, y + k - 1, 1, n, cnt++);
			q.push_back({x, {y, k}});

		}
	}

}