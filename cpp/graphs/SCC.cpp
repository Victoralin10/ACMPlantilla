const int N = 2 * (int)5e4 + 4; // for 2-sat must be twice as the max number of variables

// tested on https://codeforces.com/gym/100430/problem/A
struct DirectedGraph {
    // inputs
    int n = 0;
    vector<int> G[ N + 5 ];
    vector<int> dag[ N + 5 ];
    
    // internals
    int timer , top;
    int dfsn[ N + 5 ] , pila[ N + 5 ] , inpila[ N + 5 ];
    
    // output
    int comp[ N + 5 ];

    DirectedGraph() {}

    void init(int _n) {
        REP (i, n) G[i].clear();
        n = _n;
    }

    void addEdge(int from , int to) {
        G[from].push_back(to);
    }

    int dfs( int u ){
        int low = dfsn[ u ] = ++timer;
        inpila[ pila[ top ++ ] = u ] = 1;
        for( int v : G[ u ] ){
            if( dfsn[ v ] == 0 ) low = min( low , dfs( v ) );
            else if( inpila[ v ] ) low = min( low , dfsn[ v ] );
        }
        if( low == dfsn[ u ] ){
            int fin;
            do{
                fin = pila[ --top ];
                inpila[ fin ] = 0;
                comp[ fin ] = u;
            }while( fin != u );
        }
        return low;
    }

    void SCC(){
        CLR( dfsn , 0 );
        top = timer = 0;
        REP( i , n ) if( !dfsn[ i ] ) dfs( i );
    }

    void buildSccDag() {
        REP (i, n) dag[i].clear();
        REP (u, n)for( auto v : G[ u ] ){
            int i = comp[ u ] , j = comp[ v ];
            if( i != j ) dag[ i ].push_back( j );
        }
    }
}dg;