#pragma once
#include "Player.hpp"
#include "Entity.hpp"
#include "CommonFunction.hpp"
#include "Bullet.hpp"
#include "Enemy.hpp"
#include "bat.hpp"
#include "magician.hpp"
#include "magic_bullet.hpp"
#include "boss.hpp"
#include "boss_skill.hpp"
#include "TTF.hpp"
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
