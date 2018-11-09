#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 2;
const int INF = 1e9 + 7;

/************************************/
string A, B;
int dp[2][N];

int main() {
	while (getline(cin, A)) {
		getline(cin, B);
		for (int posA = A.size(); posA >= 0; posA --) {
			for (int posB = B.size(); posB >= 0; posB --) {
				if (posA == A.size() || posB == B.size()) {
					dp[posA&1][posB] = 0;
					continue;
				}
				int &ans = dp[posA&1][posB] = 0;
				ans = max(ans, dp[(posA + 1)&1][posB]);
				ans = max(ans, dp[posA&1][posB + 1]);
				if (A[posA] == B[posB]) {
					ans = max(ans, 1 + dp[(posA + 1)&1][posB + 1]);
				}
			}
		}
		cout << dp[0][0] << endl;
	}

	return 0;
}