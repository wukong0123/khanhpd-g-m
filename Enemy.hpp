#pragma once
#include "Entity.hpp"

class Enemy:public Entity{
	public:
		Enemy();
		bool is_exist() ;
		void RDPos() ;
};
