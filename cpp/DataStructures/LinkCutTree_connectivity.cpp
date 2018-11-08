struct Node {
	int left = 0 ;
	int rigth = 0 ;
	int parent = 0 ;
	bool revert = 0 ;
} ;

Node node[ V ] ;
char type[ 10 ] ;
int u , v ;

bool isRoot( int u ) {
	int p = node[ u ].parent ;
	return !p || ( node[ p ].left != u && node[ p ].rigth != u ) ;
}

void push( int x ) {
	if( !node[ x ].revert ) return ;
	node[ x ].revert = false ;
	swap( node[ x ].left , node[ x ].rigth ) ;
	if( node[ x ].left ) node[ node[ x ].left ].revert ^= 1 ;
	if( node[ x ].rigth ) node[ node[ x ].rigth ].revert ^= 1 ;
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
	bool leftChildX = x == node[ p ].left ;
	connect( leftChildX ? node[ x ].rigth : node[ x ].left , p , leftChildX ) ;
	connect( p , x , !leftChildX ) ;
	connect( x , g , !isRootP ? p == node[ g ].left : -1 ) ;
}

void splay( int x ) {
	while( !isRoot( x ) ) {
		int p = node[ x ].parent ;
		int g = node[ p ].parent ;
		if( !isRoot( p ) )
			push( g ) ;
		push( p ) ;
		push( x ) ;
		if( !isRoot( p ) ) {
			bool onLeft1 = x == node[ p ].left ;
			bool onLeft2 = p == node[ g ].left ;
			rotate( onLeft1 == onLeft2 ? p : x ) ;
		}
		rotate( x ) ;
	}
	push( x ) ;
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

void makeRoot( int x ) {
	expose( x ) ;
	node[ x ].revert ^= 1 ;
}

bool connected( int x , int y ) {
	if( x == y ) return true ;
	expose( x ) ;
	expose( y ) ;
	return node[ x ].parent ;
}

void link( int x , int y ) {
	if( connected( x , y ) ) return ;
	makeRoot( x ) ;
	node[ x ].parent = y ;
}

void cut( int x , int y ) {
	makeRoot( x ) ;
	expose( y ) ;
	if( node[ y ].rigth != x || node[ x ].left || node[ x ].rigth ) return ;
	node[ node[ y ].rigth ].parent = 0 ;
	node[ y ].rigth = 0 ;
}

int main() {
	int n , m ;
	cin >> n >> m ;
	REP( i , m ) {
		scanf( "%s" , &type ) ;
		if( type[ 0 ] == 'a' ) {
			sc2( u , v ) ;
			link( u , v ) ;
		}
		if( type[ 0 ] == 'r' ) {
			sc2( u , v ) ;
			cut( u , v ) ;
		}
		if( type[ 0 ] == 'c' ) {
			sc2( u , v ) ;
			if( connected( u , v ) ) printf( "YES\n" ) ;
			else printf( "NO\n" ) ;
		}
	}

	return 0 ;
}