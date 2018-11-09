int num[N];
int L[N];

int bs(int r, int num) {
	int l = 0;
	while (l <= r) {
		int me = (l + r) >> 1;
		if (L[me] < num) l = me + 1;
		else r = me - 1;
	}
	return r;
}

int LIS(int n) {
	int size = 0;
	for (int i = 0; i < n; i ++) {
		int pos = bs(size - 1, num[i]) + 1;
		size = max(size, pos + 1);
		L[pos] = num[i];
	}
	return size;
}