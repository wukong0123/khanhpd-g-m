#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.hpp"


using namespace std;

const char* WINDOW_TITLE = "SURVIVAL_MINE_V1.0";

Game::Game() {
    SDL_Window * window = CommonFunc::initSDL(SCREEN_WIDTH, SCREEN_HEIGHT,WINDOW_TITLE);
    renderer = CommonFunc::createRenderer(window);
}

void Game::Gamestart(){

    srand(time(NULL)) ;


    Player Mine ;

    SDL_Texture* BackGround = CommonFunc::loadTexture("Back_ground.jpg", this->renderer);

    CommonFunc::renderTexture( BackGround , 0 , 0 , this->renderer );

    SDL_RenderPresent( this->renderer );
    CommonFunc::waitUntilKeyPressed();

    Mine.resetInput() ;
    Mine.setTexture("UFO.png", renderer);

    Mine.setX(500) ; Mine.setY(325) ;
    CommonFunc::renderTexture( Mine.getTexture(), Mine.getX() , Mine.getY() , renderer);
    SDL_RenderPresent( renderer );

    SDL_Event e;
    std::vector<Enemy*> List_enemy ;
    List_enemy.clear() ;
    while ( true ) {

        if ( Mine.getHP() <= 0 ){
            CommonFunc::quitSDL(window , renderer) ;
            break ;
        }

        if ( List_enemy.size() < 5 ){
            Enemy* Su = new Enemy();
            Su->setTexture("Enemy.png" , renderer) ;
            Su->MOVETO( Mine.getX() , Mine.getY() , Su->getSP() ) ;
            List_enemy.push_back(Su) ;
        }
        while(SDL_PollEvent(&e)){
            if ( e.type == SDL_MOUSEMOTION ) continue ;
            switch(e.type){
                case SDL_QUIT:
                    exit(0);
                    break;
                case SDL_KEYUP:
                    Mine.keyUp(&e.key);
                    break;
                case SDL_KEYDOWN:
                    Mine.keyDown(&e.key);
                    break;
                case SDL_MOUSEBUTTONDOWN :
                    int x , y;
                    Uint32 buttons = SDL_GetMouseState(&x , &y);
                    Mine.mouseDown( x , y , renderer ) ;
                    break;
            }
            Mine.move() ;
        }
         CommonFunc::renderTexture( BackGround , 0 , 0 , renderer );
         CommonFunc::renderTexture( Mine.getTexture(), Mine.getX() , Mine.getY(), renderer);

        for ( int i = 0 ; i < List_enemy.size() ; ++ i ){
            std::vector<Enemy*> L_list = List_enemy ;
            Enemy* C_enemy = L_list.at(i) ;
             if ( C_enemy->is_exist() ){
                CommonFunc::renderTexture( C_enemy->getTexture() , C_enemy->getX() , C_enemy->getY() , renderer ) ;
                C_enemy->MOVETO( Mine.getX() , Mine.getY() , C_enemy->getSP() ) ;
                C_enemy->move() ;
                if (  C_enemy->Coll(Mine) ){
                    C_enemy->updHP() ;
                    Mine.updHP() ;
                }
                for ( int j = 0 ; j < Mine.GetBulletlist().size() ; ++ j ){
                    std::vector<Bullet*> N_list = Mine.GetBulletlist() ;
                    Bullet* Current_Bullet = N_list.at(j) ;
                    if ( Current_Bullet != NULL ){
                        if ( C_enemy->is_exist() && Current_Bullet->is_exist() && C_enemy->Coll(*Current_Bullet) ){
                            C_enemy->updHP() ;
                            Current_Bullet->updHP() ;
                        }
                    }
                }
            }
            else{
                L_list.erase(L_list.begin() + i) ;
                List_enemy = L_list ;
                C_enemy->release() ;
                delete C_enemy ;
            }
        }
         for ( int i = 0 ; i <Mine.GetBulletlist().size() ; ++ i ){
                std::vector<Bullet*> N_list = Mine.GetBulletlist() ;
                Bullet* Current_Bullet = N_list.at(i) ;
                if ( Current_Bullet != NULL ){
                if ( Current_Bullet->is_exist() ){
                        CommonFunc::renderTexture( Current_Bullet->getTexture(), Current_Bullet->getX() , Current_Bullet->getY(), renderer);
                        Current_Bullet->move() ;
                } else {
                        N_list.erase( N_list.begin() + i ) ;
                        Mine.setbulletlist(N_list) ;
                        Current_Bullet->release() ;
                        delete Current_Bullet ;
                        Current_Bullet = NULL ;
                    }
                }
         }
         SDL_RenderPresent( renderer );
    }

    Mine.release() ;
    SDL_DestroyTexture( BackGround );
    BackGround = NULL;

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    CommonFunc::quitSDL(window, renderer);
}
