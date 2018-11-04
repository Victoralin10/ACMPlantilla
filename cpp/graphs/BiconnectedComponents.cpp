// tested on http://codeforces.com/gym/101462/problem/D

const int N = (int)1e5 + 5;
const int M = (int)1e5 + 5;

// finding the 2-vertex-connected components (BCC, biconnected components)
// k-vertex-connected: has more than k vertices and
//     if you remove less than k vertices the component remains connected
// for practical purposes, we will consider a bridge as a BCC in this algorithm
struct Graph {
    // INPUTS
    int n = 0; // nodes

    // internals for the graph
    int m = 0;
    vector<int> E[N + 1]; // edges
    int orig[M + 1], dest[M + 1];

    // internals for BCC algorithm
    int pila[M + 1], top, fin;
    int low[N + 1], timer;
    int dfsn[N + 1]; // dfs arrival time

    // OUTPUTS
    // artp: articulation point (its removal from the graph increases the
    //       number of connected components)
    // bridge: edge that when removed increases the number of connected components
    int bicomp[M + 1], nbicomp;
    bool bridge[M + 1], artp[N + 1]; 

    Graph() {
    }

    void clear(int n) {
        REP (i, n) E[i].clear();
        m = 0;
        this -> n = n;
    }

    int otherVertex(int e, int u) {
        return orig[e] == u? dest[e] : orig[e];
    }

    // it supports multiple edges
    void addEdge(int a, int b) {
        orig[m] = a;
        dest[m] = b;
        E[a].push_back(m);
        E[b].push_back(m);
        m++;
    }

    int dfsbcc (int u, int p = -1){
        low[u] = dfsn[u] = ++timer;
        int ch = 0;
        for( auto e : E[ u ] ){
            int v = otherVertex(e, u);
            if (dfsn[v] == 0){
                pila[top++] = e;
                dfsbcc (v, e);
                low[u] = min (low[u], low[v]);
                ch++;
                if (low[v] >= dfsn[u]){
                    artp[u] = 1;
                    do {
                        fin = pila[--top];
                        bicomp[fin] = nbicomp;
                    } while (fin != e);
                    nbicomp++;
                }
                if (low[v] == dfsn[v]) bridge[e] = 1;
            } else if (e != p && dfsn[v] < dfsn[u]){
                pila[top++] = e;
                low[u] = min (low[u], dfsn[v]);
            }
        }
        return ch;
    }
    void bcc (){
        REP( i , n ) artp[ i ] = dfsn[ i ] = 0;
        REP( i , m ) bridge[ i ] = 0;
        fin = top = nbicomp = timer = 0;
        REP( i , n ) if (dfsn[ i ] == 0) artp[ i ] = dfsbcc( i ) >= 2;
    }
}graph;