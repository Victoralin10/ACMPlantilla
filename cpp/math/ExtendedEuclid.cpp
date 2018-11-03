// tested on https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1045

struct EuclidReturn{
    Long u , v , d;
    EuclidReturn( Long u , Long v, Long d ) : u( u ) , v( v ) , d( d ) {}
};
    
EuclidReturn Extended_Euclid( Long a , Long b){
    if( b == 0 ) return EuclidReturn( 1 , 0 , a );
    EuclidReturn aux = Extended_Euclid( b , a%b );
    Long v = aux.u - (a/b)*aux.v;
    return EuclidReturn( aux.v , v , aux.d );
}