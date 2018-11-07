typedef long long Long;

struct Node {
	Node* left = NULL;
	Node* right = NULL;
	Long ans = 0;
	node() {}
};

void update(Node* node, Long b, Long e, Long pos, Long add) {
	if (b == e) {
		node->ans += add;
		return;
	}
	Long me = (b + e) >> 1;
	if (!node->left) node->left = new Node;
	if (!node->right) node->right = new Node;
	if (pos <= me) update(node->left, b, me, pos, add);
	else update(node->right, me + 1, e, pos, add);
	node->ans = node->left->ans + node->right->ans;
}

Long query(Node *node, Long b, Long e, Long l, Long r) {
	if (r < b || e < l) return 0;
	if (l <= b && e <= r) return node->ans;
	Long me = (b + e) >> 1;
	Long q1 = node->left? query(node->left, b, me, l, r): 0;
	Long q2 = node->right? query(node->right, me + 1, e, l, r): 0;
	return q1 + q2;
}

Node *tree = new Node;