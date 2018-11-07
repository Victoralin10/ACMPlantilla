// tested in at least 4 problems
struct flowGraph{
    // O (E * V ^ 2) => but you can expect a lot less in practice (up to 100 times better)
	// O (E * sqrt(V)) => on bipartite graphs or unit flow through nodes
    // O (min(V ^ (2/3), sqrt(E)) * E) => in network with unit capacities
	// memory = O(E + V)

	/**
	
	On bipartite graphs:
	//maximum independent set + maxflow = nodes
	//maximum independent set = minimun edge cover
	//maxflow = minimum vertex cover 
	Grafos bipartitos:
	Any tree is 2-colorable.
	The following are equivalent:
	1. G is bipartite.
	2. G is 2-colorable.
	3. G has no cycles of odd length.

	Reconstruccion de Vertex Cover en grafo bipartito:
	DFS the residual graph and mark those nodes you visit,
	Answer is the nodes on the left that you don't visit and
	the nodes on the right that you visit.

	Reconstrucción del Min-Cut:
	Hacer un BFS o DFS desde s (source) sobre el grafo residual y todos los nodos 
	visitados serán parte del corte de s, las aristas que entren a alguno de estos nodos
	pero no hayan sido visitados por el DFS serán las que forman parte del corte.

	Dilworth Theorem(Max antichain = Min path cover)
	How to find a maxim chain
	OJO : El grafo tiene que ser un dag.


	*/
	typedef Long flowtype;
    const flowtype INF = (flowtype)2e10;
	const int bfsINF = (1<<28);
	int n , m , s , t , E;
	vector<int> to , NEXT;//maxe * 2
	vector<flowtype> cap; //maxe * 2
	vector<int> last, now , dist;// maxv
	flowGraph(){}
	flowGraph( int n , int m , int s , int t ) {
		init(n, m, s, t);
	}
	void init( int n , int m , int s , int t ) {
		this->n = n;
		this->m = m;
		this->s = s;
		this->t = t;
		cap = vector<flowtype>( 2 * m + 5 );
		to = NEXT = vector<int>( 2 * m + 5 );
		now = dist = vector<int>( n + 5 );
		E = 0;
		last = vector<int>( n + 5 , -1 );
	}
	void add( int u , int v , flowtype uv , flowtype vu = 0 ){
		to[ E ] = v ; cap[ E ] = uv ; NEXT[ E ] = last[ u ] ; last[ u ] = E ++;
		to[ E ] = u ; cap[ E ] = vu ; NEXT[ E ] = last[ v ] ; last[ v ] = E ++;
	}
	bool bfs(){
		REP( i , n ) dist[ i ] = bfsINF;
		queue< int > Q;
		dist[ t ] = 0;
		Q.push( t );
		while( !Q.empty() ){
			int u = Q.front() ; Q.pop();
			for( int e = last[ u ] ; e != -1 ; e = NEXT[ e ] ){
				int v = to[ e ];
				if( cap[ e ^ 1 ] && dist[ v ] >= bfsINF ){
					dist[ v ] = dist[ u ] + 1;
					Q.push( v );
				}
			}
		}
		return dist[ s ] < bfsINF;
	}
	flowtype dfs( int u , flowtype f ){
		if( u == t ) return f;
		for( int &e = now[ u ] ; e != -1 ; e = NEXT[ e ] ){
			int v = to[ e ];
			if( cap[ e ] && dist[ u ] == dist[ v ] + 1 ){
				flowtype ret = dfs( v  , min( f , cap[ e ] ) );
				if( ret ){
					cap[ e ] -= ret;
					cap[ e ^ 1 ] += ret;
					return ret;
				}
			}
		}
		return 0;
	}
	
	flowtype maxFlow(){
		flowtype flow = 0;
		while( bfs() ){
			REP( i , n ) now[ i ] = last[ i ];
			while( 1 ){
				flowtype f = dfs( s , INF );
				if( !f ) break;
				flow += f;
			}
		}
		return flow;
	}
	
	/**
	 * Gets residual capacity per edge
	 * **/
	vector<pair<pair<int, int>, flowtype> > getResPerEdge() {
		vector<pair<pair<int, int>, flowtype> > res;
		REP (u, n) {
			for( int e = last[ u ] ; e != -1 ; e = NEXT[ e ] ) {
				int v = to[ e ];
				res.push_back(make_pair(make_pair(u, v), cap[e]));
			}
		}
		return res;
	}
}fg;