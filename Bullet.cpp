#include "Bullet.hpp"

Bullet::Bullet(){
    speed = (double)(10)  ;
    HP = 1 ;
}
bool Bullet::is_exist(){
    if ( x < 0 || y < 0 || ( x + 20 > 1000 || y + 20 > 650 || HP <= 0 ) )
        return 0 ;
    return 1 ;
}
