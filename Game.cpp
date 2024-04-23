#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.hpp"


using namespace std;
using namespace CommonFunc ;
const char* WINDOW_TITLE = "SURVIVAL_MINE_V1.0";
const double fps = 30 ;

int ADDX[] = { 1 , -1 , 1 , -1 } ;
int ADDY[] = { -1 , -1 , -1 , -1 } ;

Game::Game() {
    SDL_Window * window = CommonFunc::initSDL(SCREEN_WIDTH, SCREEN_HEIGHT,WINDOW_TITLE);
    renderer = CommonFunc::createRenderer(window);
}

void Game::Gamestart(){

    srand(time(NULL)) ;

    int cur_x = 0 , cur_y = 0 ;
    Player Mine ;

    int Boss_bullet_status = 0 ;
    SDL_Texture* BackGround = loadTexture("Background.png", this->renderer);
    SDL_Texture* BG = loadTexture("Newbackground.png", this->renderer);
    vector<Entity*> swords ;
    CommonFunc::renderTexture( BackGround , 0 , 0 , this->renderer );

    SDL_RenderPresent( this->renderer );
    CommonFunc::waitUntilKeyPressed();
//..........................................Texture.................................................

    SDL_Texture * tPlayer = loadTexture("Player.png", this->renderer);
    SDL_Texture * tbow = loadTexture("bow.png", this->renderer);
    SDL_Texture * tcannon = loadTexture("cannon.png", this->renderer);
    SDL_Texture * tbullet = loadTexture("bullet.png" , renderer ) ;
    SDL_Texture * tmbullet = loadTexture("magic_bullet.png" , renderer ) ;
    SDL_Texture * sword = loadTexture("sword.png" , renderer ) ;
    vector<SDL_Texture *> fires , magicians , tms , boms , bats , Tboss[4] , boss_skill ;
    boms.push_back( loadTexture("bom.png" , renderer )  ) ;
    for ( int i = 1 ; i <= 4 ; ++ i ){
        string s = "bossskill"  ;
        s = s + char( i + '0' ) + ".png"  ;
        boss_skill.push_back(loadTexture(s.c_str() , renderer )) ;
    }
    for ( int i = 1 ; i <= 8 ; ++ i ){
        string s = "bat"  ;
        s = s + char( i + '0' ) + ".png"  ;
        cout << s << "\n" ;
        bats.push_back( loadTexture(s.c_str() , renderer ) ) ;
        s = "fire"  ;
        s = s + char( i + '0' ) + ".png"  ;
        fires.push_back( loadTexture(s.c_str() , renderer ) ) ;
        s = "boom"  ;
        s = s + char( i + '0' ) + ".png"  ;
        boms.push_back( loadTexture(s.c_str() , renderer ) ) ;
    }
    for ( int i = 1 ; i <= 5 ; ++ i ){
        string s = "magician"  ;
        s = s + char( i + '0' ) + ".png"  ;
        magicians.push_back( loadTexture(s.c_str() , renderer ) ) ;
    }
    for ( int i = 1 ; i <= 6 ; ++ i ){
        string s = "tm"  ;
        s = s + char( i + '0' ) + ".png"  ;
        tms.push_back( loadTexture(s.c_str() , renderer ) ) ;
    }

    for ( int i = 0 ; i < 20 ; ++ i ){
        string s = "./bossdied" ;
        s = s + "/frame_" + char( i / 10 + '0' ) + char( i % 10 + '0' ) +  "_delay-0.04s.png" ;
        Tboss[3].push_back( loadTexture( s.c_str() , renderer ) ) ;
    }
    for ( int i = 0 ; i < 36 ; ++ i ){
        string s = "./bossmove" ;
        s = s + "/frame_" + char( i / 10 + '0' ) + char( i % 10 + '0' ) +  "_delay-0.04s.png" ;
        Tboss[0].push_back( loadTexture( s.c_str() , renderer ) ) ;
    }
    for ( int i = 0 ; i < 26 ; ++ i ){
        string s = "./bossskill" ;
        s = s + "/frame_" + char( i / 10 + '0' ) + char( i % 10 + '0' ) +  "_delay-0.04s.png" ;
        Tboss[1].push_back( loadTexture( s.c_str() , renderer ) ) ;
    }
    for ( int i = 0 ; i < 24 ; ++ i ){
        string s = "./bossstand" ;
        s = s + "/frame_" + char( i / 10 + '0' ) + char( i % 10 + '0' ) +  "_delay-0.04s.png" ;
        Tboss[2].push_back( loadTexture( s.c_str() , renderer ) ) ;
    }

//.............................................................................................

    Mine.resetInput() ;
    Mine.setTexture(tPlayer, renderer );

    Mine.setX(500) ; Mine.setY(325) ;
    Mine.setWH(36 , 48) ;
    Mine.render(renderer) ;

    SDL_RenderPresent( renderer );

    boss* Main_boss = new boss() ;
    Main_boss->setstatus( 0 ) ;

    SDL_Event e;
    std::vector<Enemy*> List_enemy ;
    std::vector<bat*> List_bat ;

    std::vector<magician*> List_magic ;
    std::vector<mbullet*> Enemy_bullet ;

    List_enemy.clear() ; List_bat.clear()  ;
    int timer = 0 ;

    Mine.setweapon( tbow , renderer ) ;

    int weapon_type = 1 ;
    int Cannon_timer = -3000 ;

    unsigned int Cur_ticks = SDL_GetTicks();
    unsigned int New_ticks = SDL_GetTicks();
    double delta = 0;

    int sword_angle = 0 ;
    while ( true ) {

        if ( Mine.getHP() <= 0 ){
            CommonFunc::quitSDL(window , renderer) ; // Player died
            break ;
        }

        timer += 50 ;

        if ( timer >= 1500 && List_enemy.size() < 15 ){
            Enemy* Su = new Enemy();
            Su->setframe( 6 ) ;

            Su->setTexture( tms[ Su->getsernum()-1] , renderer ) ;
            Su->MOVETO( Mine.getX() , Mine.getY() , Su->getSP() ) ;
            List_enemy.push_back(Su) ;
        }

        if ( timer >= 5000 && List_bat.size() < 20 ){
            bat* Su_bat = new bat();
            Su_bat->setframe( 8 ) ;
            Su_bat->setTexture( bats[Su_bat->getsernum()-1] , renderer ) ;
            Su_bat->MOVETO( Mine.getX() , Mine.getY() , Su_bat->getSP() ) ;

            List_bat.push_back(Su_bat) ;
        }
        if ( timer >= 8000 && List_magic.size() < 2 ){
            //cout << 1 <<"\n" ;
            magician* Su_bat = new magician();
            Su_bat->setframe( 5 ) ;

            Su_bat->setTexture( magicians[Su_bat->getsernum()-1] , renderer ) ;
            Su_bat->MOVETO( Mine.getX() , Mine.getY() , Su_bat->getSP() ) ;

            List_magic.push_back(Su_bat) ;
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
                           Mine.setweapon( tcannon, renderer ) , weapon_type = 2 ;
                        }
                        else  Mine.setweapon( tbow , renderer ) , weapon_type = 1;
                    }
                    else  if ( e.key.keysym.scancode == SDL_SCANCODE_K )
                        Mine.setweapon( tbow , renderer ) , weapon_type = 1;
                }

                if ( e.type == SDL_MOUSEBUTTONDOWN ){

                   int x , y;
                    Uint32 buttons = SDL_GetMouseState(&x , &y);
                    Mine.mouseDown( x , y , weapon_type , tbullet , boms[0] ,  renderer ) ;

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

        if ( swords.size() < 5 && timer >= 5000 * swords.size() ){
            Entity* sw = new Entity() ;
            sw->setTexture( sword , renderer ) ;
               for ( int j = 0 ; j < swords.size() ; ++ j ){
                    Entity * N_sword = swords.at(j) ;
                    N_sword->setangle( j * 360 / (int)(swords.size()) ) ;
               }
             swords.push_back( sw ) ;
        }

        for ( int j = 0 ; j < swords.size() ; ++ j ){
            Entity * N_sword = swords.at(j) ;
            N_sword->setX( Mine.getX() + Mine.getW()/2 - N_sword->getW() ) ;
            N_sword->setY( Mine.getY() + Mine.getH()/2 - N_sword->getH() ) ;
            N_sword->setangle(double((int)((N_sword->getangle() + 20)) % 360) ) ;
            CommonFunc::swordrenderTexture( N_sword->getTexture() , N_sword->getW() , N_sword->getH() / 2 ,N_sword->getX() , N_sword->getY() , N_sword->getangle() , 0 , renderer ) ;
        }
        Mine.render(renderer) ;

        Mine.setWH(36 , 48) ;

        if ( timer < 10000 ){
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

                    C_enemy->setTexture( tms[ C_enemy->getsernum()-1] , renderer ) ;

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
                                if ( Current_Bullet->get_order() == 0 ){
                                    Current_Bullet->upd_order() ;
                                    Current_Bullet->upd_image(renderer , boms[Current_Bullet->get_order()]) ;
                                }
                            }
                        }
                    }
                //..........................

                    for ( int j = 0 ; j < swords.size() ; ++ j ){
                        Entity* Current_Bullet = swords.at(j) ;
                            double Mid_x = C_enemy->getX() + C_enemy->getW() / 2 ;
                            double Mid_y = C_enemy->getY() + C_enemy->getH() / 2 ;
                            double Mid_mine_x = Mine.getX() + Mine.getW() / 2 ;
                            double Mid_mine_y = Mine.getY() + Mine.getH() / 2 ;
                            double delta_angle = ((((int)(atan2( Mid_x - Mid_mine_x  , Mid_mine_y - Mid_y ) * (180 / M_PI)) + 360)) % 360 ) - ((int)( Current_Bullet->getangle() - 90 + 360 ) % 360 );
                            double distance =  sqrt( ( Mid_mine_x - Mid_x ) * ( ( Mid_mine_x - Mid_x ) ) + ( Mid_mine_y - Mid_y ) * ( Mid_mine_y - Mid_y )) ;
                            //cout << delta_angle <<' ' << distance << "\n" ;
                            if ( C_enemy->is_exist() && delta_angle <= 21 && distance <= 130 ){
                                //cout << "-------------------" << "\n" ;
                                C_enemy->updHP() ;
                            }
                    }
                }
                else{
                    L_list.erase(L_list.begin() + i) ;
                    List_enemy = L_list ;
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

                    C_enemy->setTexture( bats[C_enemy->getsernum() - 1] , renderer ) ;

                    RealrenderTexture( C_enemy->getTexture() , C_enemy->getX()  , C_enemy->getY() , 0 ,( C_enemy->getX() < Mine.getX() ? 1 : 0 ) , renderer ) ;

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
                                if ( Current_Bullet->get_order() == 0 ){
                                    Current_Bullet->upd_order() ;
                                    Current_Bullet->upd_image(renderer , boms[Current_Bullet->get_order()]) ;
                                }

                            }
                        }
                    }
                    for ( int j = 0 ; j < swords.size() ; ++ j ){
                        Entity* Current_Bullet = swords.at(j) ;
                            double Mid_x = C_enemy->getX() + C_enemy->getW() / 2 ;
                            double Mid_y = C_enemy->getY() + C_enemy->getH() / 2 ;
                            double Mid_mine_x = Mine.getX() + Mine.getW() / 2 ;
                            double Mid_mine_y = Mine.getY() + Mine.getH() / 2 ;
                            double delta_angle = ((((int)(atan2( Mid_x - Mid_mine_x  , Mid_mine_y - Mid_y ) * (180 / M_PI)) + 360)) % 360 ) - ((int)( Current_Bullet->getangle() - 90 + 360 ) % 360 );
                            double distance =  sqrt( ( Mid_mine_x - Mid_x ) * ( ( Mid_mine_x - Mid_x ) ) + ( Mid_mine_y - Mid_y ) * ( Mid_mine_y - Mid_y )) ;
                            //cout << delta_angle <<' ' << distance << "\n" ;
                            if ( C_enemy->is_exist() && delta_angle <= 21 && distance <= 130 ){
                                //cout << "-------------------" << "\n" ;
                                C_enemy->updHP() ;
                            }
                    }
                }
                else{
                    L_list.erase(L_list.begin() + i) ;
                    List_bat = L_list ;
                    delete C_enemy ;
                }
            }
    //.....................................magician................................................

            for ( int i = 0 ; i < List_magic.size() ; ++ i ){
                 magician* C_enemy = List_magic.at(i) ;
                 C_enemy->setX( C_enemy->getX() - dif_map_x) ;
                 C_enemy->setY( C_enemy->getY() - dif_map_y) ;
            }
            for ( int i = 0 ; i < List_magic.size() ; ++ i ){
                std::vector<magician*> L_list = List_magic ;
                magician* C_enemy = L_list.at(i) ;
                 if ( C_enemy->is_exist() ){
                    C_enemy->updateframe() ;

                    if ( timer - C_enemy->getbullettimer() > 5000 ){
                        C_enemy->setbullettimer( timer ) ;
                        mbullet* curbullet = new mbullet() ;
                        curbullet->setX( C_enemy->getX() + C_enemy->getW() / 2 ) ;
                        curbullet->setY( C_enemy->getY() + C_enemy->getH() / 2 ) ;

                        curbullet->setTexture( tmbullet , renderer ) ;

                        curbullet->MOVETO( Mine.getX() , Mine.getY() , curbullet->getSP() ) ;
                        Enemy_bullet.push_back( curbullet ) ;
                    }

                    C_enemy->setTexture( magicians[C_enemy->getsernum() - 1] , renderer ) ;

                    RealrenderTexture( C_enemy->getTexture() , C_enemy->getX()  , C_enemy->getY() , 0 ,( C_enemy->getX() < Mine.getX() ? 1 : 0 ) , renderer ) ;

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
                                if ( Current_Bullet->get_order() == 0 ){
                                    Current_Bullet->upd_order() ;
                                    Current_Bullet->upd_image(renderer , boms[Current_Bullet->get_order()]) ;
                                }

                            }
                        }
                    }
                    for ( int j = 0 ; j < swords.size() ; ++ j ){
                        Entity* Current_Bullet = swords.at(j) ;
                            double Mid_x = C_enemy->getX() + C_enemy->getW() / 2 ;
                            double Mid_y = C_enemy->getY() + C_enemy->getH() / 2 ;
                            double Mid_mine_x = Mine.getX() + Mine.getW() / 2 ;
                            double Mid_mine_y = Mine.getY() + Mine.getH() / 2 ;
                            double delta_angle = ((((int)(atan2( Mid_x - Mid_mine_x  , Mid_mine_y - Mid_y ) * (180 / M_PI)) + 360)) % 360 ) - ((int)( Current_Bullet->getangle() - 90 + 360 ) % 360 );
                            double distance =  sqrt( ( Mid_mine_x - Mid_x ) * ( ( Mid_mine_x - Mid_x ) ) + ( Mid_mine_y - Mid_y ) * ( Mid_mine_y - Mid_y )) ;
                            //cout << delta_angle <<' ' << distance << "\n" ;
                            if ( C_enemy->is_exist() && delta_angle <= 21 && distance <= 130 ){
                                //cout << "-------------------" << "\n" ;
                                C_enemy->updHP() ;
                            }
                    }
                }
                else{
                    L_list.erase(L_list.begin() + i) ;
                    List_magic = L_list ;
                    delete C_enemy ;
                }
            }
    //.....................................upd_magic_bullet..................................................

             for ( int i = 0 ; i < Enemy_bullet.size() ; ++ i ){
                std::vector<mbullet*> N_list = Enemy_bullet;
                mbullet* Current_Bullet = N_list.at(i) ;
                if ( Current_Bullet != NULL ){
                    if ( Current_Bullet->is_exist() ){
                            Current_Bullet->upd_timer() ;
                            if ( Current_Bullet->getexistedtimer() >= 2000 ){
                                if ( Current_Bullet->getexistedtimer() - 50 < 2000){
                                    Current_Bullet->setX(Current_Bullet->getX() - 20 ) ;
                                    Current_Bullet->setY(Current_Bullet->getY() - 50 ) ;
                                }
                                Current_Bullet->upd_order() ;
                                Current_Bullet->upd_image(renderer , fires[Current_Bullet->get_order() - 1] ) ;
                            }
                            RealrenderTexture( Current_Bullet->getTexture(), Current_Bullet->getX() , Current_Bullet->getY(), Current_Bullet->getangle() , 0 ,  renderer);
                            if ( Current_Bullet->Coll(Mine) ){
                                Mine.updHP() ;
                            }
                    }
                }
             }
             for ( int i = 0 ; i < Enemy_bullet.size() ; ++ i ){
                    std::vector<mbullet*> N_list = Enemy_bullet ;
                    mbullet* Current_Bullet = N_list.at(i) ;
                    if ( Current_Bullet != NULL ){
                    if ( Current_Bullet->is_exist() && Current_Bullet->get_order() == 0 ){
                            Current_Bullet->move() ;
                    } else if ( !Current_Bullet->is_exist() ) {
                            N_list.erase( N_list.begin() + i ) ;
                            Enemy_bullet = N_list ;
                            delete Current_Bullet ;
                            Current_Bullet = NULL ;
                        }
                    }
             }
        } else
