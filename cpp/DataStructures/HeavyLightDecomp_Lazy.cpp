#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 2;
const int INF = 1e9 + 7;

vector<int> adj[N];

/************************************/
typedef vector<int> vInt;
typedef vector<vInt> vvInt;

int depth[N];
int parent[N];
int heavy[N];

int dfs(int from, int parent_, int level) {
	depth[from] = level;
	parent[from] = parent_;
	int size = 1;
	int max_size_ST = 0;
	for (int to: adj[from]) {
		if (to == parent_) continue;
		int size_ST = dfs(to, from, level + 1);
		size += size_ST;
		if (max_size_ST < size_ST) {
			max_size_ST = size_ST;
			heavy[from] = to;
		}
	}
	return size;
}

vvInt chain;
int root[N];
int posInChain[N];
int idChain[N];
int nroChain;

void HeavyLight(int n) {
	dfs(1, 0, 0);
	for (int u = 1; u <= n; u ++) {
		if (heavy[parent[u]] == u) continue;
		int pos = 0;
		chain.push_back(vInt());
		for (int v = u; v; v = heavy[v]) {
			root[v] = u;
			posInChain[v] = pos ++;
			idChain[v] = nroChain;
			chain[nroChain].push_back(v);
		}
		nroChain ++;
	}
}

/************************************/
vvInt tree;
vvInt lazy;
#define LEFT(x) (2*x)
#define RIGHT(x) (2*x + 1)

void aplicate(int node, int b, int e, int id) {
	if (!lazy[id][node]) return;
	tree[id][node] += (e - b + 1)*lazy[id][node];
	if (b != e) {
		int leftChild = LEFT(node), rightChild = RIGHT(node);
		lazy[id][leftChild] += lazy[id][node];
		lazy[id][rightChild] += lazy[id][node];
	}
	lazy[id][node] = 0;
}

void update(int node, int b, int e, int l, int r, int add, int id) {
	aplicate(node, b, e, id) ;
	if (r < b || e < l) return ;
	if (l <= b && e <= r) {
		lazy[id][node] = add;
		aplicate(node, b, e, id);
		return ;
	}
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	update(leftChild, b, me, l, r, add, id);
	update(rightChild, me + 1, e, l, r, add, id);
	tree[id][node] = tree[id][leftChild] + tree[id][rightChild];
}

int query(int node, int b, int e, int l, int r, int id) {
	if (r < b || e < l) return 0;
	aplicate(node, b, e, id);
	if (l <= b && e <= r) return tree[id][node];
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	int q1 = query(leftChild, b, me, l, r, id);
	int q2 = query(rightChild, me + 1, e, l, r, id);
	return q1 + q2;
}

/************************************/
void updateTree(int id, int u, int v, int add) {
	int l = posInChain[u], r = posInChain[v];
	update(1, 0, chain[ id ].size() - 1, l, r, add, id);
}

void updateGraph(int u, int v, int add) {
	int ans = 0;
	for ( ; root[u] != root[v]; v = parent[root[v]]) {
		if (depth[root[u]] > depth[root[v]]) swap(u, v);
		updateTree(idChain[v], root[v], v, add);
	}
	if (depth[u] > depth[v]) swap(u, v);
	updateTree(idChain[v], u, v, add);
}

int queryTree(int id, int u, int v) {
	int l = posInChain[u], r = posInChain[v];
	return query(1, 0, chain[id].size() - 1, l, r, id);
}

int queryGraph(int u, int v) {
	int ans = 0;
	for ( ; root[u] != root[v]; v = parent[root[v]]) {
		if (depth[root[u]] > depth[root[v]]) swap(u, v);
		ans += queryTree(idChain[v], root[v], v);
	}
	if (depth[u] > depth[v]) swap(u, v);
	ans += queryTree(idChain[v], u, v);
	return ans;
}

/************************************/
void buildTrees() {
	tree = vvInt(nroChain);
	lazy = vvInt(nroChain);
	for (int id = 0; id < nroChain; id ++) {
		int size = chain[id].size();
		tree[id] = vInt(size << 2);
		lazy[id] = vInt(size << 2);
	}
}

/************************************/

int main() {
	int n, q;
	cin >> n >> q;
	int u, v, k;
	for (int i = 1; i < n; i ++) {
		scanf("%d %d", &u, &v) ;
		u ++, v ++;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	HeavyLight(n);
	buildTrees();
	while ( q -- ) {
		scanf("%d %d %d", &u, &v, &k);
		u ++, v ++;
		updateGraph(u, v, k) ;
	}
	int ans = 0;
	for (int u = 1; u <= n; u ++) {
		ans = max(ans, queryGraph(u , u)) ;
	}
	cout << ans;

	return 0;
}