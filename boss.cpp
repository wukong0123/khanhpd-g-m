#include "boss.hpp"
int BX[] = { 115 , 115 , 1000 - 115 , 1000 - 115 } ;
int BY[] = { 88 , 650 - 88 , 650 - 88 , 88 } ;
int numstatus[] = { 36 , 26 , 24 , 20 } ;

boss::boss(){
    speed = (double)(7)  ;
    HP = 700 ;
    x = -300 ;
    y = -300 ;
    pos = 0 ;
    status = 0 ;
    flip = 1 ;serial_num = 1 ;
    this->MOVETO(BX[pos] , BY[pos] , speed ) ;
    active = 0 ;
}
bool boss::is_exist(){
    if ( status == 4 )
        return 0 ;
    return 1 ;
}
int boss::getpos(){
    return this->pos ;
}
bool boss::getflip(){
    return flip ;
}

void boss::updateframe(){

    this->W = 229 ; this->H = 177 ;

    if ( HP < 0 && status != 3 ){
        status = 3 ; serial_num = 1 ;
    }
    else
    if ( status == 3 ){
        serial_num %= ( numstatus[status] ) ;
        serial_num ++  ;
        if ( serial_num == 20 ){
            status = 4 ;
        }
    }
    else
    if ( status == 0 ){
        serial_num %= ( numstatus[status] ) ;
        serial_num ++  ;
        if ( this->True() ){
            //( pos += 1 ) %= 4 ;
            status = 1 ;
            serial_num = 1 ;
            x -= 13 ; y -= 56 ;
        }
    }
    else if ( status == 1 ){
        serial_num %= ( numstatus[status] ) ;
        serial_num ++  ;
        if ( serial_num == 26 ){
            ( pos += 1 ) %= 4 ;
            this->MOVETO( BX[pos] -13 , BY[pos] - 56, speed ) ;
            status = 0 ;
            serial_num = 1 ;
            active = 1 ;
            x += 13 ; y += 56 ;
        }
    }
    if ( status == 0 ){
       if ( ( pos == 0 && active == 0 ) || pos == 2 || pos == 1 ) flip = 1 ;
       else flip = 0 ;
    }
    else if ( status == 1 ){
        if ( pos == 0 || pos == 1 ) flip = 1 ;
        else flip = 0 ;
    }
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
bool boss::True(){
    return (( pos == 0 && x *( x + dx ) < 0) || ( pos == 1 && ( y - 650 + 177 ) * ( y + dy - 650 + 177) < 0 )
            || ( pos == 2 && ( 771 - x ) * ( 771 - x - dx ) < 0  || ( pos == 3 && y * ( y + dy ) < 0 ) ) ) ;
}
