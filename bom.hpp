#pragma once
#include "Entity.hpp"

class bom:public Entity{
    private :
        int order_image ;
	public:
		bom();
		void upd_image( SDL_Renderer * ) ;
		int get_order() ;
		bool is_exist() ;
};
