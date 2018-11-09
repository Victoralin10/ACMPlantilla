unsigned long long seed = time(0);
  
long long rand(unsigned long long range){
	seed = (seed*1664525ull + 1013904223ull)%(1ull<<32);
	return (seed*range) >> 32;
}