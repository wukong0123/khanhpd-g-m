#pragma once
#include "Player.hpp"
#include "Entity.hpp"
#include "CommonFunction.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"

class Game{
    protected:
      SDL_Renderer* renderer ;
      SDL_Window* window ;
    public :
      Game();
      void Gamestart() ;
      void set_Renderer() ;
      SDL_Renderer* get_Renderer() ;
      void set_Window() ;
      SDL_Window* get_Window() ;
};