//        if ( timer > 120000 && timer < 123000 ){
//        /// xu li mid game
//        } else
        {
                BackGround = BG ;
                if ( Main_boss->is_exist() ){
                    if ( Boss_bullet_status < 1 && Main_boss->getstatus() == 1 ){
                        // them nhat chem cho quai
                    }
                    else if ( Main_boss->getstatus() != 1 ) Boss_bullet_status = 0 ;

                    Main_boss->setTexture( Tboss[Main_boss->getstatus()][Main_boss->getsernum()-1] , renderer ) ;
                    Main_boss->updateframe() ;

                    RealrenderTexture( Main_boss->getTexture() , Main_boss->getX()  , Main_boss->getY() , 0 , Main_boss->getflip() , renderer ) ;
                    if ( Main_boss->getstatus() == 0 ) {
                        Main_boss->move() ;
                        cout << Main_boss->getX() +  Main_boss->getW() / 2 << ' ' << Main_boss->getY() +  Main_boss->getH() / 2  << "\n" ;
                    }

                    if (  Main_boss->Coll( Mine ) ){
                        Main_boss->updHP() ;
                        Mine.updHP() ;
                    }
                    boss* C_enemy = Main_boss ;
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
                                    if ( Current_Bullet->get_order() == 0 ){
                                        Current_Bullet->upd_order() ;
                                        Current_Bullet->upd_image(renderer , boms[Current_Bullet->get_order()]) ;
                                    }

                                }
                            }
                        }
                        for ( int j = 0 ; j < swords.size() ; ++ j ){
                            Entity* Current_Bullet = swords.at(j) ;
                                double Mid_x = C_enemy->getX() + C_enemy->getW() / 2 ;
                                double Mid_y = C_enemy->getY() + C_enemy->getH() / 2 ;
                                double Mid_mine_x = Mine.getX() + Mine.getW() / 2 ;
                                double Mid_mine_y = Mine.getY() + Mine.getH() / 2 ;
                                double delta_angle = ((((int)(atan2( Mid_x - Mid_mine_x  , Mid_mine_y - Mid_y ) * (180 / M_PI)) + 360)) % 360 ) - ((int)( Current_Bullet->getangle() - 90 + 360 ) % 360 );
                                double distance =  sqrt( ( Mid_mine_x - Mid_x ) * ( ( Mid_mine_x - Mid_x ) ) + ( Mid_mine_y - Mid_y ) * ( Mid_mine_y - Mid_y )) ;
                                if ( C_enemy->is_exist() && delta_angle <= 21 && distance <= 130 ){
                                    C_enemy->updHP() ;
                                }
                        }

                }

        }
//.....................................updbullet..................................................
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
                        delete Current_Bullet ;
                        Current_Bullet = NULL ;
                    }
                   else{
                        Current_Bullet->upd_order() ;
                        if ( Current_Bullet->is_exist() )
                        Current_Bullet->upd_image(renderer , boms[Current_Bullet->get_order()]) ;
                   }
                }
         }
         CommonFunc::RealrenderTexture( Mine.getweapon()->getTexture() , Mine.getweapon()->getX() ,  Mine.getweapon()->getY() ,  Mine.getweapon()->getangle() , 0 , renderer ) ;
         SDL_RenderPresent( renderer );
         SDL_Delay(50) ;
    }

   // BackGround = loadTexture("Newbackground.png", this->renderer);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    CommonFunc::quitSDL(window, renderer);
}
