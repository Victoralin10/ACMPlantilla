struct Query {
	int l, r, pos;
};

Query q[N];
int ans[N];
int curr_ans;

void remove(int num) {}

void add(int num) {}

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i ++) {
		scanf("%d", &num[i]);
	}
	int l, r;
	for (int i = 0; i < m; i ++) {
		scanf("%d %d", &l, &r);
		l --, r --; /*indexed of zero*/
		q[i] = {l, r, i};
	}
	int lenBlock = sqrt(1.*n) + 1;
	sort(q, q + m, [lenBlock](Query q1, Query q2){
		if (q1.l/lenBlock != q2.l/lenBlock)
			return q1.l/lenBlock < q2.l/lenBlock;
		return q1.r < q2.r;
	});
	int curr_l = 0;
	int curr_r = -1;
	for (int i = 0; i < n; i ++) {
		while (curr_l < q[i].l)
			remove(num[curr_l ++]);
		while (q[i].l < curr_l)
			add(num[-- curr_l]);
		while (q[i].r < curr_r)
			remove(num[curr_r --]);
		while (curr_r < q[i].r)
			add(num[++ curr_r]);
		ans[q[i].pos] = curr_ans;
	}
	for (int i = 0; i < m; i ++) {
		printf("%d\n", ans[i]);
	}

	return 0;
}