#include<bits/stdc++.h>

using namespace std ;
int a[1000006] ;
int main(){

    int n ; cin >> n ;
    for ( int i = 1 ; i <= n ; ++ i ){
        int x ; cin >> x ;
        if ( x > 0 && x <= n ){
            a[x] = 1 ;
        }
    }
    for ( int i = 1 ; i <= n + 1 ; ++ i ) if ( a[i] == 0 ){
        cout << i ; break ;
    }
    return 0 ;
}
