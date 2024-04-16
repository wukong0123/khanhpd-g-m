#pragma once
#include <SDL.h>
#include "CommonFunction.hpp"
using namespace CommonFunc ;
class Entity{
	protected:
		double x, y, dx, dy ;
		int HP ;
		double W , H ;
		double speed ;
		SDL_Texture *texture;
	public:
		Entity();
		void move();
		void setX(double);
		void setY(double);
		void setDX(double);
		void setDY(double);
		void setHP(int) ;
		void setTexture(const char* , SDL_Renderer* );
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
		double getDY();
		double getW() ;
		double getH() ;
		bool Coll( Entity ) ;
		SDL_Texture *getTexture();
		virtual ~Entity();
};
