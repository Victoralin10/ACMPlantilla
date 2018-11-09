/************************************/
vector<int> adj[ N ] ;
bool vis[ N ] ;
int tin[ N ] ;
int low[ N ] ;
int Time = 1 ;

stack<int> q ;
int id[ N ] ;
int nroC ;

void dfs( int from ) { // dfs(from, parent) {
	vis[ from ] = true ;
	tin[ from ] = low[ from ] = Time ++ ;
	q.push( from ) ;
	for( int to : adj[ from ] ) { // if (to == parent) continue;
		if( !tin[ to ] ) {
			dfs( to ) ; // dfs(to, from);
		}
		if( vis[ to ] ) {
			low[ from ] = min( low[ from ] , low[ to ] ) ;
		}
	}
	if( tin[ from ] == low[ from ] ) {
		while( true ) {
			int v = q.top() ;
			q.pop() ;
			id[ v ] = nroC ;
			vis[ v ] = false ;
			if( from == v ) {
				break ;
			}
		}
		nroC ++ ;
	}
}

void Tarjan( int n ) {
	for( int i = 1 ; i <= n ; i ++ ) {
		if( tin[ i ] ) continue ;
		dfs( i ) ; // dfs(i, 0)
	}
}

/************************************/
//undirected