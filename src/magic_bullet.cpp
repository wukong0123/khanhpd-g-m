#pragma once
#include "magic_bullet.hpp"
#include <string>

mbullet::mbullet(){
    speed = (double)(5)  ;
    HP = 1 ;
    angle = 0 ;
    order_image = 0 ;
    existed_time = 0  ;
}
bool mbullet::is_exist(){
    if ( ((x < 0 || y < 0 || ( x + 20 > 1000 || y + 20 > 650 ) ) && order_image == 0)  || existed_time > 7000 )
        return 0 ;
    return 1 ;
}
int mbullet::get_order(){
    return this->order_image ;
}
void mbullet::upd_timer(){
    this->existed_time += 50 ;
}
void mbullet::upd_order(){
    order_image %= 8 ;
    order_image ++ ;
}
int mbullet::getexistedtimer(){
    return this->existed_time ;
}
void mbullet::upd_image( SDL_Renderer * renderer , SDL_Texture * s ){
    this->setTexture( s , renderer ) ;
}
