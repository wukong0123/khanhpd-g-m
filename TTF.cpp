#include "TTF.hpp"

TTF::TTF(){
    HP = 20 ;
}
bool TTF::is_exist(){
    return ( HP > 0 ) ;
}
void TTF::setcolor( int apha , int red , int green , int blue ){
    SDL_SetTextureColorMod( this->texture , red, green, blue );
    SDL_SetTextureAlphaMod( this->texture , apha );
}
void TTF::setTTFTexture( int a , int b , const char * s , SDL_Color col , TTF_Font * gfont , SDL_Renderer * renderer ){
    //this->release() ;
    SDL_Surface* textSurface = TTF_RenderText_Solid( gfont, s , col );

    this->texture = SDL_CreateTextureFromSurface( renderer, textSurface );
    this->W = textSurface->w ;
    this->H = textSurface->h ;
    this->x = a ; this->y = b ;
    SDL_FreeSurface( textSurface );
}
void TTF::setmid( int a , int b ){
    x = a - W / 2 ; y = b - H / 2 ;
}
void TTF::render( SDL_Renderer * renderer ){
    CommonFunc::RealrenderTexture( texture , x , y , 0 , 0 , renderer ) ;
}
bool TTF::is_coll(int a , int b ){
    return (CommonFunc::IS_ATC(a , b , x , y , x + W , y + H)) ;
}
