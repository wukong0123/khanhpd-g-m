#pragma once
#include "Entity.hpp"
using namespace CommonFunc ;

Entity::Entity(){
	x = y = dx = dy = W = H = 0 ;
	HP = 0 ;
	speed = 0 ;
	texture = NULL;
	angle = 0 ;
}
void Entity::setSP( double speed ){
    this->speed = speed ;
}
void Entity::updSP(){
    this->speed += 0.1 ;
}
double Entity::getSP(){
    return speed ;
}
void Entity::move(){
	this->x += dx;
	this->y += dy;
}
void Entity::setangle( double ag ){
    this->angle = ag ;
}
double Entity::getangle(){
    return this->angle ;
}
void Entity::setX(double x){
	this->x = x;
}

void Entity::setY(double y){
	this->y = y;
}

void Entity::setDX(double dx){
	this->dx = dx;
}

void Entity::setDY(double dy){
	this->dy = dy;
}

void Entity::setHP( int HP ){
	this->HP = HP;
}
int Entity::getHP(){
    return HP ;
}
void Entity::setTexture( SDL_Texture * texture , SDL_Renderer* renderer ){
    //SDL_Texture * texture = CommonFunc::loadTexture( Name , renderer ) ;
	this->texture = texture;
	int _W , _H ;
	SDL_QueryTexture(texture, NULL, NULL, &_W, &_H);
	this->W = _W ; this->H = _H ;
}
double Entity::getX(){
	return x;
}

double Entity::getY(){
	return y;
}

double Entity::getDX(){
	return dx;
}

double Entity::getDY(){
	return dy;
}

SDL_Texture* Entity::getTexture(){
	return texture;
}
void Entity::MOVETO( int Newx , int Newy , double speed ){
    double Deltax = (double)(Newx) - ( this->x + W / 2) ;
	double Deltay = (double)(Newy) - ( this->y + H / 2) ;

	if ( Deltax == 0 ){
        this->setDY( (Deltay > 0 ? 1 : -1 ) * speed ) ;
        return ;
	} else if ( Deltay == 0 ){
        this->setDX( (Deltax > 0 ? 1 : -1 ) * speed ) ;
        return ;
	}

	double Ratio = Deltax / Deltay ;
    Ratio = Ratio * Ratio ;
    double _DX = speed * speed /( 1 + Ratio ) * Ratio ;
    double _DY = speed * speed - _DX ;
    this->setDX( sqrt(_DX)* (Deltax > 0 ? 1 : -1 ) ) ;
    this->setDY( sqrt(_DY)* (Deltay > 0 ? 1 : -1 ) ) ;
}

double Entity::getW(){
    return W ;
}
void Entity::updHP(){
    this->HP -- ;
}
double Entity::getH(){
    return H ;
}
void Entity::release(){
    x = y = dx = dy = 0 ;
    SDL_DestroyTexture(texture) ;
    texture = NULL ;
}
bool Entity::Coll( Entity Cur ){
    int Ax = x , Ay = y , Az = x + W , At = y + H ;
    int Bx = Cur.getX() , By = Cur.getY() , Bz = Cur.getX() + Cur.getW() , Bt = Cur.getY() + Cur.getH() ;
    return ((IS_ATC( Ax , Ay , Bx , By , Bz , Bt )) || (IS_ATC( Ax , At , Bx , By , Bz , Bt ))
            || (IS_ATC( Az , Ay , Bx , By , Bz , Bt )) || (IS_ATC( Az , At , Bx , By , Bz , Bt ))
            || (IS_ATC( Bx , By , Ax , Ay , Az , At )) || (IS_ATC( Bz , By , Ax , Ay , Az , At ))
            || (IS_ATC( Bx , Bt , Ax , Ay , Az , At )) || (IS_ATC( Bz , Bt , Ax , Ay , Az , At ))) ;
}
Entity::~Entity(){
    //SDL_DestroyTexture(texture) ;
}
void Entity::setmid( int a , int b ){
    x = a - W / 2 ; y = b - H / 2 ;
}
bool Entity::is_coll(int a , int b ){
    return (CommonFunc::IS_ATC(a , b , x , y , x + W , y + H)) ;
}
void Entity::render( SDL_Renderer * renderer ){
    CommonFunc::RealrenderTexture( texture , x , y , 0 , 0 , renderer ) ;
}
