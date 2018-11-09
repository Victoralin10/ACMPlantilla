typedef pair<int,int> Pair ;

/*****************************/
vector<int> adj[ N ] ;
bool vis[ N ] ;
int tin[ N ] ;
int low[ N ] ;
int Time ;
stack<Pair> edges ;

vector<Pair> E[ N ] ;
int nroBC ;

void dfs( int from , int fat ) {
	vis[ from ] = true ;
	tin[ from ] = low[ from ] = Time ++ ;
	int cantChild = 0 ;
	for( int to : adj[ from ] ) {
		if( to == fat ) continue ;
		if( !vis[ to ] ) {
			cantChild ++ ;
			edges.push( { from , to } ) ;
			dfs( to , from ) ;
			low[ from ] = min( low[ from ] , low[ to ] ) ;
			if( ( fat && tin[ from ] <= low[ to ] ) || ( !fat && cantChild > 1 ) ) {
				while( edges.top().first != from && edges.top().second != to ) {
					E[ nroBC ].push_back( edges.top() ) ;
					edges.pop() ;
				}
				E[ nroBC ].push_back( edges.top() ) ;
				edges.pop() ;
				nroBC ++ ;
			}
		} else {
			if( tin[ to ] < low[ from ] ) {
				low[ from ] = tin[ to ] ;
				edges.push( { from , to } ) ;
			}
		}
	}
}

void buildBC( int n ) {
	for( int i = 1 ; i <= n ; i ++ ) {
		if( vis[ i ] ) continue ;
		dfs( i , 0 ) ;
		for( ; !edges.empty() ; edges.pop() ) {
			E[ nroBC ].push_back( edges.top() ) ;
		}
		nroBC ++ ;
	}
}

/*****************************/

int main() {
    int n , m ;
    cin >> n >> m ;
    int u , v ;
    while( m -- ) {
		scanf( "%d %d" , &u , &v ) ;
		adj[ u ].push_back( v ) ;
		adj[ v ].push_back( u ) ;
	}
	buildBC( n ) ;
	for( int i = 0 ; i < nroBC ; i ++ ) {
		set<int> nodes ;
		for( Pair edge : E[ i ] ) {
			nodes.insert( edge.first ) ;
			nodes.insert( edge.second ) ;
		}
	}

    return 0 ;
}