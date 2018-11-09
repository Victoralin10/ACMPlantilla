typedef pair<int,int> Pair ;

/************************************/
vector<int> adj[ N ] ;
bool vis[ N ] ;
int tin[ N ] ;
int low[ N ] ;
int Time ;

int cantChild[ N ] ;
bool isCut[ N ] ;
vector<Pair> bridges ;

void dfs( int from , int fat ) {
	vis[ from ] = true ;
	tin[ from ] = low[ from ] = Time ++ ;
	for( int to : adj[ from ] ) {
		if( to == fat ) continue ;
		if( !vis[ to ] ) {
			cantChild[ from ] ++ ;
			dfs( to , from ) ;
			low[ from ] = min( low[ from ] , low[ to ] ) ;
			if( low[ to ] > tin[ from ] ) {
				bridges.push_back( { from , to } ) ;
			}
			if( tin[ from ] <= low[ to ] ) {
				isCut[ from ] = true ;
			}
		}
		low[ from ] = min( low[ from ] , tin[ to ] ) ;
	}
}

void Articulation( int n ) {
	for( int i = 1 ; i <= n ; i ++ ) {
		if( vis[ i ] ) continue ;
		dfs( i , 0 ) ;
		isCut[ i ] = cantChild[ i ] > 1 ;
	}
}