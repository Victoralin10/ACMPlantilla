#include <bits/stdc++.h>
using namespace std;

const int N = 6e5 + 2;
const int INF = 1e9 + 0;

int Pot[10];

/************************************/
struct Node {
	Node *child[10];
	int cant;
	Node() {
		cant = 0;
		for (int i = 0; i < 10; i ++) {
			child[i] = NULL;
		}
	}
	Node (Node* node) {
		cant = node->cant;
		for (int i = 0; i < 10; i ++) {
			child[i] = node->child[i];
		}
	}
};

Node *trie[N];
Node *null;

Node* insert(Node *node, int num, int it = 9) {
	Node* trie = new Node(node);
	trie->cant ++;
	if (it < 0) return trie;
	int digit = (num/Pot[it])%10;
	if (!trie->child[digit]) {
		trie->child[digit] = new Node;
	}
	trie->child[digit] = insert(trie->child[digit], num, it - 1);
	return trie;
}

int query(Node *node1, Node *node2, int num, bool less, int it = 9) {
	if (less || it < 0) return node2->cant - node1->cant;
	int digit = (num/Pot[it])%10, ans = 0;
	for (int i = 0; i <= digit; i ++) {
		ans += query(node1->child[i], node2->child[i], num, (i < digit)|less, it - 1);
	}
	return ans;
}

/************************************/
void init() {
	null = new Node;
	for (int i = 0; i < 10; i ++) {
		null->child[i] = null;
	}
	trie[0] = null;
}

void buildP10() {
	Pot[0] = 1;
	for (int i = 1; i < 10; i ++) {
		Pot[i] = Pot[i - 1]*10;
	}
}

int main() {
	buildP10();
	init();
	int q, type;
	cin >> q;
	int pos = 0;
	int l, r, num;
	while (q --) {
		scanf("%d", &type);
		if (type == 1) {
			scanf("%d", &num);
			trie[++ pos] = insert(trie[pos - 1], num);
			continue;
		}
		scanf("%d %d %d", &l, &r, &num);
		int a, b;
		if (type == 2) a = 0, b = num - 1;
		if (type == 3) a = num - 1, b = num;
		if (type == 4) a = num, b = INF;
		int q2 = query(trie[l - 1], trie[r], b, false);
		int q1 = query(trie[l - 1], trie[r], a, false);
		printf("%d\n", q2 - q1);
	}

	return 0;
}