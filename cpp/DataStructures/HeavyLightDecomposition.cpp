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

void buildST(int node, int b, int e, int id) {}

void update(int node, int b, int e, int pos, int new_val, int id) {}

int query(int node, int b, int e, int l, int r, int id) {}

/************************************/
void updateGraph(int u, int newVal) {
	int id = idChain[u];
	int pos = posInChain[u];
	update(1, 0, chain[id].size() - 1, pos, newVal, id);
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
	for (int id = 0; id < nroChain; id ++) {
		int size = chain[id].size();
		tree[id] = vInt(size << 2);
		buildST(1, 0, size - 1, id);
	}
}

/************************************/
void Clear(int n) {
	tree.clear();
	chain.clear();
	nroChain = 0;
	for (int u = 1; u <= n; u ++) {
		adj[u].clear();
		heavy[u] = 0;
	}
}

/************************************/
int num[N];

int main() {
	int t, n;
	int u, v;
	cin >> t;
	while (t --) {
		cin >> n;
		Clear(n);
		for (int i = 1; i <= n; i ++) {
			scanf("%d", &num[i]);
		}
		for (int i = 1; i < n; i ++) {
			scanf("%d %d", &u, &v);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		HeavyLight(n);
		buildTrees();
		int q, type;
		cin >> q;
		int newVal;
		while (q --) {
			scanf("%d", &type);
			if (type == 1) {
				scanf("%d %d", &u, &newVal);
				updateGraph(u, newVal);
			}
			if (type == 2) {
				scanf("%d %d", &u, &v);
				printf("%d\n", queryGraph(u, v));
			}
		}
	}

	return 0;
}