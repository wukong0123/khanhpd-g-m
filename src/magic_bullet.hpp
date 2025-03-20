#pragma once
#include "Entity.hpp"

class mbullet:public Entity{
    private :
        int order_image ;
        int existed_time ;
	public:
		mbullet();
		void upd_image( SDL_Renderer * , SDL_Texture * ) ;
		void upd_timer() ;
		int getexistedtimer() ;

		int get_order() ;
		void upd_order() ;
		bool is_exist() ;
};
