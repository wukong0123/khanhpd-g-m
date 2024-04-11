#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Bullet.hpp"
class Player:public Entity{
	private:
		bool up = 0 , down = 0 , left = 0 , right = 0;
	    vector<Bullet*> List_Bullet ;
	    int direct ; int cur_pos ;
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
		void resetInput();
};
