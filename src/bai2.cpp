#include<bits/stdc++.h>

#define ll long long

using namespace std ;
int m , n , q , k , a[2005][2005] ;
int main(){

    cin >> m >> n >> q >> k ;
    for ( int i = 1 ; i <= q ; ++ i ){
        int x , y , z ;
        cin >> x >> y >> z ;
        a[x+1][y+1] = z ;
    }

    for ( int i = 1 ; i <= m ; ++ i ) for ( int j = 1 ; j <= n ; ++ j ){
        a[i][j] += ( a[i-1][j] + a[i][j-1] - a[i-1][j-1] ) ;
    }
    int res = 0 ;
    for ( int i = 1 ; i <= k ; ++ i ){
        int x , y , z , t ;
        cin >> x >> y >> z >> t ;
        x ++ ; y ++ ;
        res = max( res , a[x+z-1][y + t-1] - a[x+z-1][y-1] - a[x-1][y + t - 1] + a[x-1][y-1] ) ;
    }
    cout << res  ;
    return 0 ;
}
