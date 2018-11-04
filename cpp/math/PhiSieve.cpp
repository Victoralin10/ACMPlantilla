// not tested, I just use the prime decomposition to obtain phi

#define MAXN 10000
int phi[MAXN + 1]
for(i = 1; i <= MAXN; ++i) phi[i] = i;
for(i = 1; i <= MAXN; ++i) for (j = i * 2; j <= MAXN; j += i) phi[j] -= phi[i];

#define MAXN 3000000
int phi[MAXN + 1], prime[MAXN/10], sz;
bitset <MAXN + 1> mark;

for (int i = 2; i <= MAXN; i++ ){
	if(!mark[i]){
		phi[i] = i-1;
		prime[sz++]= i;
	}
	for (int j=0; j<sz && prime[j]*i <= MAXN; j++ ){
		mark[prime[j]*i]=1;
		if(i%prime[j]==0){
			phi[i*prime[j]] = phi[i]*prime[j];
			break;
		}
		else phi[i*prime[j]] = phi[i]*(prime[j]-1 );
	}
}