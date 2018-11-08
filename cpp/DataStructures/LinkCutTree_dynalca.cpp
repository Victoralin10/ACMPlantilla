struct Node {
	int left = 0 ;
	int rigth = 0 ;
	int parent = 0 ;
} ;

Node node[ V ] ;
char type[ 10 ] ;
int u , v ;

bool isRoot( int u ) {
	int p = node[ u ].parent ;
	return !p || ( node[ p ].left != u && node[ p ].rigth != u ) ;
}

void connect( int ch , int p , int isLeftChild ) {
	if( ch ) node[ ch ].parent = p ;
	if( isLeftChild == -1 ) return ;
	if( isLeftChild ) node[ p ].left = ch ;
	else node[ p ].rigth = ch ;
}

void rotate( int x ) {
	int p = node[ x ].parent ;
	int g = node[ p ].parent ;
	bool isRootP = isRoot( p ) ;
	bool leftChildX = ( x == node[ p ].left ) ;
	connect( leftChildX ? node[ x ].rigth : node[ x ].left , p , leftChildX ) ;
	connect( p , x , !leftChildX ) ;
	connect( x , g , !isRootP ? p == node[ g ].left : -1 ) ;
}

void splay( int x ) {
	while( !isRoot( x ) ) {
		int p = node[ x ].parent ;
		int g = node[ p ].parent ;
		if( !isRoot( p ) ) {
			bool onLeft1 = x == node[ p ].left ;
			bool onLeft2 = p == node[ g ].left ;
			rotate( onLeft1 == onLeft2 ? p : x ) ;
		}
		rotate( x ) ;
	}
}

int expose( int x ) {
	int last = 0 ;
	for( int y = x ; y ; y = node[ y ].parent ) {
		splay( y ) ;
		node[ y ].left = last ;
		last = y ;
	}
	splay( x ) ;
	return last ;
}

int findRoot( int x ) {
	expose( x ) ;
	while( node[ x ].rigth ) 
		x = node[ x ].rigth ;
	splay( x ) ;
	return x ;
}

void link( int x , int y ) {
	if( findRoot( x ) == findRoot( y ) ) return ;
	expose( x ) ;
//	if( node[ x ].rigth ) return ;
	node[ x ].parent = y ;
//	node[ y ].left = x ;
}

void cut( int x ) {
	expose( x ) ;
	if( !node[ x ].rigth ) return ;
	node[ node[ x ].rigth ].parent = 0 ;
	node[ x ].rigth = 0 ;
}

int lca( int x , int y ) {
	if( findRoot( x ) != findRoot( y ) ) return 0 ;
	expose( x ) ;
	return expose( y ) ;
}

int main() {
	int n , m ;
	cin >> n >> m ;
	REP( i , m ) {
		scanf( "%s" , &type ) ;
		if( type[ 1 ] == 'i' ) {
			sc2( u , v ) ;
			link( u , v ) ;
		}
		if( type[ 1 ] == 'u' ) {
			sc( u ) ;
			cut( u ) ;
		}
		if( type[ 1 ] == 'c' ) {
			sc2( u , v ) ;
			pf( lca( u , v ) ) ;
		}
	}

	return 0 ;
}