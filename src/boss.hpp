#pragma once
#include "Entity.hpp"
using namespace std ;
class boss:public Entity{
    private :
        int serial_num ;
        string name ;
        int type ;
        int status ;
        int pos , active ;
        bool flip ;
	public:
		boss();
		bool getflip() ;
		bool is_exist() ;
		int getpos() ;
		void updateframe() ;
		int getsernum() ;
		void setstatus(int ) ;
		bool True() ;
        int getstatus() ;
		void RDPos() ;
};
