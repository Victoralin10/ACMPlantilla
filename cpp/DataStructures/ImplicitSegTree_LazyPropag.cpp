typedef long long Long;

struct Node {
	Node* left = NULL;
	Node* right = NULL;
	int ans = 0;
	bool lazy = false;
	node() {}
};

void aplicate(Node *node, Long b, Long e) {
	if (!node->lazy) return;
	node->ans = (e - b + 1 - node->ans)%mod;
	if (b != e) {
		if (!node->left) node->left = new Node;
		if (!node->right) node->right = new Node;
		node->left->lazy ^= 1;
		node->right->lazy ^= 1;
	}
	node->lazy = false;
}

void update(Node* node, Long b, Long e, Long l, Long r) {
	aplicate(node, b, e);
	if (r < b || e < l) return;
	if (l <= b && e <= r) {
		node->lazy = true;
		aplicate(node, b, e);
		return;
	}
	Long me = (b + e) >> 1;
	if (!node->left) node->left = new Node;
	if (!node->right) node->right = new Node;
	update(node->left, b, me, l, r);
	update(node->right, me + 1, e, l, r);
	node->ans = (node->left->ans + node->right->ans)%mod;
}

Long query(Node *node, Long b, Long e, Long l, Long r) {
	if (r < b || e < l) return 0;
	aplicate(node, b, e);
	if (l <= b && e <= r) return node->ans;
	Long me = (b + e) >> 1;
	if (!node->left) node->left = new Node;
	if (!node->right) node->right = new Node;
	int q1 = query(node->left, b, me, l, r);
	int q2 = query(node->right, me + 1, e, l, r);
	return (q1 + q2)%mod;
}

Node *tree[2];

void initTrees(int n) {
	for (int i = 0; i < n; i ++) {
		tree[i] = new Node;
	}
}