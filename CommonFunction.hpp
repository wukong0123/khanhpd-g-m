#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;
const int BULLET_WIDTH = 20 ;
const int BULLET_HEIGHT = 650 ;

using namespace std ;
namespace CommonFunc{

  void logErrorAndExit(const char*, const char* ) ;

  SDL_Window* initSDL(int , int , const char* ) ;
  SDL_Renderer* createRenderer(SDL_Window* ) ;
  void quitSDL(SDL_Window* , SDL_Renderer*) ;
  void waitUntilKeyPressed() ;

  void renderTexture(SDL_Texture *, double , double , SDL_Renderer* ) ;
  void ProrenderTexture(SDL_Texture *, double , double , double , double , double , double , double , double , SDL_Renderer* ) ;
  SDL_Texture *loadTexture(const char *, SDL_Renderer* ) ;
  int genRDNumber( int , int ) ;
  void render(SDL_Renderer * ) ;
  double getangle( int , int ) ;
  pair<int,int> getPosmovemouse( int , int , int , int , pair<int , int> , pair<int , int> ) ;
  void RealrenderTexture(SDL_Texture *, double , double , double , bool , SDL_Renderer*) ;
  bool IS_ATC( int , int , int , int , int , int ) ;
}

