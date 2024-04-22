#include "boss.hpp"
int BX[] = { 0 , 0 , 1000 - 200 , 1000 - 200 } ;
int BY[] = { 0 , 650 - 200 , 650 - 200 , 0 } ;
int numstatus[] = { 36 , 26 , 24 , 20 } ;
boss::boss(){
    speed = (double)(1)  ;
    HP = 1000 ;
    this->RDPos() ;
    x = -300 ;
    y = -300 ;
}
bool boss::is_exist(){
    if ( HP <= 0 )
        return 0 ;
    return 1 ;
}
void boss::setframe( int x ){
    this->serial_num = 1 ; this->num_photo = x ;
}
void boss::setflip( bool x ){
    flip = x ;
}
bool boss::getflip(){
    return flip ;
}
void boss::updateframe(){
    //serial_num ++  ;
    serial_num %= ( num_photo ) ;
    serial_num ++  ;
}
int boss::getsernum(){
    return this->serial_num ;
}
int boss::getstatus(){
    return this->status ;
}
void boss::setstatus( int x ){
    this->status = x ;
}
void boss::RDPos(){
    //srand(time(NULL)) ;

    int pos = genRDNumber( 0 , 3 ) ;
    this->x = BX[pos] ;
    this->y = BY[pos] ;
}
