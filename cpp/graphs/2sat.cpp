
// tested on https://codeforces.com/gym/100430/problem/A

// you need the SCC struct with a dg instance

//Consider f=(x1 or y1) and (x2 or y2) and ...  and (xn or yn).
// All you need is to add condictions with addClause

// remember: 
// x == true  is  x or x
// x == false  is  !x or !x
// x != y is (x or y) and (!x or !y)
// x == y is (!x or y) and (!y or x)


struct TwoSat { // 2-sat 
    int n = 0; // number of variables
    
    // internals
    int vis[ N + 5 ], cola[ N + 5 ], sz;

    // outputs
    int decision[ N + 5 ];

    TwoSat() {}
    void init(int _n) {
        n = _n;
        dg.init(2 * n);
    }
    int getVar(bool s, int x) {
        if (s) return 2 * x; // even
        return 2 * x + 1;
    }
    int neg(int var) { // not
        return var ^ 1;
    }

    // adds a clause
    void addClause(bool xsign, int x, bool ysign, int y) { // or-clause
        ///Now consider a graph with 2n vertices; For each of (xi ∨ yi) s we add two directed edges
        //From !xi to yi
        //From !yi to xi
        
        int a = getVar(xsign, x);
        int b = getVar(ysign, y);
        dg.addEdge(neg(a), b);
        dg.addEdge(neg(b), a);
    }

    // checks wether a solution exists
    bool solve() {
        dg.SCC();
        REP( i , n ) {
            if( dg.comp[ getVar(1, i) ] == dg.comp[ getVar(0, i) ] ){
                return 0;
            }
        }
        return 1;
    }

    void topsort( int u ){
        vis[ u ] = 1;
        for( auto v : dg.dag[ u ] )
            if( !vis[ v ] ) topsort( v );
        cola[ sz ++ ] = u;
    }
    void paint( int u ){
        decision[ u ] = 1;
        for( auto v : dg.dag[ u ] )
            if( decision[ v ] == -1 ) paint( v );
    }

    /**
     * This assigns a boolean value (decision) to all dag components (not values)
     * You may call it only if a solution exists.
     * **/
    void rebuild() {
        dg.buildSccDag();
        REP( i , 2 * n ) vis[ i ] = 0;
        sz = 0;
        REP( i , 2 * n ) if( dg.comp[ i ] == i && !vis[ i ] ) topsort( i );
        REP( i , 2 * n ) decision[ i ] = -1;
        reverse( cola , cola + sz );
        REP( i , sz )
            if( decision[ cola[ i ] ] == -1 ){
                decision[ cola[ i ] ] = 0;
                paint( dg.comp[ cola[ i ] ^ 1 ] );
            }
    }

    // use only after calling rebuild
    bool getValueForVariable(int x) {
        return decision[dg.comp[getVar(1, x)]];
    }
}ts;

int color[N]; // color per wire
pair<int, int> sockets[N]; // sockets per wire

int main() {
	freopen( "chip.in" , "r" , stdin );
	freopen( "chip.out" , "w" , stdout );
    int n;
    while (sc(n) == 1) {
        REP (i, n) {
            sc(color[i]);
            sockets[i] = {-1, -1};
        }
        ts.init(n);

        int firstWire;
        bool firstSign;
        int lastWire;
        bool lastSign;
        REP (i, 2 * n) {
            int w;
            sc(w);
            w--;

            bool mySign;
            if (sockets[w].first == -1) {
                sockets[w].first = i;
                mySign = 0;
            } else {
                sockets[w].second = i;
                mySign = 1;
            }

            if (i == 0) {
                firstWire = w;
                firstSign = mySign;
            } else {
                if (color[lastWire] == color[w]) {
                    ts.addClause(!lastSign, lastWire, !mySign, w);
                }
            }

            lastSign = mySign;
            lastWire = w;
        }
        if (color[lastWire] == color[firstWire]) {
            ts.addClause(!lastSign, lastWire, !firstSign, firstWire);
        }

        bool hasSolution = ts.solve();
        if (!hasSolution) {
            puts("NO");
        } else {
            puts("YES");
            ts.rebuild();

            REP (i, n) {
                bool isSecond = ts.getValueForVariable(i);
                int socket;
                if (!isSecond) {
                    socket = sockets[i].first;
                } else {
                    socket = sockets[i].second;
                }
                socket++;
                if (i) putchar(' ');
                printf("%d", socket);
            }
            puts("");
        }
    }
}