typedef pair<int,int> Pair ;
typedef vector<Pair> vPair ;

/************************************/
vPair adj[ N ] ;

struct orden {
	bool operator () ( Pair p1 , Pair p2 ) {
		return p1.second > p2.second ;
	}
} ;

void dijkstra( int node , int n , int *dist ) {
	for( int i = 0 ; i <= n ; i ++ ) {
		dist[ i ] = INF ;
	}
	dist[ node ] = 0 ;
	priority_queue<Pair,vPair,orden> q ;
	q.push( { node , 0 } ) ;
	while( !q.empty() ) {
		Pair t = q.top() ;
		q.pop() ;
		int a = t.first ;
		int da = t.second ;
		if( dist[ a ] < da ) continue ;
		for( Pair edge : adj[ a ] ) {
			int b = edge.first ;
			int cost = edge.second ;
			if( dist[ b ] > dist[ a ] + cost ) {
				dist[ b ] = dist[ a ] + cost ;
				q.push( { b , dist[ b ] } ) ;
			}
		}
	}
}

/************************************/

bool bellmon( int node , int n , int *dist ) {
	for( int u = 0 ; u <= n ; u ++ ) {
		dist[ u ] = INF ;
	}
	dist[ node ] = 0 ;
	for( int i = 1 ; i < n ; i ++ ) {
		for( int u = 1 ; u <= n ; u ++ ) {
			for( Pair edge : adj[ u ] ) {
				if( dist[ u ] == INF ) continue ;
				if( dist[ edge.first ] > dist[ u ] + edge.second ) {
					dist[ edge.first ] = dist[ u ] + edge.second ;
				}
			}
		}
	}
	for( int u = 1 ; u <= n ; u ++ ) {
		for( Pair edge : adj[ u ] ) {
			if( dist[ u ] == INF ) continue ;
			if( dist[ edge.first ] > dist[ u ] + edge.second ) {
				return true ;
			}
		}
	}
	return false ;
}

/************************************/
int dist[ N ][ N ] ;
int dS[ N ] ;

bool Johnson( int n ) {
	int root = n + 1 ;
	for( int i = 1 ; i <= n ; i ++ ) {
		adj[ root ].push_back( { i , 0 } ) ;
	}
	if( bellmon( root , n + 1 , dS ) ) {
		return false ;
	}
	for( int i = 1 ; i <= root ; i ++ ) {
		for( Pair &edge : adj[ i ] ) {
			edge.second += dS[ i ] - dS[ edge.first ] ;
		}
	}
	for( int i = 1 ; i <= n ; i ++ ) {
		dijkstra( i , n , dist[ i ] ) ;
	}
	for( int u = 1 ; u <= n ; u ++ ) {
		for( int v = 1 ; v <= n ; v ++ ) {
			if( dist[ u ][ v ] == INF ) continue ;
			dist[ u ][ v ] += dS[ v ] - dS[ u ] ;
		}
	}
	return true ;
}