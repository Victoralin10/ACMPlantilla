// tested on https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=165&page=show_problem&problem=499

const int MAXE = (int)2e3 + 3;
const int MAXV = (int)1e3 + 3;

Long dis[MAXV];
pair<int, int> edge[MAXE];
Long weight[MAXE];
int edges, nodes, q;
const Long INF = (int)1e7;

// returns -1 if no vertex was relaxed
int relax(Long dis[MAXV]) {
    int lastRelaxed = -1;
    for (int i = 0; i < edges; i++) {
        int from = edge[i].first;
        int to = edge[i].second;
        Long w = weight[i];
        // INF check is not only for overflow when dis[from] = INF,
        // it is also for avoiding distances like INF - 1, INF -2, ... 
        if (dis[from] != INF && dis[to] > dis[from] + w) {
            dis[to] = max(dis[from] + w, -INF); // because distances may go far in the negative (- 2 ^ V)
            // save parent here p[to] = from;
            lastRelaxed = to;
        }
    }
    return lastRelaxed;
}

int main() {
    int tc;
    sc(tc);
    REP (itc, tc) {
        sc(nodes);
        sc(edges);

        REP (i, edges) {
            int a, b;
            int w;
            sc(a); 
            sc(b);
            sc(w);
            edge[i] = {a, b};
            weight[i] = w;
        }

        // bellman ford O(E * V)
        REP (i, nodes) {
            dis[i] = INF;
        }
        dis[0] = 0;
        REP (i, nodes - 1) {
            relax(dis);
        }
        // one more to check for negative cycles
        int lastRelaxed = relax(dis);
        
        if (lastRelaxed == -1) {
            puts("not possible");
        } else {
            puts("possible");
            // to rebuild the negative cycle closer to the source:
            // int y = lastRelaxed;
            // for (int i=0; i<n; ++i)
            //     y = p[y];

            // vector<int> path;
            // for (int cur=y; ; cur=p[cur])
            // {
            //     path.push_back (cur);
            //     if (cur == y && path.size() > 1)
            //         break;
            // }
            // reverse (path.begin(), path.end());

            // cout << "Negative cycle: ";
            // for (size_t i=0; i<path.size(); ++i)
            //     cout << path[i] << ' ';
        }
        // The above implementation looks for a negative cycle reachable from some starting vertex source; however, the algorithm can be modified to just looking for any negative cycle in the graph. For this we need to put all the distance d[i] to zero and not infinity — as if we are looking for the shortest path from all vertices simultaneously; the validity of the detection of a negative cycle is not affected.

        /*
            Solving a set of inequalities:
            Building the constraint graph:
                Each variable Xi corresponds to a node Vi
                Each constraint Xj - Xi <= bij corresponds to an
                edge from Xi to Xj with weight bij
                We add a special node V0 and we add edges from
                this special node to all other nodes. The weights of
                these edges are 0
                We run bellman ford with source V0.

            There are no negative cycles if and only if the set on inequalities has solution (the solution is the final distances)
        */
    }
}