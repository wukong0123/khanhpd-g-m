#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;
const int BULLET_WIDTH = 20 ;
const int BULLET_HEIGHT = 650 ;
//static SDL_Texture *BGR = NULL ;
//static SDL_Event g_even ;
using namespace std ;
namespace CommonFunc{

  void logErrorAndExit(const char*, const char* ) ;

  SDL_Window* initSDL(int , int , const char* ) ;
  SDL_Renderer* createRenderer(SDL_Window* ) ;
  void quitSDL(SDL_Window* , SDL_Renderer*) ;
  void waitUntilKeyPressed() ;

  void renderTexture(SDL_Texture *, double , double , SDL_Renderer* ) ;

  SDL_Texture *loadTexture(const char *, SDL_Renderer* ) ;
  int genRDNumber( int , int ) ;
  bool IS_ATC( int , int , int , int , int , int ) ;
}

