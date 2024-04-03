#include "Enemy.hpp"

int VTX[] = { 0 , 0 , 1000 - 80 , 1000 - 80 } ;
int VTY[] = { 0 , 650 - 45 , 650 - 45 , 0 } ;
Enemy::Enemy(){
    speed = (double)(0.5)  ;
    HP = 1 ;
    this->RDPos() ;
}
bool Enemy::is_exist(){
    if ( x < 0 || y < 0 || ( x + 80 > 1000 || y + 45 > 650 || HP <= 0 ) )
        return 0 ;
    return 1 ;
}
void Enemy::RDPos(){
    //srand(time(NULL)) ;
    int oc = genRDNumber( 0 , 1 ) ;
    int pos = genRDNumber( 0 , 3 ) ;
    if ( oc == 0 ){
    this->x = VTX[pos] ; this->y = genRDNumber( 0 , 650 - 45 ) ; }
    else{
    this->y = VTY[pos] ; this->x = genRDNumber( 0 , 1000 - 80 ) ; }
}
