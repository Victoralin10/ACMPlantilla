vector<int> adj[N];
int depth[N];
int st[N][logN];

void dfs(int from, int parent, int level) {
	depth[from] = level;
	st[from][0] = parent;
	for (int to: adj[from]) {
		if (to == parent) continue;
		dfs(to, from, level + 1);
	}
}

void buildST(int n) {
	dfs(1, 0, 0);
	for (int loglen = 1, len = 2; len <= n; loglen ++, len <<= 1) {
		for (int u = 1; u <= n; u ++) {
			if (!st[u][loglen]) continue;
			int v = st[u][loglen - 1];
			st[u][loglen] = st[v][loglen - 1];
		}
	}
}

int lca(int u, int v) {
	if (depth[u] < depth[v]) swap(u, v);
	int limit = log2(depth[u]) + 1;
	int len = 1 << limit;
	for (int loglen = limit; loglen >= 0; loglen --, len >>= 1) {
		if (depth[u] - len >= depth[v]) {
			u = st[u][loglen];
		}
	}
	if (u == v) return u;
	for(int loglen = limit; loglen >= 0; loglen --) {
		if (!st[u][loglen]) continue;
		if (st[u][loglen] != st[v][loglen]) {
			u = st[u][loglen];
			v = st[v][loglen];
		}
	}
	return st[u][0];
}