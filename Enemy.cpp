#include "Enemy.hpp"
int VTX[] = { 0 , 0 , 1000 - 50 , 1000 - 50 } ;
int VTY[] = { 0 , 650 - 50 , 650 - 50 , 0 } ;
Enemy::Enemy(){
    speed = (double)(0.3)  ;
    HP = 2 ;
    this->RDPos() ;
}
bool Enemy::is_exist(){
    if ( x < 0 || y < 0 || ( x + W > 1000 || y + H > 650 || HP <= 0 ) )
        return 0 ;
    return 1 ;
}
void Enemy::setframe( int x ){
    this->serial_num = 1 ; this->num_photo = x ;
}
void Enemy::updateframe(){
    //serial_num ++  ;
    serial_num %= ( num_photo ) ;
    serial_num ++  ;
}
int Enemy::getsernum(){
    return this->serial_num ;
}
void Enemy::setNametexture( string s ){
    this->name = s ;
}
string Enemy::getName(){
    return this->name ;
}
void Enemy::RDPos(){
    //srand(time(NULL)) ;
    int oc = genRDNumber( 0 , 1 ) ;
    int pos = genRDNumber( 0 , 3 ) ;
    if ( oc == 0 ){
    this->x = VTX[pos] ; this->y = genRDNumber( 0 , 650 - 50 ) ; }
    else{
    this->y = VTY[pos] ; this->x = genRDNumber( 0 , 1000 - 50 ) ; }
}
