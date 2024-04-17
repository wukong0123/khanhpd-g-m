#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Bullet.hpp"
class Player:public Entity{
	private:
		bool up = 0 , down = 0 , left = 0 , right = 0;
	    vector<Bullet*> List_Bullet ;
	    Entity* weapon ;
	    int direct ; int cur_pos ;
	    int over_x = 0 , over_y = 0 ;
	public:
		Player();
		void move();
		void setbulletlist(std::vector<Bullet*> ) ;
		vector<Bullet*> GetBulletlist();
		bool is_move() ;
		void keyDown(SDL_KeyboardEvent*);
		void keyUp(SDL_KeyboardEvent*);
		void mouseDown(int , int , SDL_Renderer*) ;
		void render(SDL_Renderer * ) ;
		int getox() ;
		void mouseMove(int , int , SDL_Renderer*) ;
		Entity* getweapon() ;
		void setweapon( char * , SDL_Renderer * ) ;
		int getoy() ;
		void setWH(int , int) ;
		void resetInput();
};
