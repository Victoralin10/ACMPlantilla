//https://www.spoj.com/problems/QTREE/
#include <bits/stdc++.h>
using namespace std;

const int N = 1e4 + 2;
const int INF = 1e9 + 7;

struct Edge {
	int to, cost, nro;
};

vector<Edge> adj[N];
int num[N];

/************************************/
typedef vector<int> vInt;
typedef vector<vInt> vvInt;

int depth[N];
int parent[N];
int heavy[N];
int node[N];

int dfs(int from, int parent_, int level) {
	depth[from] = level;
	parent[from] = parent_;
	int size = 1;
	int max_size_ST = 0;
	for (Edge edge: adj[from]) {
		int to = edge.to;
		if (to == parent_) continue;
		node[edge.nro] = to;
		num[to] = edge.cost;
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
#define LEFT(x) (2*x)
#define RIGHT(x) (2*x + 1)

void buildST(int node, int b, int e, int id) {
	if (b == e) {
		tree[id][node] = num[chain[id][b]];
		return;
	}
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	buildST(leftChild, b, me, id);
	buildST(rightChild, me + 1, e, id);
	tree[id][node] = max(tree[id][leftChild], tree[id][rightChild]);
}

void update(int node, int b, int e, int pos, int newVal, int id) {
	if (b == e) {
		tree[id][node] = newVal;
		return;
	}
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	if (pos <= me) update(leftChild, b, me, pos, newVal, id);
	else update(rightChild, me + 1, e, pos, newVal, id);
	tree[id][node] = max(tree[id][leftChild], tree[id][rightChild]);
}

int query(int node, int b, int e, int l, int r, int id) {
	if (r < b || e < l) return 0;
	if (l <= b && e <= r) return tree[id][node];
	int me = (b + e) >> 1;
	int leftChild = LEFT(node), rightChild = RIGHT(node);
	int q1 = query(leftChild, b, me, l, r, id);
	int q2 = query(rightChild, me + 1, e, l, r, id);
	return max(q1, q2);
}

/************************************/
void updateGraph(int u, int newVal) {
	int id = idChain[u];
	int pos = posInChain[u];
	update(1, 0, chain[id].size() - 1, pos, newVal, id);
}

int queryTree(int id, int u, int v, int down = 0) {
	int l = posInChain[u] + down, r = posInChain[v];
	return query(1, 0, chain[id].size() - 1, l, r, id);
}

int queryGraph(int u, int v) {
	int ans = -INF;
	for ( ; root[u] != root[v]; v = parent[root[v]]) {
		if (depth[root[u]] > depth[root[v]]) swap(u, v);
		ans = max(ans, queryTree(idChain[v], root[v], v));
	}
	if (depth[u] > depth[v]) swap(u, v);
	ans = max(ans, queryTree(idChain[v], u, v, 1));
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
char type[10];
int u, v, c;
int nroEdge, newVal;

int main() {
	int t, n;
	cin >> t;
	while (t --) {
		cin >> n;
		Clear(n);
		for (int i = 1; i < n; i ++) {
			scanf("%d %d %d", &u, &v, &c);
			adj[u].push_back({v, c, i});
			adj[v].push_back({u, c, i});
		}
		HeavyLight(n);
		buildTrees();
		while (true) {
			scanf("%s", type);
			if (type[0] == 'D') break;
			if (type[0] == 'Q') {
				scanf("%d %d", &u, &v);
				printf("%d\n", queryGraph(u, v));
			}
			if (type[0] == 'C') {
				scanf("%d %d", &nroEdge, &newVal);
				updateGraph(node[nroEdge], newVal);
			}
		}
	}

	return 0;
}