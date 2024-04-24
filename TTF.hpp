#pragma once
#include "Entity.hpp"

class TTF:public Entity{
	public:
		TTF();
		bool is_exist() ;
		void setcolor( int  , int , int , int ) ;
		void setTTFTexture( int , int , const char * , SDL_Color , TTF_Font * , SDL_Renderer * ) ;
		void setmid( int , int ) ;
		void render( SDL_Renderer * ) ;
		bool is_coll(int , int ) ;
};
