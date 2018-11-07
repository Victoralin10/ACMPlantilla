#define LEFT(x) (2*x)
#define RIGHT(x) (2*x + 1)
int tree[N << 2];
int lazy[N << 2];
int num[N];

void buildST(int node, int b, int e) {
	if (b == e) {
		tree[node] = num[b];
		return;
	}
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	buildST(leftChild, b, me);
	buildST(rightChild, me + 1, e);
	tree[node] = tree[leftChild] + tree[rightChild];
}

void aplicate(int node, int b, int e) {
	if (!lazy[node]) return;
	tree[node] += (e - b + 1)*lazy[node];
	if (b != e) {
		int leftChild = LEFT(node), rightChild = RIGHT(node);
		lazy[leftChild] += lazy[node];
		lazy[rightChild] += lazy[node];
	}
	lazy[node] = 0;
}

void update(int node, int b, int e, int l, int r, int add) {
	aplicate(node, b, e);
	if (r < b || e < l) return;
	if (l <= b && e <= r) {
		lazy[node] = add;
		aplicate(node, b, e);
		return;
	}
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	update(leftChild, b, me , l, r, add);
	update(rightChild, me + 1, e, l, r, add);
	tree[node] = tree[leftChild] + tree[rightChild];
}

int query(int node, int b, int e, int l, int r) {
	if (r < b || e < l) return 0;
	aplicate(node, b, e);
	if (l <= b && e <= r) return tree[node];
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	return query(leftChild, b, me, l, r) + query(rightChild, me + 1, e, l , r);
}