#pragma once
#include "boss_skill.hpp"
#include <string>

kboss::kboss(){
    speed = (double)(10)  ;
    HP = 1 ;
    angle = 0 ;
    order_image = 1 ;
    numtexture = 4 ;
}
bool kboss::is_exist(){
    if ( ((x < 0 || y < 0 || ( x + 20 > 1000 || y + 20 > 650 ) )) )
        return 0 ;
    return 1 ;
}
int kboss::get_order(){
    return this->order_image ;
}
void kboss::upd_order(){
    order_image %= 4 ;
    order_image ++ ;
}
