char s[ 1000 ] ;
char ch ;
string ss ;
int n ;
long long m;
double d;
cin >> ss ;

ios::sync_with_stdio(false); // FAST IO CIN, COUT, anula el uso de scanf, printf, puts
cin.tie(NULL);
cout.tie(NULL);

scanf( "%d" , &n ) ; // lectura de un entero
scanf( "%lld" , &m ) ; // lectura de un long long
scanf( "%c" , &ch ) ; // lectura de un caracter
scanf( "%s" , s ) ; // lectura de una cadena (No se coloca el "&")
scanf( "%f" , &d ) ; // lectura de un double
scanf( "%Lf" , &d ) ; // lectura de un long double

printf( "%d" , n ) ; // imprimir un entero (En el printf No se coloca el "&" a las variables)

ss.c_str() ; // convert string to char[] 
string(s); // convert char[] to string

scanf( " %c" , &ch ) ; // leer un string o un char con un espacio delante para ignorar el endl de una anterior lectura
scanf( "%s" , s + 1 ) ; // leer apartir de index 1
scanf( "%*d %d", &n ) ; // ignorar lectura
sscanf( s , "%d" , &n ) ; // enviar una cadena y leerla

scanf( "%[^\n]s" , s ) ; // leer una linea, hasta el salto de linea
getline(cin, s); // leer una linea, hasta el salto de linea

stringstream out(ss); // separar por espacios los valores del string y almacenarlos en out
while(out >> variables) {}; // de esta forma extraemos los valores almacenados en out