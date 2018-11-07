// Plan-chotaV2
//http://ahmed-aly.com/Standings.jsp?ID=2954
//11371_SPOJ
#define MAXN 100

// this was is useful for some backtracking problem
// , also useful for breaking ties by other criteria (i.e: node index)
void bfsTopsort() {
	for( int i = 0 ; i < m ; ++i )
	{
		G[u].push_back(v);
		in[v]++;
	}
	priority_queue <int> Q;
	for( int i = 0 ; i < n ; ++i )
		if( in[i] == 0 )
			Q.push(-i);
	vector< int >orden;
	while( !Q.empty() )
	{
		int u = Q.top();
		u = -u;
		Q.pop();    
		orden.push_back(u);
		int nG = G[u].size();
		for( int i = 0 ; i < nG ; ++i )
		{
			int v = G[u][i];
			in[v]--;
			if( in[v] == 0 )
			Q.push(-v);
		}
	}
}


// recrusivily
void topsort( int u ){
	vis[ u ] = 1;
	FOR( v , dag[ u ] )
		if( !vis[ *v ] ) topsort( *v );
	cola[ sz ++ ] = u;
}