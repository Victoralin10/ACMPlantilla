// tested on https://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=99999999&category=791&page=show_problem&problem=2471
typedef unsigned long long ull;
typedef vector<ull> vull;

struct Pollard_Rho
{
	ull q;
	vull v;	
	Pollard_Rho(){}
	Pollard_Rho( ull x ) {
		q = x;
	}
	ull gcd(ull a, ull b){
	    if(b == 0) return a;
	    return gcd( b , a % b );
	}
	ull mul(ull a,ull b,ull c){
	    ull x = 0, y = a % c;
	    while(b > 0){
	        if(b%2 == 1){
	            x = (x+y)%c;
	        }
	        y = (y*2)%c;
	        b /= 2;
	    }
	    return x%c;
	}
	ull modd(ull a,ull b,ull c){
	    ull x=1,y=a; 
	    while(b > 0){
	        if(b%2 == 1){
	            x=mul(x,y,c);
	        }
	        y = mul(y,y,c); 
	        b /= 2;
	    }
	    return x%c;
	}
	bool Miller(ull p,int iteration){ // isPrime? O(iteration * (log(n)) ^ 3 )
	    if(p<2){
	        return false;
	    }
	    if(p!=2 && p%2==0){
	        return false;
	    }
	    ull s=p-1;
	    while(s%2==0){
	        s/=2;
	    }
	    for(int i=0;i<iteration;i++){
	        ull a=rand()%(p-1)+1,temp=s;
	        ull mod=modd(a,temp,p);
	        while(temp!=p-1 && mod!=1 && mod!=p-1){
	            mod=mul(mod,mod,p);
	            temp *= 2;
	        }
	        if(mod!=p-1 && temp%2==0){
	            return false;
	        }
	    }
	    return true;
	}
	ull rho(ull n){
	    if( n % 2 == 0 ) return 2;
	    ull x = 2 , y = 2 , d = 1;
	    int c = rand() % n + 1;
	    while( d == 1 ){
	        x = (mul( x , x , n ) + c)%n;
	        y = (mul( y , y , n ) + c)%n;
	        y = (mul( y , y , n ) + c)%n;
	        if( x - y >= 0 ) d = gcd( x - y , n );
	        else d = gcd( y - x , n );
	    }
	    return d;
	}
	void factor(ull n){
	    if (n == 1) return;
	    if( Miller(n , 10) ){ // 10 is good enough for most cases
	        if(q != n) v.push_back(n);
	        return;
	    }
	    ull divisor = rho(n);
	    factor(divisor);
	    factor(n/divisor);
	}
	vull primefact( ull num ) // O(num ^ (1/4))
	{
		v.clear();
		q = num;
		factor( num );
		sort( ALL(v) );
		if( v.empty() ) // primos o 1 
			v.push_back( num );
		return v;
	}
    map<ull, int> primeFactorsDescomposition(ull num) { // returns pairs of {prime, exponent}
        vull pf = primefact(num);
        map<ull, int> pd; // prime descomposition
        for (int i = 0; i < (int)pf.size(); i++) {
            pd[pf[i]]++;
        }
        return pd;
    }
};
