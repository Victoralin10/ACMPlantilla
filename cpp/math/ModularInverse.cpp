// ax = 1(mod n)
Long modular_inverse(Long a, Long n){
    EuclidReturn aux = Extended_Euclid(a,n);
    if (aux.d != 1) return -1; // not coprimes, so impossible to get a modular inverse
    return ((aux.u % n) + n)%n;
}