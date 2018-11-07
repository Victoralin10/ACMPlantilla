vector<int> adj[N];
bool isCentroid[N];
int sizeST[N];

void build_subtrees(int from, int parent) {
	sizeST[from] = 1;
	for (int to: adj[from]) {
		if (to == parent) continue;
		if (isCentroid[to]) continue;
		build_subtrees(to, from);
		sizeST[from] += sizeST[to];
	}
}

int find_centroid(int from , int parent, int size_total) {
	for (int to: adj[from]) {
		if (to == parent) continue;
		if (isCentroid[to]) continue;
		if (sizeST[to] > size_total/2) {
			return find_centroid(to, from, size_total);
		}
	}
	return from;
}

int parentC[N];

int buildCT(int from) {
	build_subtrees(from, 0);
	int centroid = find_centroid(from, 0, sizeST[from]);
	isCentroid[centroid] = true;
	for (int to: adj[centroid]) {
		if (!isCentroid[to]) {
			int centroid_ = buildCT(to);
			parentC[centroid_] = centroid;
		}
	}
	return centroid;
}