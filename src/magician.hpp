#pragma once
#include "Entity.hpp"
using namespace std ;
class magician:public Entity{
    private :
        int serial_num ;
        int num_photo ;
        string name ;
        int type ;
        int bullet_timer ;
	public:
		magician();
		bool is_exist() ;
		void setframe(int) ;
		void updateframe() ;
		int getsernum() ;
		void setbullettimer(int) ;
		int getbullettimer() ;
		void setNametexture(string ) ;
		string getName() ;
		void RDPos() ;
};
