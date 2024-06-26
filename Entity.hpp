#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "CommonFunction.hpp"
using namespace CommonFunc ;
class Entity{
	protected:
		double x, y, dx, dy ;
		int HP ;
		double W , H ;
		double speed , angle ;
		SDL_Texture *texture;
	public:
		Entity();
		void move();
		void setX(double);
		void setY(double);
		void setDX(double);
		void setDY(double);
		void updSP() ;
		void setHP(int) ;
		void setTexture( SDL_Texture * , SDL_Renderer* );
		void setTexturecut(const char* , SDL_Renderer* , int , int );
		void release() ;
		double getX();
		void MOVETO( int , int , double ) ;
		int getHP() ;
		double getY();
		double getDX();
		void updHP() ;
		void setSP( double ) ;
		double getSP() ;
		void setangle( double ) ;
		double getangle() ;
		double getDY();
		double getW() ;
		double getH() ;
		void render( SDL_Renderer * ) ;
		void setmid( int , int ) ;
		bool Coll( Entity ) ;
		bool is_coll(int , int ) ;
		SDL_Texture *getTexture();
		virtual ~Entity();
};
