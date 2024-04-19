#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.hpp"


using namespace std;
using namespace CommonFunc ;
const char* WINDOW_TITLE = "SURVIVAL_MINE_V1.0";

Game::Game() {
    SDL_Window * window = CommonFunc::initSDL(SCREEN_WIDTH, SCREEN_HEIGHT,WINDOW_TITLE);
    renderer = CommonFunc::createRenderer(window);
}

void Game::Gamestart(){

    srand(time(NULL)) ;

    int cur_x = 0 , cur_y = 0 ;
    Player Mine ;

    SDL_Texture* BackGround = loadTexture("Background.png", this->renderer);

    vector<Entity*> sword ;
    CommonFunc::renderTexture( BackGround , 0 , 0 , this->renderer );

    SDL_RenderPresent( this->renderer );
    CommonFunc::waitUntilKeyPressed();

    Mine.resetInput() ;
    Mine.setTexture("Player.png", renderer );

    Mine.setX(500) ; Mine.setY(325) ;
    Mine.setWH(36 , 48) ;
    Mine.render(renderer) ;
    SDL_RenderPresent( renderer );

    SDL_Event e;
    std::vector<Enemy*> List_enemy ;
    std::vector<bat*> List_bat ;

    List_enemy.clear() ; List_bat.clear()  ;
    int timer = 0 ;
    Mine.setweapon( "bow.png" , renderer ) ;

    int weapon_type = 1 ;
    int Cannon_timer = -3000 ;

    int sword_angle = 0 ;
    while ( true ) {

        if ( Mine.getHP() <= 0 ){
            CommonFunc::quitSDL(window , renderer) ; // Player died
            break ;
        }

        timer += 50 ;

        if ( timer >= 1500 && List_enemy.size() < 15 ){
            Enemy* Su = new Enemy();
            Su->setNametexture( "tm" ) ;
            Su->setframe( 6 ) ;
            string cur_enemy_name = Su->getName() +(char('0' + Su->getsernum())) +".png";
            const char* s = cur_enemy_name.c_str() ;

            Su->setTexture( s , renderer ) ;
            Su->MOVETO( Mine.getX() , Mine.getY() , Su->getSP() ) ;
            List_enemy.push_back(Su) ;
        }

        if ( timer >= 5000 && List_bat.size() < 20 ){
            //cout << 1 <<"\n" ;
            bat* Su_bat = new bat();
            Su_bat->setNametexture( "bat" ) ;
            Su_bat->setframe( 8 ) ;
            string cur_enemy_name = Su_bat->getName() +(char('0' + Su_bat->getsernum())) +".png";
            const char* s_bat = cur_enemy_name.c_str() ;

            Su_bat->setTexture( s_bat , renderer ) ;
            Su_bat->MOVETO( Mine.getX() , Mine.getY() , Su_bat->getSP() ) ;

            List_bat.push_back(Su_bat) ;
            //cout << List_bat.size() ;
        }
//......................................pull event..............................................

        int z , t ;
        //Cannon_bullet_timer = timer - 1000 ;
        while(SDL_PollEvent(&e)){
                if ( e.type == SDL_QUIT )
                    exit(0);
                if ( e.type == SDL_KEYUP )
                    Mine.keyUp(&e.key);
                if ( e.type ==  SDL_KEYDOWN ){
                    Mine.keyDown(&e.key);

                    if ( e.key.keysym.scancode == SDL_SCANCODE_C ){
                        if ( timer - Cannon_timer >= 3000 ){
                           Cannon_timer = timer ;
                           //Cannon_bullet_timer = timer - 1000 ;
                           Mine.setweapon( "cannon.png" , renderer ) , weapon_type = 2 ;
                        }
                        else  Mine.setweapon( "bow.png" , renderer ) , weapon_type = 1;
                    }
                    else  if ( e.key.keysym.scancode == SDL_SCANCODE_K )
                        Mine.setweapon( "bow.png" , renderer ) , weapon_type = 1;
                }

                if ( e.type == SDL_MOUSEBUTTONDOWN ){

                   int x , y;
                    Uint32 buttons = SDL_GetMouseState(&x , &y);
                    Mine.mouseDown( x , y , weapon_type , renderer ) ;

                }
                if ( e.type == SDL_MOUSEMOTION )
                {
                    Uint32 buttons = SDL_GetMouseState(&z , &t);
                    Mine.mouseMove( z , t , renderer ) ;
                }
            Mine.move() ;
        }

        Mine.move() ;

        Mine.mouseMove( z , t , renderer ) ;

        int dif_map_x = cur_x ;
        int dif_map_y = cur_y ;

        cur_x += Mine.getox() ; cur_y += Mine.getoy() ;
        cur_x = max( 0 , min( cur_x , 1290 - 1000 ) ) ;
        cur_y = max( 0 , min( cur_y , 964 - 650 ) ) ;
        dif_map_x = cur_x - dif_map_x ;
        dif_map_y = cur_y - dif_map_y ;

        CommonFunc::ProrenderTexture( BackGround , cur_x , cur_y , 0 , 0 , 1000 , 650 , 1000 , 650 , renderer );
//.........................................sword.........................................................................
        //SDL_Texture* sword = loadTexture("sword.png", this->renderer);
        //RealrenderTexture( sword ,
        if ( sword.size() < 5 && timer >= 5000 * sword.size() ){
            Entity* sw = new Entity() ;
            sw->setTexture("sword.png" , renderer ) ;
               for ( int j = 0 ; j < sword.size() ; ++ j ){
                    Entity * N_sword = sword.at(j) ;
                    N_sword->setangle( j * 360 / (int)(sword.size()) ) ;
               }
             sword.push_back( sw ) ;
        }

        for ( int j = 0 ; j < sword.size() ; ++ j ){
            Entity * N_sword = sword.at(j) ;
            N_sword->setX( Mine.getX() + Mine.getW()/2 - N_sword->getW() ) ;
            N_sword->setY( Mine.getY() + Mine.getH()/2 - N_sword->getH() ) ;
            N_sword->setangle(double((int)((N_sword->getangle() + 20)) % 360) ) ;
            CommonFunc::swordrenderTexture( N_sword->getTexture() , N_sword->getW() , N_sword->getH() / 2 ,N_sword->getX() , N_sword->getY() , N_sword->getangle() , 0 , renderer ) ;
        }
        Mine.render(renderer) ;

        Mine.setWH(36 , 48) ;
//...........................................tm..............................................
        for ( int i = 0 ; i < List_enemy.size() ; ++ i ){
             Enemy* C_enemy = List_enemy.at(i) ;
             C_enemy->setX( C_enemy->getX() - dif_map_x) ;
             C_enemy->setY( C_enemy->getY() - dif_map_y) ;
        }
        for ( int i = 0 ; i < List_enemy.size() ; ++ i ){
            std::vector<Enemy*> L_list = List_enemy ;
            Enemy* C_enemy = L_list.at(i) ;
             if ( C_enemy->is_exist() ){
                C_enemy->updateframe() ;
                string cur_enemy_name = C_enemy->getName() +(char('0' + C_enemy->getsernum())) +".png";
                const char* s = cur_enemy_name.c_str() ;
                C_enemy->setTexture(s , renderer ) ;

                RealrenderTexture( C_enemy->getTexture() , C_enemy->getX()  , C_enemy->getY() , 0 ,( C_enemy->getX() > Mine.getX() ? 1 : 0 ) , renderer ) ;


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
//..........................bomer
                for ( int j = 0 ; j < Mine.Getbomlist().size() ; ++ j ){
                    std::vector<bom*> N_list = Mine.Getbomlist() ;
                    bom* Current_Bullet = N_list.at(j) ;
                    if ( Current_Bullet != NULL ){
                        if ( C_enemy->is_exist() && Current_Bullet->is_exist() && C_enemy->Coll(*Current_Bullet) ){
                            C_enemy->updHP() ;
                            Current_Bullet->updHP() ;
                            if ( Current_Bullet->get_order() == 0 )
                              Current_Bullet->upd_image(renderer) ;
                        }
                    }
                }
//..........................
            }
            else{
                L_list.erase(L_list.begin() + i) ;
                List_enemy = L_list ;
                C_enemy->release() ;
                delete C_enemy ;
            }
        }
//...............................Bat...............................................................
        for ( int i = 0 ; i < List_bat.size() ; ++ i ){
             bat* C_enemy = List_bat.at(i) ;
             C_enemy->setX( C_enemy->getX() - dif_map_x) ;
             C_enemy->setY( C_enemy->getY() - dif_map_y) ;
        }
        for ( int i = 0 ; i < List_bat.size() ; ++ i ){
            std::vector<bat*> L_list = List_bat ;
            bat* C_enemy = L_list.at(i) ;
             if ( C_enemy->is_exist() ){
                C_enemy->updateframe() ;
                string cur_enemy_name = C_enemy->getName() +(char('0' + C_enemy->getsernum())) +".png";
                const char* s = cur_enemy_name.c_str() ;
                C_enemy->setTexture(s , renderer ) ;

                RealrenderTexture( C_enemy->getTexture() , C_enemy->getX()  , C_enemy->getY() , 0 ,( C_enemy->getX() < Mine.getX() ? 1 : 0 ) , renderer ) ;

                //cout << 1 << "\n" ;
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
                for ( int j = 0 ; j < Mine.Getbomlist().size() ; ++ j ){
                    std::vector<bom*> N_list = Mine.Getbomlist() ;
                    bom* Current_Bullet = N_list.at(j) ;
                    if ( Current_Bullet != NULL ){
                        if ( C_enemy->is_exist() && Current_Bullet->is_exist() && C_enemy->Coll(*Current_Bullet) ){
                            C_enemy->updHP() ;
                            Current_Bullet->updHP() ;
                            if ( Current_Bullet->get_order() == 0 )
                              Current_Bullet->upd_image(renderer) ;
                        }
                    }
                }
            }
            else{
                L_list.erase(L_list.begin() + i) ;
                List_bat = L_list ;
                C_enemy->release() ;
                delete C_enemy ;
            }
        }
//.....................................bullet..................................................
         for ( int i = 0 ; i <Mine.GetBulletlist().size() ; ++ i ){
            std::vector<Bullet*> N_list = Mine.GetBulletlist() ;
            Bullet* Current_Bullet = N_list.at(i) ;
            if ( Current_Bullet != NULL ){
                if ( Current_Bullet->is_exist() ){
                        RealrenderTexture( Current_Bullet->getTexture(), Current_Bullet->getX() , Current_Bullet->getY(), Current_Bullet->getangle() , 0 ,  renderer);
                }
         }
         }
         for ( int i = 0 ; i <Mine.GetBulletlist().size() ; ++ i ){
                std::vector<Bullet*> N_list = Mine.GetBulletlist() ;
                Bullet* Current_Bullet = N_list.at(i) ;
                if ( Current_Bullet != NULL ){
                if ( Current_Bullet->is_exist() ){
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
//................................updbom.........................................................
        for ( int i = 0 ; i <Mine.Getbomlist().size() ; ++ i ){
            std::vector<bom*> N_list = Mine.Getbomlist() ;
            bom* Current_Bullet = N_list.at(i) ;
            if ( Current_Bullet != NULL ){
                if ( Current_Bullet->is_exist() ){
                    if ( Current_Bullet->get_order() == 0 )
                        RealrenderTexture( Current_Bullet->getTexture(), Current_Bullet->getX() , Current_Bullet->getY(), Current_Bullet->getangle() , 0 ,  renderer);
                    else
                        RealrenderTexture( Current_Bullet->getTexture(), Current_Bullet->getX() , Current_Bullet->getY(), 0 , 0 ,  renderer);
                }
         }
         }
         for ( int i = 0 ; i <Mine.Getbomlist().size() ; ++ i ){
                std::vector<bom*> N_list = Mine.Getbomlist() ;
                bom* Current_Bullet = N_list.at(i) ;
                if ( Current_Bullet != NULL ){
                if ( Current_Bullet->is_exist() && Current_Bullet->get_order() == 0 ){
                        Current_Bullet->move() ;
                } else if ( !Current_Bullet->is_exist() ){
                        N_list.erase( N_list.begin() + i ) ;
                        Mine.setbomlist(N_list) ;
                        Current_Bullet->release() ;
                        delete Current_Bullet ;
                        Current_Bullet = NULL ;
                    }
                   else{
                        Current_Bullet->upd_image(renderer) ;
                   }
                }
         }
         CommonFunc::RealrenderTexture( Mine.getweapon()->getTexture() , Mine.getweapon()->getX() ,  Mine.getweapon()->getY() ,  Mine.getweapon()->getangle() , 0 , renderer ) ;
         SDL_RenderPresent( renderer );
         SDL_Delay(50) ;
    }

    Mine.release() ;
    SDL_DestroyTexture( BackGround );
    BackGround = NULL;

    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    CommonFunc::quitSDL(window, renderer);
}
