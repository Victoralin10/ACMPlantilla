// tested on http://codeforces.com/contest/20/problem/C

const int MAXE = (int)1e5 + 5;
const int MAXV = (int)1e5 + 5;

vector<int> adj[MAXV]; // adjacent edges
int to[2 * MAXE]; // to
Long weight[2 * MAXE]; // weight
Long dis[MAXV];
int parent[MAXV];
int edges = 0;

void addDirectedEdge(int u, int v, Long w) {
    adj[u].push_back(edges++);
    to[edges - 1] = v;
    weight[edges - 1] = w;
}
void addUndirectedEdge(int u, int v, Long w) {
    addDirectedEdge(u, v, w);
    addDirectedEdge(v, u, w);
}

// O ( (E + V) * log(V) )
Long dijkstra(int source, int target) {
    priority_queue<pair<Long, int> > pq; // weight, vertex
    CLR(dis, -1);
    CLR(parent, -1);

    dis[source] = 0;
    pq.push({0, source});
    parent[source] = source;

    while (!pq.empty()) {
        auto nnp = pq.top();
        pq.pop();
        Long nndist = -nnp.first;
        int nn = nnp.second;

        if (nndist > dis[nn]) continue; // to save time ignoring improved nodes (which are already in the heap)

        if (nn == target) break;

        for (int i = 0; i < (int)adj[nn].size(); i++) {
            int e = adj[nn][i]; // edge
            int son = to[e];
            Long w = weight[e];
            Long dson = nndist + w;
            if (dis[son] == -1 || dis[son] > dson) {
                dis[son] = dson;
                parent[son] = nn; // only saving the first shortest path found
                pq.push({-dson, son});
            }
        }
    }

    return dis[target];
}


int main() {
    int n, m;
    sc(n);
    sc(m);
    REP (i, m) {
        int a, b, w;
        sc(a);
        sc(b);
        sc(w);
        a--;
        b--;
        addUndirectedEdge(a, b, w);
    }
    Long ans = dijkstra(0, n - 1);
    if (ans != -1) {
        int p = n - 1;
        vector<int> path;
        path.push_back(p);
        while (p != parent[p]) {
            p = parent[p];
            path.push_back(p);
        }
        reverse(ALL(path));
        REP (i, SZ(path)) {
            if (i) putchar(' ');
            printf("%d", path[i] + 1);
        }
        puts("");
    } else {
        puts("-1");
    }
}