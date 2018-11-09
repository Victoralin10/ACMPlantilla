#include <bits/stdc++.h>
using namespace std;

const int N = 1e3 + 2;
const int INF = 1e9 + 7;

/************************************/
string A, B;
bool used[N][N];
int memo[N][N];

int dp(int posA, int posB) {
	if (posA == A.size() || posB == B.size()) return 0;
	if (used[posA][posB]) return memo[posA][posB];
	used[posA][posB] = true;
	int &ans = memo[posA][posB] = 0;
	ans = max(ans, dp(posA + 1, posB));
	ans = max(ans, dp(posA, posB + 1));
	if (A[posA] == B[posB]) {
		ans = max(ans, 1 + dp(posA + 1, posB + 1));
	}
	return ans;
}

int main() {
	while (getline(cin, A)) {
		getline(cin, B);
		memset(used, 0, sizeof used);
		cout << dp(0, 0) << endl;
	}

	return 0;
}