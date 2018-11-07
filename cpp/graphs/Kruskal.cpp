// tested on https://icpcarchive.ecs.baylor.edu/index.php?option=onlinejudge&page=show_problem&problem=516
// O (E * log(E))

const int N = 1e6;

int id[ N + 5 ];
int Find( int x ){ return id[ x ] = (id[ x ] == x ? x : Find( id[ x ] ) );}
struct Edge{
	int u , v;
    Long w;
	Edge(){}
	Edge( int u , int v , Long w ) : u( u ) , v( v ) , w( w ) {}
};
bool operator < ( const Edge &a , const Edge &b ){ return a.w < b.w ;}
int main(){
	int n , m , u , v , w;
	while( sc( n ) == 1 ){
		if( !n ) break;
		sc( m );
		REP( i , N ) id[ i ] = i;
		vector< Edge > E;
		REP( i , m ){
			sc( u ) , sc( v ) , sc( w );
			u -- , v --;
			E.push_back( Edge( u , v , w ) );
		}
		sort( ALL( E ) );
		int ans = 0;
		REP( i , SZ( E ) ){
			int pu = Find( E[ i ].u ) , pv = Find( E[ i ].v );
			if( pu != pv ){
				ans += E[ i ].w;
				id[ pu ] = pv;
			}
		}
		printf( "%d\n" , ans );
	}
}