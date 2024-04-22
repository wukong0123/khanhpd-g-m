#pragma once
#include <SDL.h>
#include "Entity.hpp"
#include "Bullet.hpp"
#include "bom.hpp"
class Player:public Entity{
	private:
		bool up = 0 , down = 0 , left = 0 , right = 0;
	    vector<Bullet*> List_Bullet ;
	    Entity* weapon ;
	    int direct ; int cur_pos ;
	    int over_x = 0 , over_y = 0 ;
	    vector<bom*> List_bom ;
	public:
		Player();
		void move();
		void setbulletlist(std::vector<Bullet*> ) ;
		void setbomlist(std::vector<bom*> ) ;
		vector<Bullet*> GetBulletlist();
		vector<bom*> Getbomlist();
		bool is_move() ;
		void keyDown(SDL_KeyboardEvent*);
		void keyUp(SDL_KeyboardEvent*);
		void mouseDown(int , int , int , SDL_Texture * , SDL_Texture * , SDL_Renderer* ) ;
		void render(SDL_Renderer * ) ;
		int getox() ;
		void mouseMove(int , int , SDL_Renderer*) ;
		Entity* getweapon() ;
		void setweapon( SDL_Texture * , SDL_Renderer * ) ;
		int getoy() ;
		void setWH(int , int) ;
		void resetInput();
};
