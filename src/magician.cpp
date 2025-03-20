#include "magician.hpp"

int VLX[] = { 0 , 0 , 1000 - 50 , 1000 - 50 } ;
int VLY[] = { 0 , 650 - 50 , 650 - 50 , 0 } ;
magician::magician(){
    speed = (double)(0.2)  ;
    HP = 1 ;
    this->RDPos() ;
    bullet_timer = 0 ;
}
bool magician::is_exist(){
    if (  HP <= 0  )
        return 0 ;
    return 1 ;
}
void magician::setframe( int x ){
    this->serial_num = 1 ; this->num_photo = x ;
}
void magician::updateframe(){
    serial_num %= ( num_photo ) ;
    serial_num ++  ;
}
void magician::setbullettimer( int x ){
    this->bullet_timer = x ;
}
int magician::getbullettimer(){
    return this->bullet_timer ;
}
int magician::getsernum(){
    return this->serial_num ;
}
void magician::setNametexture( string s ){
    this->name = s ;
}
string magician::getName(){
    return this->name ;
}
void magician::RDPos(){
    //srand(time(NULL)) ;
    int oc = genRDNumber( 0 , 1 ) ;
    int pos = genRDNumber( 0 , 3 ) ;
    if ( oc == 0 ){
    this->x = VLX[pos] ; this->y = genRDNumber( 0 , 650 - 50 ) ; }
    else{
    this->y = VLY[pos] ; this->x = genRDNumber( 0 , 1000 - 50 ) ; }
}
