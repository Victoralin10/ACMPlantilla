// tested on https://open.kattis.com/problems/allpairspath

const int MAXV = (int)155;

Long dis[MAXV][MAXV];
int edges, nodes, q;
const Long INF = 150 * 1000 * 2;

void init() {
    REP (i, nodes) {
        REP (j, nodes) {
            dis[i][j] = INF;
        }
        dis[i][i] = 0;
    }
}

void floydWarshall() {
    REP (k, nodes) {
        REP (i, nodes) {
            REP (j, nodes) {
                if (dis[i][k] != INF && dis[k][j] != INF &&
                    dis[i][j] > dis[i][k] + dis[k][j]) {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
}

int main() {
    int q;
    while (scanf("%d%d%d", &nodes, &edges, &q) == 3) {
        if (nodes == 0) break;

        init();

        REP (i, edges) {
            int a, b;
            int w;
            sc(a); 
            sc(b);
            sc(w);
            dis[a][b] = min(dis[a][b], (Long)w);
        }

        floydWarshall();

        // detecting negative cycles
        REP (i, nodes) {
            REP (j, nodes) {
                REP (k, nodes) {
                    // there is a negative cycle passing by k and there is connectivity from i to k and from k to j
                    if (dis[k][k] < 0 && dis[i][k] != INF && dis[k][j] != INF) {
                        dis[i][j] = -INF;
                    }
                }
            }
        }

        REP (i, q) {
            int from, to;
            sc(from);
            sc(to);
            if (dis[from][to] == -INF) {
                puts("-Infinity");
            } else if (dis[from][to] == INF) {
                puts("Impossible");
            } else {
                printf("%d\n", (int)dis[from][to]);
            }
        }
        puts("");
    }
}