typedef pair<int,int> Pair ;

vector<Pair> adj[ N ] ;
int dist[ N ] ;
bool inq[ N ] ;
int cant[ N ] ;

bool SPFA( int node , int n ) {
	for( int i = 1 ; i <= n ; i ++ ) {
		dist[ i ] = INF ;
		cant[ i ] = 0 ;
		inq[ i ] = false ;
	}
	dist[ node ] = 0 ;
	queue<int> q ;
	q.push( node ) ;
	inq[ node ] = true ;
	cant[ node ] = 1 ;
	while( !q.empty() ) {
		int from = q.front() ;
		q.pop() ;
		inq[ from ] = false ;
		for( Pair edge : adj[ from ] ) {
			int to = edge.first ;
			int w = edge.second ;
			if( dist[ to ] > dist[ from ] + w ) {
				dist[ to ] = dist[ from ] + w ;
				if( !inq[ to ] ) {
					q.push( to ) ;
					inq[ to ] = true ;
					cant[ to ] ++ ;
					if( cant[ to ] > n ) {
						return true ; // exist ciclo negativo
					}
				}
			}
		}
	}
	return false ;
}