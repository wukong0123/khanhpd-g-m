#include<bits/stdc++.h>

#define ll long long

using namespace std ;
int n , k ;
char c[10005] ;
vector<char> V ;
void printff( int Num , int pos ){
    if ( Num == k  ){
        for ( char cx : V ){
            cout << cx ;
        }
        cout << "\n" ; return ;
    }
    for ( int i = pos ; i <= n ; ++ i ){
        V.push_back( c[i] ) ;
        printff( Num + 1 , i + 1 ) ;
        V.pop_back() ;
    }
}
int main(){


    cin >> n >> k ;
    for ( int i = 1 ; i <= n ; ++ i ) {
        cin >> c[i] ;
    }
    sort( c + 1 , c + n + 1 ) ;
    printff( 0 , 1 ) ;
    return 0 ;
}
