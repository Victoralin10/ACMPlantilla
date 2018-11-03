int BIT[N];

void update(int x, int n, int add) {
	for (; x <= n; x += x&-x) {
		BIT[x] += add;
	}
}

int query(int x) {
	int sum = 0;
	for (; x; x -= x&-x) {
		sum += BIT[x];
	}
	return sum;
}

int Query(int l, int r) {
	return query(r) - query(l - 1);
}