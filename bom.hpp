#pragma once
#include "Entity.hpp"

class bom:public Entity{
    private :
        int order_image ;
	public:
		bom();
		void upd_image( SDL_Renderer * ,  SDL_Texture * ) ;
		int get_order() ;
		void upd_order() ;
		bool is_exist() ;
};
