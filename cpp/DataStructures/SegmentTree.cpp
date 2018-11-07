#define LEFT(x) (2*x)
#define RIGHT(x) (2*x + 1)
int tree[N << 2];
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

void update(int node, int b, int e, int pos, int newVal) {
	if (b == e) {
		tree[node] = newVal;
		return;
	}
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	if (pos <= me) update(leftChild, b, me , pos, newVal);
	else update(rightChild, me + 1, e, pos, newVal);
	tree[node] = tree[leftChild] + tree[rightChild];
}

int query(int node, int b, int e, int l, int r) {
	if (r < b || e < l) return 0;
	if (l <= b && e <= r) return tree[node];
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	return query(leftChild, b, me, l, r) + query(rightChild, me + 1, e, l , r);
}