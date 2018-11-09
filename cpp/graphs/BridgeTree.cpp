typedef pair<int,int> Pair ;

/************************************/
int F[ N ] ;

int find( int u ) {
	if( !F[ u ] ) return u ;
	return F[ u ] = find( F[ u ] ) ;
}

void Union( int u , int v ) {
	u = find( u ) ;
	v = find( v ) ;
	if( u == v ) return ;
	F[ v ] = u ;
}

/************************************/
vector<Pair> adj[ N ] ;
bool vis[ N ] ;
int tin[ N ] ;
int low[ N ] ;
int Time ;

bool bridge[ N ] ;

void dfs( int from , int fat ) {
	vis[ from ] = true ;
	tin[ from ] = low[ from ] = Time ++ ;
	for( Pair edge : adj[ from ] ) {
		int to = edge.first ;
		int nroB = edge.second ;
		if( to == fat ) continue ;
		if( !vis[ to ] ) {
			dfs( to , from ) ;
			low[ from ] = min( low[ from ] , low[ to ] ) ;
			if( tin[ from ] < low[ to ] ) {
				bridge[ nroB ] = true ;
			}
		}
		low[ from ] = min( low[ from ] , tin[ to ] ) ;
	}
}

void Articulation( int n ) {
	for( int i = 1 ; i <= n ; i ++ ) {
		if( vis[ i ] ) continue ;
		dfs( i , 0 ) ;
	}
}

/***********************************/
vector<int> adj2[ N ] ;
Pair E[ N ] ;

void buildBT( int m ) {
	for( int i = 0 ; i < m ; i ++ ) {
		if( bridge[ i ] ) continue ;
		int u = E[ i ].first ;
		int v = E[ i ].second ;
		Union( u , v ) ;
	}
	for( int i = 0 ; i < m ; i ++ ) {
		if( !bridge[ i ] ) continue ;
		int u = find( E[ i ].first ) ;
		int v = find( E[ i ].second ) ;
		adj2[ u ].push_back( v ) ;
		adj2[ v ].push_back( u ) ;
	}
}

/***********************************/

int main() {
	int n , m ;
	cin >> n >> m ;
	int u , v ;
	for( int i = 0 ; i < m ; i ++ ) {
		scanf( "%d %d" , &u , &v ) ;
		adj[ u ].push_back( { v , i } ) ;
		adj[ v ].push_back( { u , i } ) ;
		E[ i ] = { u , v } ;
	}
	Articulation( n ) ;
	buildBT( m ) ;
	
	return 0 ;
}