#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 650;
const int BULLET_WIDTH = 20 ;
const int BULLET_HEIGHT = 650 ;

static Mix_Chunk* kick ;
static Mix_Chunk* roar ;
static Mix_Chunk* smenu ;
static Mix_Chunk* explosion ;
static Mix_Chunk* click ;
static Mix_Chunk* duel ;
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
  pair<int,int> getPosmovemouse( int , int , int , int ,int , int, double , double ) ;
  void RealrenderTexture(SDL_Texture *, double , double , double , bool , SDL_Renderer*) ;
  void swordrenderTexture(SDL_Texture *, int , int , double , double , double , bool , SDL_Renderer*) ;
  bool IS_ATC( int , int , int , int , int , int ) ;

}

