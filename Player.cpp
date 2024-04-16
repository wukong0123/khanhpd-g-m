#include "Player.hpp"

Player::Player(){
	up = left = down = right = false;
	speed = (double)(3);
	HP = 3 ;
	direct = 0 ; cur_pos = 0 ;
}
void Player::move(){
	if(up){
		dy = -speed;
		if ( direct == 0 ) ++ cur_pos ; else cur_pos = 0 ;
		direct = 0 ;
	}else if(down){
		dy = speed;
		if ( direct == 2 ) ++ cur_pos ; else cur_pos = 0 ;
		direct = 2 ;
	}else if(left){
		dx = -speed;
		if ( direct == 3 ) ++ cur_pos ; else cur_pos = 0 ;
		direct = 3 ;
	} else if(right){
		dx = speed;
		if ( direct == 1 ) ++ cur_pos ; else cur_pos = 0 ;
		direct = 1 ;
	}
	cur_pos %= 12 ;
	over_x = 0 ;
	over_y = 0 ;
	if ( x + dx < 0 ) over_x = x + dx ;
    else if ( x + dx > 1000 - this->W ) over_x= x + dx - 1000 + this->W ;
    if ( y + dy < 0 ) over_y = y + dy ;
    else if ( y + dy > 650 - this->H ) over_y = y + dy - 650 + this->H ;

	x = (x + dx < 0 ? 0 : (x + dx > 1000 - this->W ? 1000 - this->W : x + dx));
	y = (y + dy < 0 ? 0 : (y + dy > 650 - this->H ? 650 - this->H : y + dy));
	dx = dy = 0;
}
bool Player :: is_move(){
    return ( up || down || left || right ) ;
}

void Player::keyDown(SDL_KeyboardEvent *event){
	if(!(event->repeat)){
		switch(event->keysym.scancode){
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_UP:
                up = true;
                break;
            case SDL_SCANCODE_S:
            case SDL_SCANCODE_DOWN:
                down = true;
                break;
            case SDL_SCANCODE_A:
            case SDL_SCANCODE_LEFT:
                left = true;
                break;
            case SDL_SCANCODE_D:
            case SDL_SCANCODE_RIGHT:
                right = true;
                break;
        }
    }
}
void Player::keyUp(SDL_KeyboardEvent *event){
	if(!(event->repeat)){
		switch(event->keysym.scancode){
		case SDL_SCANCODE_W:
		case SDL_SCANCODE_UP:
			up = false;
			break;
		case SDL_SCANCODE_S:
		case SDL_SCANCODE_DOWN:
			down = false;
			break;
		case SDL_SCANCODE_A:
		case SDL_SCANCODE_LEFT:
			left = false;
			break;
		case SDL_SCANCODE_D:
		case SDL_SCANCODE_RIGHT:
			right = false;
			break;
    }
    }
}
void Player::mouseDown( int Newx , int Newy , SDL_Renderer* renderer){
    int xxx ;
	Bullet* NewBullet = new Bullet() ;
	NewBullet->setTexture( "Bullet.png" , renderer  ) ;
    NewBullet->setHP(1) ;
    int radius = sqrt((this->W) * ( this->W ) + (this->H) * ( this->H )) / 2 + 1 ;
	double Deltax = (double)(Newx) - ( this->x + this->W / 2) ;
	double Deltay = (double)(Newy) - ( this->y + this->H / 2) ;
	if ( sqrt(Deltax * Deltay + Deltay * Deltay ) < radius ){
        NewBullet->release() ; return ;
	}
    if ( Deltax == 0 ){
        NewBullet->setX(this->x) ;
        NewBullet->setY(this->y + radius * ( Newy > this->y ? 1 : -1 )) ;
    } else
    if ( Deltay == 0 ){
        NewBullet->setY(this->y) ;
        NewBullet->setX(this->x + radius * ( Newx > this->x ? 1 : -1 )) ;
    }
    else{
        double Ratio = Deltax / Deltay ;
        Ratio = Ratio * Ratio ;
        double _DX = speed * speed /( 1 + Ratio ) * Ratio ;
        double _DY = speed * speed - _DX ;
        double _GX = (double)(radius * radius) /( 1 + Ratio ) * Ratio ;
        double _GY = (double)(radius * radius) - _GX ;
        double _LX = ( this->x + this->W / 2) + (sqrt(_GX) )* ( Deltax > 0 ? 1 : -1 );
        double _LY = ( this->y + this->H / 2) + (sqrt(_GY) )* ( Deltay > 0 ? 1 : -1 ) ;
        NewBullet->setX(_LX - 10 ) ;
        NewBullet->setY(_LY - 10 ) ;
    }
    NewBullet->MOVETO( Newx , Newy , NewBullet->getSP() ) ;
    List_Bullet.push_back(NewBullet) ;
}
void Player::setWH( int x ,int y ){
    this->W = x ; this->H = y ;
}
void Player::render( SDL_Renderer * renderer){
    CommonFunc::ProrenderTexture(texture , cur_pos * 36 , direct * 48 , x , y , 36 , 48 , 36 , 48 , renderer ) ;
}
int Player::getox(){
    return this->over_x ;
}
int Player::getoy(){
    return this->over_y ;
}
void Player::resetInput(){
	left = up = right = down = false;
}
void Player::setbulletlist(std::vector<Bullet*> List ){
    List_Bullet = List ;
}

std :: vector<Bullet*> Player::GetBulletlist(){
    return List_Bullet ;
}
