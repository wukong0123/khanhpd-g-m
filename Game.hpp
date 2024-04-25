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
static bool CHK = 0 ;
class Game{
    protected:
      SDL_Renderer* renderer ;
      SDL_Window* window ;
      int volume ; int stage ;
    public :
      Game();
      void Gamestart() ;
      void set_Renderer() ;
      SDL_Renderer* get_Renderer() ;
      void set_Window() ;
      void YOUWIN() ;
      void YOULOSS() ;
      void Mainmenu() ;
      void Sound() ;
      void Guide() ;
      void Regime() ;
      SDL_Window* get_Window() ;
};
