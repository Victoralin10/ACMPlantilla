struct Node {
	Node *left = NULL;
	Node *right = NULL;
	int cant = 0;
	Node() {}
	Node(int cant, Node *l, Node *r):
		cant(cant), left(l), right(r) {}
};

Node *tree[N];
Node *null;

Node* insert(Node *node, int b, int e, int pos) {
	if (pos < b || e < pos) return node;
	if (b == e) return new Node(node->cant + 1, null, null);
	int me = (b + e) >> 1;
	Node *l = insert(node->left, b, me, pos);
	Node *r = insert(node->right, me + 1, e, pos);
	return new Node(node->cant + 1, l, r);
}

int query2(Node *node1, Node *node2, int b, int e, int l, int r) {
	if (r < b || e < l) return 0;
	if (l <= b && e <= r) return node1->cant - node2->cant;
	int me = (b + e) >> 1;
	int q1 = query2(node1->left, node2->left, b, me, l, r);
	int q2 = query2(node1->right, node2->right, me + 1, e, l, r);
	return q1 + q2;
}

/************************************/
int num[N];

void buildTrees(int n) {
	null = new Node;
	null->left = null;
	null->right = null;
	tree[0] = null;
	for (int i = 1; i <= n; i ++) {
		tree[i] = insert(tree[i - 1], 0, INF, num[i]);
	}
}