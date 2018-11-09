vector<int> adj[ N ] ;
bool vis[ N ] ;
stack<int> q ;

void dfs( int from ) {
	vis[ from ] = true ;
	for( int to : adj[ from ] ) {
		if( vis[ to ] ) continue ;
		dfs( to ) ;
	}
	q.push( from ) ;
}

void TS( int n ) {
	for( int i = 1 ; i <= n ; i ++ ) {
		sort( adj[ i ].rbegin() , adj[ i ].rend() ) ;
	}
	for( int i = n ; i >= 1 ; i -- ) {
		if( vis[ i ] ) continue ;
		dfs( i ) ;
	}
}