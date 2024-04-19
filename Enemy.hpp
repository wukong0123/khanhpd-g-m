#pragma once
#include "Entity.hpp"
using namespace std ;
class Enemy:public Entity{
    private :
        int serial_num ;
        int num_photo ;
        string name ;
        int type ;
	public:
		Enemy();
		bool is_exist() ;
		void setframe(int) ;
		void updateframe() ;
		int getsernum() ;
		void setNametexture(string ) ;
		string getName() ;
		void RDPos() ;
};
