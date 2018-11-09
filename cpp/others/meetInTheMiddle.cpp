#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 2;
const int INF = 1e9 + 7;

/************************************/
int bs(vector<long long> &v, long long num) {
	int l = 0, r = v.size() - 1;
	while (l <= r) {
		int me = (l + r) >> 1;
		if (v[me] <= num) l = me + 1;
		else r = me - 1;
	}
	return r + 1;
}

int s[34];

int main() {
	int n, l, r;
	cin >> n >> l >> r;
	for (int i = 0; i < n; i ++) {
		scanf("%d", &s[i]);
	}
	int lenA = n/2, lenB = n - n/2;
	vector<long long> A;
	for (int mask = 0; mask < 1 << lenA; mask ++) {
		long long sum = 0;
		for (int i = 0; i < lenA; i ++) {
			if ((mask >> i)&1) {
				sum += s[i];
			}
		}
		A.push_back(sum);
	}
	sort(A.begin(), A.end());
	long long ans = 0;
	for (int mask = 0; mask < 1 << lenB; mask ++) {
		long long sum = 0;
		for (int i = 0; i < lenB; i ++) {
			if ((mask >> i)&1) {
				sum += s[i + lenA];
			}
		}
		ans += bs(A, r - sum) - bs(A, l - sum - 1);
	}
	cout << ans;

	return 0;
}