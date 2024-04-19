#include "bat.hpp"

int VX[] = { 0 , 0 , 1000 - 50 , 1000 - 50 } ;
int VY[] = { 0 , 650 - 50 , 650 - 50 , 0 } ;
bat::bat(){
    speed = (double)(0.6)  ;
    HP = 1 ;
    this->RDPos() ;
}
bool bat::is_exist(){
    if ( x < 0 || y < 0 || ( x + W > 1000 || y + H > 650 || HP <= 0 ) )
        return 0 ;
    return 1 ;
}
void bat::setframe( int x ){
    this->serial_num = 1 ; this->num_photo = x ;
}
void bat::updateframe(){
    //serial_num ++  ;
    serial_num %= ( num_photo ) ;
    serial_num ++  ;
}
int bat::getsernum(){
    return this->serial_num ;
}
void bat::setNametexture( string s ){
    this->name = s ;
}
string bat::getName(){
    return this->name ;
}
void bat::RDPos(){
    //srand(time(NULL)) ;
    int oc = genRDNumber( 0 , 1 ) ;
    int pos = genRDNumber( 0 , 3 ) ;
    if ( oc == 0 ){
    this->x = VX[pos] ; this->y = genRDNumber( 0 , 650 - 50 ) ; }
    else{
    this->y = VY[pos] ; this->x = genRDNumber( 0 , 1000 - 50 ) ; }
}
