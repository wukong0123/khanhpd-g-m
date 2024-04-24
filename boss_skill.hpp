#pragma once
#include "Entity.hpp"

class kboss:public Entity{
    private :
        int order_image ;
        int numtexture ;
	public:
		kboss();
		int get_order() ;
		void upd_order() ;
		bool is_exist() ;
};
