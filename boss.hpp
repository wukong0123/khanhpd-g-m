#pragma once
#include "Entity.hpp"
using namespace std ;
class boss:public Entity{
    private :
        int serial_num ;
        int num_photo ;
        string name ;
        int type ;
        int status ;
        int Tox , Toy ;
        bool flip ;
	public:
		boss();
		void setflip(bool ) ;
		bool getflip() ;
		bool is_exist() ;
		void setframe(int) ;
		void updateframe() ;
		int getsernum() ;
		void setstatus(int ) ;
        int getstatus() ;
		void RDPos() ;
};
