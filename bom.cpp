#pragma once
#include "bom.hpp"
#include <string>

bom::bom(){
    speed = (double)(15)  ;
    HP = 1 ;
    angle = 0 ;
    order_image = 0 ;
}
bool bom::is_exist(){
    if ( ((x < 0 || y < 0 || ( x + 20 > 1000 || y + 20 > 650 ) ) && order_image == 0)  || order_image > 8 )
        return 0 ;
    return 1 ;
}
int bom::get_order(){
    return this->order_image ;
}
void bom::upd_order(){
    order_image ++ ;
}

void bom::upd_image( SDL_Renderer * renderer , SDL_Texture * s ){

    this->setTexture( s , renderer ) ;
    if ( order_image == 1 ){
        x -= 33 ;
        y -= 92 ;
    }
}
