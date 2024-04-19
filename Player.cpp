#include "Player.hpp"

Player::Player(){
	up = left = down = right = false;
	speed = (double)(3.5);
	HP = 3 ;
	direct = 0 ; cur_pos = 0 ;
	weapon = new Entity();
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

void Player::mouseMove( int Nx , int Ny , SDL_Renderer* renderer ){

    weapon->setangle( CommonFunc::getangle(Nx - this->x - this->W / 2 , Ny - this->y - this->H/2)) ;
    pair<int,int> newpos = CommonFunc::getPosmovemouse( this->x , this->y , this->W , this->H ,  Nx - this->x - this->W / 2 , Ny - this->y - this->H/2 , weapon->getW() , weapon->getH() ) ;
    weapon->setX( newpos.first ) ;
    weapon->setY( newpos.second ) ;

}

void Player::mouseDown( int Newx , int Newy , int type , SDL_Renderer* renderer ){

    if ( type == 1 ){
        Bullet* NewBullet = new Bullet() ;
        NewBullet->setTexture( "bullet.png" , renderer  ) ;

        NewBullet->setHP(1) ;
        NewBullet->setangle(CommonFunc::getangle( Newx - this->x - this->W / 2 , Newy - this->y - this->H/2 )) ;

        pair<int,int> newpos = CommonFunc::getPosmovemouse( x , y , W , H ,  Newx - this->x - this->W / 2 , Newy - this->y - this->H/2 , NewBullet->getW() , NewBullet->getH() ) ;

        NewBullet->setX( newpos.first ) ; NewBullet->setY( newpos.second ) ;

        NewBullet->MOVETO( Newx , Newy , NewBullet->getSP() ) ;
        List_Bullet.push_back(NewBullet) ;
    }
    else{
        bom* NewBullet = new bom() ;
        NewBullet->setTexture( "bom.png" , renderer  ) ;

        NewBullet->setHP(1) ;
        NewBullet->setangle(CommonFunc::getangle( Newx - this->x - this->W / 2 , Newy - this->y - this->H/2 )) ;

        pair<int,int> newpos = CommonFunc::getPosmovemouse( x , y , W , H ,  Newx - this->x - this->W / 2 , Newy - this->y - this->H/2 , NewBullet->getW() , NewBullet->getH() ) ;

        NewBullet->setX( newpos.first ) ; NewBullet->setY( newpos.second ) ;

        NewBullet->MOVETO( Newx , Newy , NewBullet->getSP() ) ;
        List_bom.push_back(NewBullet) ;
    }

}

void Player::setWH( int x ,int y ){
    this->W = x ; this->H = y ;
}

Entity* Player::getweapon(){
    return this->weapon ;
}

void Player::render( SDL_Renderer * renderer){
    CommonFunc::ProrenderTexture(texture , cur_pos * 36 , direct * 48 , x , y , 36 , 48 , 36 , 48 , renderer ) ;
}
void Player::setweapon( char* Tr , SDL_Renderer * renderer ){
    this->weapon->setTexture( Tr , renderer )  ;
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
void Player::setbomlist(std::vector<bom*> List ){
    List_bom = List ;
}
std :: vector<Bullet*> Player::GetBulletlist(){
    return List_Bullet ;
}
std :: vector<bom*> Player::Getbomlist(){
    return List_bom ;
}

