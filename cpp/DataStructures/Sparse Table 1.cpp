int num[N];
int st[N][logN];

void buildST(int n) {
	for (int i = 1; i <= n; i ++) {
		st[i][0] = num[i];
	}
	for (int loglen = 1, len = 2; len <= n; loglen ++, len <<= 1) {
		for (int i = 1; i + len -1 <= n; i ++) {
			st[i][loglen] = min(st[i][loglen - 1], st[i + len/2][loglen - 1]);
		}
	}
}

int query(int l, int r) {
	int loglen = 31 - __builtin_clz(r - l + 1);
	int len = 1 << loglen;
	return min(st[l][loglen], st[r - len + 1][loglen]);
}