const int MAXN = (int)1e5;

bool prime[MAXN+1];

void sieve() {// O(nlglgn)
	memset(prime, true, sizeof(prime));

	prime[0] = false;
	prime[1] = false;

	for(int i=2; i*i<=MAXN; i++)
		if(prime[i])
			for(int j=i*i; j<=MAXN; j+=i)
				prime[j]=false;
}

const int MAXN = (int)3e8;

bitset <MAXN+1> notprime;

void sieve() { // careful as pair numbers are not marked as notprime
    for(int i=3; i*i<=MAXN; i+=2)
	if(!notprime[i])
		for(int j=i*i; j<=MAXN; j+=(i<<1))
			notprime[j] = true;
}
