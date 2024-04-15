#pragma once
#include "Entity.hpp"
#include "Bullet.hpp"
using namespace std ;
class Enemy:public Entity{
    private :
        vector<Bullet*> List_Bullet ;
	public:
		Enemy();
		bool is_exist() ;
		void RDPos() ;
};
