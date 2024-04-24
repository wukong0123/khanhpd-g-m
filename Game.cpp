#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "Game.hpp"


using namespace std;
using namespace CommonFunc ;
const char* WINDOW_TITLE = "Zelda Survival Game";
const double fps = 30 ;

int ADDX[] = { 1 , -1 , 1 , -1 } ;
int ADDY[] = { -1 , -1 , -1 , -1 } ;

Game::Game() {
    SDL_Window * window = CommonFunc::initSDL(SCREEN_WIDTH, SCREEN_HEIGHT,WINDOW_TITLE);
    renderer = CommonFunc::createRenderer(window);
}
void Game::Mainmenu(){
    TTF_Font * gfont = TTF_OpenFont( "Main.ttf", 20 );
    TTF_Font * realfont = TTF_OpenFont( "China.ttf", 90 );
    TTF_Font * cfont = TTF_OpenFont( "menu.ttf", 50 );
    TTF_Font * tofont = TTF_OpenFont( "menu.ttf", 70 );

    SDL_Color White = { 255 , 255 , 255 } ;
    SDL_Color Black = { 0 , 0 , 0 } ;
    SDL_Color Blue = { 0 , 0 , 255 } ;
    SDL_Color Green = { 0 , 255 , 0 } ;

    SDL_Texture* BackGround = loadTexture("MainMenu.png", this->renderer);
    renderTexture( BackGround , 0 , 0 , this->renderer );
    TTF* Play = new TTF() ;TTF* Regime = new TTF() ; TTF* Guide = new TTF() ; TTF* Sound = new TTF() ;
    TTF* Tittle = new TTF() ;
    Tittle->setTTFTexture(0,0,"Zelda Survival Game" , Black , realfont , renderer ) ; Tittle->setmid( 500 , 100 + 100 ) ;
    Play->setTTFTexture( 0 , 0 , "Start Game" , Green , cfont , renderer ) ; Play->setmid(500 ,170 + 150) ;
    Regime->setTTFTexture( 0 , 0 , "Regime" , Green , cfont , renderer ) ; Regime->setmid(500 , 240 + 150 + 20 ) ;
    Guide->setTTFTexture( 0 , 0 , "Guide" , Green , cfont , renderer ) ; Guide->setmid(500 , 310 + 150 + 40 ) ;
    Sound->setTTFTexture( 0 , 0 , "Sound" , Green , cfont , renderer ) ; Sound->setmid(500 , 380 + 150 + 60) ;
    Tittle->render(renderer) ; Play->render(renderer) ; Regime->render(renderer) ; Guide->render(renderer) ; Sound->render(renderer) ;

    SDL_RenderPresent(renderer) ;

    SDL_Event e ;
    SDL_Color Cplay , Cregime , Cguide , Csound ;
    TTF_Font * Fplay = cfont ;
    TTF_Font * Fregime = cfont ;
    TTF_Font * Fguide = cfont ;
    TTF_Font * Fsound = cfont ;
    //, Fregime , Fguide , Fsound ;

    roar = Mix_LoadWAV("roar.wav");
    smenu = Mix_LoadWAV("menu.wav") ;
    kick = Mix_LoadWAV("kick.wav") ;
    explosion = Mix_LoadWAV("explosion.wav") ;

    Mix_PlayChannel(-1 , smenu , 1) ;
    while( true ){

        renderTexture( BackGround , 0 , 0 , this->renderer );
        Tittle->setTTFTexture(0,0,"Zelda Survival Game" , Black , realfont , renderer ) ; Tittle->setmid( 500 , 100 + 100 ) ;
        Cplay = Green ;  Cregime = Green ;  Cguide = Green ;  Csound = Green ;
        Fplay = cfont ; Fregime= cfont ; Fguide = cfont ; Fsound = cfont ;
        int z , t ;
        while(SDL_PollEvent(&e)){
            if ( e.type == SDL_QUIT )
                exit(0);
            if ( e.type == SDL_MOUSEBUTTONDOWN ){
                int x , y;
                Mix_PlayChannel(-1 , kick , 0) ;
                Uint32 buttons = SDL_GetMouseState(&x , &y);
                if ( Play->is_coll(x , y) ) {
                    this->Gamestart() ;
                    Mix_CloseAudio();
                    Mix_FreeChunk(roar) ; Mix_FreeChunk(smenu) ; Mix_FreeChunk(kick) ; Mix_FreeChunk(explosion) ;
                }
                Mix_PlayChannel(-1 , kick , 0) ;
            }
            //Uint32 buttons = SDL_GetMouseState(&z , &t);
        }

        Uint32 buttons = SDL_GetMouseState(&z , &t);
        if ( Play->is_coll(z , t) ){
            Fplay = tofont ; Cplay = Blue ;
        }
        if ( Regime->is_coll(z , t) ){
            Fregime = tofont ; Cregime = Blue ;
        }
        if ( Sound->is_coll(z , t) ){
            Fsound = tofont ; Csound = Blue ;
        }
        if ( Guide->is_coll(z , t) ){
            Fguide = tofont ; Cguide = Blue ;
        }
        Tittle->setTTFTexture(0,0,"Zelda Survival Game" , Black , realfont , renderer ) ; Tittle->setmid( 500 , 100 + 100 ) ;
        Play->setTTFTexture( 0 , 0 , "Start Game" , Cplay , Fplay, renderer ) ; Play->setmid(500 ,170 + 150) ;
        Regime->setTTFTexture( 0 , 0 , "Regime" , Cregime , Fregime , renderer ) ; Regime->setmid(500 , 240 + 150 + 20 ) ;
        Guide->setTTFTexture( 0 , 0 , "Guide" , Cguide , Fguide , renderer ) ; Guide->setmid(500 , 310 + 150 + 40 ) ;
        Sound->setTTFTexture( 0 , 0 , "Sound" , Csound , Fsound , renderer ) ; Sound->setmid(500 , 380 + 150 + 60) ;
        Tittle->render(renderer) ; Play->render(renderer) ; Regime->render(renderer) ; Guide->render(renderer) ; Sound->render(renderer) ;

        SDL_RenderPresent(renderer) ;
    }


}
void Game::YOULOSS(){

    TTF_Font * xfont = TTF_OpenFont( "menu.ttf", 20 );
    TTF_Font * gfont = TTF_OpenFont( "Atop-R99O3.ttf", 20 );
    TTF_Font * realfont = TTF_OpenFont( "menu.ttf", 50 );
    TTF_Font * cfont = TTF_OpenFont( "menu.ttf", 30 );
    SDL_Color White = { 255 , 255 , 255 } ;
    SDL_Color Black = { 0 , 0 , 0 } ;
//    SDL_Texture* BackGround = loadTexture("Background.png", this->renderer);
//    renderTexture( BackGround , 0 , 0 , this->renderer );

    TTF* resume = new TTF() ; resume->setTTFTexture( 0 , 0 , "You Loss!" , Black , realfont , renderer ) ;
    resume->setX( 500 - resume->getW() / 2 ) ; resume->setY( 350 - resume->getH()  * 2 ) ;
    TTF* bomer = new TTF() ; bomer->setTTFTexture( 0 , 0 , "Press G to play again" , Black , cfont , renderer ) ;
    bomer->setX( 500 - bomer->getW() / 2 ) ; bomer->setY( 350 - bomer->getH() + 10 ) ;
    TTF* sws = new TTF() ; sws->setTTFTexture( 0 , 0 , "Press Q to exit game" , Black , cfont , renderer ) ;
    sws->setX( 500 - sws->getW() / 2 ) ; sws->setY( 350 + 20 ) ;

    RealrenderTexture( resume->getTexture() , resume->getX() , resume->getY() , 0 , 0 , renderer ) ;
    RealrenderTexture( sws->getTexture() , sws->getX() , sws->getY() , 0 , 0 , renderer ) ;
    RealrenderTexture( bomer->getTexture() , bomer->getX() , bomer->getY() , 0 , 0 , renderer ) ;
    SDL_RenderPresent(renderer) ;
    bool check = 0 ;
    SDL_Event e ;
    while( true ){
        while(SDL_PollEvent(&e)){
                if ( e.type == SDL_QUIT )
                    exit(0);
                if ( e.type ==  SDL_KEYDOWN ){
                    if ( e.key.keysym.scancode == SDL_SCANCODE_Q ){
                       CommonFunc::quitSDL(window , renderer) ;
                       return ;
                    } else
                    if ( e.key.keysym.scancode == SDL_SCANCODE_G ){
                       check = 1 ; break ;
                    }
                }
        }
        if ( check == 1 ) break ;
    }
    if ( check == 1 ){
        this->Gamestart() ;
        return ;
    }

}
void Game::YOUWIN(){
    SDL_Event e ;
    TTF_Font * xfont = TTF_OpenFont( "menu.ttf", 20 );
    TTF_Font * gfont = TTF_OpenFont( "menu.ttf", 20 );
    TTF_Font * realfont = TTF_OpenFont( "menu.ttf", 50 );
    TTF_Font * cfont = TTF_OpenFont( "menu.ttf", 30 );
    SDL_Color White = { 255 , 255 , 255 } ;
    SDL_Color Black = { 0 , 0 , 0 } ;
    SDL_Color Blue = { 0 , 0 , 255 } ;
//    SDL_Texture* BackGround = loadTexture("Background.png", this->renderer);
//    renderTexture( BackGround , 0 , 0 , this->renderer );

    TTF* resume = new TTF() ; resume->setTTFTexture( 0 , 0 , "You Win!" , White , realfont , renderer ) ;
    resume->setX( 500 - resume->getW() / 2 ) ; resume->setY( 350 - resume->getH()  * 2 ) ;
    TTF* bomer = new TTF() ; bomer->setTTFTexture( 0 , 0 , "Press G to play again" , White, cfont , renderer ) ;
    bomer->setX( 500 - bomer->getW() / 2 ) ; bomer->setY( 350 - bomer->getH() + 10 ) ;
    TTF* sws = new TTF() ; sws->setTTFTexture( 0 , 0 , "Press Q to exit game" , White , cfont , renderer ) ;
    sws->setX( 500 - sws->getW() / 2 ) ; sws->setY( 350 + 20 ) ;

    RealrenderTexture( resume->getTexture() , resume->getX() , resume->getY() , 0 , 0 , renderer ) ;
    RealrenderTexture( sws->getTexture() , sws->getX() , sws->getY() , 0 , 0 , renderer ) ;
    RealrenderTexture( bomer->getTexture() , bomer->getX() , bomer->getY() , 0 , 0 , renderer ) ;
    SDL_RenderPresent(renderer) ;
    bool check = 0 ;
    while( true ){
        while(SDL_PollEvent(&e)){
                if ( e.type == SDL_QUIT )
                    exit(0);
                if ( e.type ==  SDL_KEYDOWN ){
                    if ( e.key.keysym.scancode == SDL_SCANCODE_Q ){
                       CommonFunc::quitSDL(window , renderer) ;
                       return ;
                    } else
                    if ( e.key.keysym.scancode == SDL_SCANCODE_G ){
                       check = 1 ; break ;
                    }
                }
        }
        if ( check == 1 ) break ;
    }
    if ( check == 1 ){
        this->Gamestart() ;
        return ;
    }

}
void Game::Gamestart(){

    srand(time(NULL)) ;

    int cur_x = 0 , cur_y = 0 ;
    Player Mine ;

    TTF_Font * xfont = TTF_OpenFont( "menu.ttf", 20 );
    TTF_Font * gfont = TTF_OpenFont( "Atop-R99O3.ttf", 20 );
    TTF_Font * realfont = TTF_OpenFont( "menu.ttf", 50 );
    TTF_Font * cfont = TTF_OpenFont( "menu.ttf", 30 );

    SDL_Color White = { 255 , 255 , 255 } ;
    SDL_Color Black = { 0 , 0 , 0 } ;
    SDL_Color Red = { 255 , 0 , 0 } ;
    SDL_Color Green = { 0 , 255 , 0 } ;
    SDL_Color Blue = { 0 , 0 , 255 } ;
    TTF* TIMELEFT = new TTF() ;
    TTF* WARN = new TTF() ;
    TTF* FTIME = new TTF() ;

    int Boss_bullet_status = 0 ;
    SDL_Texture* BackGround = loadTexture("Background.png", this->renderer);
    SDL_Texture* BG = loadTexture("Newbackground.png", this->renderer);
    vector<Entity*> swords ;
    CommonFunc::renderTexture( BackGround , 0 , 0 , this->renderer );
    TTF* beg = new TTF() ; beg->setTTFTexture( 0 , 0 , "Press any key to begin" , White , realfont , renderer ) ;
    beg->setX( 500 - beg->getW() / 2 ) ; beg->setY( 350 - beg->getH() / 2 ) ;
    RealrenderTexture( beg->getTexture() , beg->getX() , beg->getY() , 0 , 0 , renderer ) ;
    SDL_RenderPresent( this->renderer );
    CommonFunc::waitUntilKeyPressed();
//.........................................font................................................


FTIME->setTTFTexture( 10 , 70 , "Time Left : " , White , cfont , renderer ) ;
WARN->setTTFTexture( 0 , 0 , "Boss is coming !!!" , White , realfont , renderer ) ;
WARN->setX( 500 - WARN->getW() / 2 ) ; WARN->setY(350 - WARN->getH()) ;


//SDL_RenderPresent(renderer) ;
//..........................................Texture.................................................

    SDL_Texture * tPlayer = loadTexture("Player.png", this->renderer);
    SDL_Texture * tbow = loadTexture("bow.png", this->renderer);
    SDL_Texture * tcannon = loadTexture("cannon.png", this->renderer);
    SDL_Texture * tbullet = loadTexture("bullet.png" , renderer ) ;
    SDL_Texture * tmbullet = loadTexture("magic_bullet.png" , renderer ) ;
    SDL_Texture * sword = loadTexture("sword.png" , renderer ) ;
    SDL_Texture * minelink = loadTexture("minelink.png" , renderer ) ;
    SDL_Texture * mineheart = loadTexture("mineheart.png" , renderer ) ;
    SDL_Texture * choosesk = loadTexture("choosesk.png" , renderer ) ;

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
        //cout << s << "\n" ;
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
    int Cannon_timer = -6000 ;

    unsigned int Cur_ticks = SDL_GetTicks();
    unsigned int New_ticks = SDL_GetTicks();
    double delta = 0;

    int sword_angle = 0 ;

    std::vector<kboss*> Bullet_boss ;
    std::vector<TTF*> damge ;

    int QUIT = 0 ; Mine.setweapon( tbow , renderer ) ;
    int C = 0 , K = 0 , Render = 0 ;
    double add1 = 0 ;
    int adda = 0 ;
    while ( true ) {
        if ( !Main_boss->is_exist() ){
            this->YOUWIN() ;
            break ;
        }
        if ( Mine.getHP() <= 0 ){
            this->YOULOSS() ; // Player died
            //losser
            break ;
        }

        if ( timer - Cannon_timer > 7000 ){
            weapon_type = 1 ; Mine.setweapon(tbow , renderer) ;
        }
        C = 0 ; K = 0 ;
        adda = timer / 15000 ;
        if ( timer % 10000 == 0 && timer != 0 ){

            if ( timer > 120000 ){
                add1 += 0.2 ;
                Main_boss->setSP(Main_boss->getSP() + add1) ;
            }
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
                    if ( e.key.keysym.scancode == SDL_SCANCODE_Q ){
                        QUIT ++ ; QUIT %= 2 ;
                    } else
                    if ( e.key.keysym.scancode == SDL_SCANCODE_C )
                       C = 1 ;
                    else  if ( e.key.keysym.scancode == SDL_SCANCODE_K )
                        K = 1 ;
                       // Mine.setweapon( tbow , renderer ) , weapon_type = 1;
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


        if ( QUIT ){
            TTF* resume = new TTF() ; resume->setTTFTexture( 0 , 0 , "Press Q to resume." , White , realfont , renderer ) ;
            resume->setX( 500 - resume->getW() / 2 ) ; resume->setY( 350 - resume->getH() / 2 ) ;
            RealrenderTexture( resume->getTexture() , resume->getX() , resume->getY() , 0 , 0 , renderer ) ;
            SDL_RenderPresent(renderer) ;
            continue ;
        }


        if ( timer % 17000 == 0 && timer != 0 ){

            if ( Render == 0 ){
                TTF* resume = new TTF() ; resume->setTTFTexture( 0 , 0 , "Choose one special skill :" , Blue , cfont , renderer ) ;
                resume->setX( 500 - resume->getW() / 2 ) ; resume->setY( 350 - resume->getH()  * 2 ) ;
                TTF* bomer = new TTF() ; bomer->setTTFTexture( 0 , 0 , "Press c to have a cannon with devastating damage!" , Black , cfont , renderer ) ;
                bomer->setX( 500 - bomer->getW() / 2 ) ; bomer->setY( 350 - bomer->getH() + 10 ) ;
                TTF* sws = new TTF() ; sws->setTTFTexture( 0 , 0 , "Press k to add a sword of destruction all around!" , White , cfont , renderer ) ;
                sws->setX( 500 - sws->getW() / 2 ) ; sws->setY( 350 + 20 ) ;

                RealrenderTexture( resume->getTexture() , resume->getX() , resume->getY() , 0 , 0 , renderer ) ;
                RealrenderTexture( sws->getTexture() , sws->getX() , sws->getY() , 0 , 0 , renderer ) ;
                RealrenderTexture( bomer->getTexture() , bomer->getX() , bomer->getY() , 0 , 0 , renderer ) ;
                Render = 1 ;
            }
            if ( !K && !C){
                SDL_RenderPresent(renderer) ;
                continue ;
            }
            if ( C ){
                Mine.setweapon(tcannon , renderer) ;
                weapon_type = 2 ; Cannon_timer = timer ;
            }
        } else{
            K = 0 ; C = 0 ; Render = 0 ;
        }

        timer += 50 ;

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

        if ( K ){
            cout << 1 << "\n" ;
            Entity* sw = new Entity() ;
            sw->setTexture( sword , renderer ) ;
            swords.push_back( sw ) ;
               for ( int j = 0 ; j < swords.size() ; ++ j ){
                    Entity * N_sword = swords.at(j) ;
                    N_sword->setangle( j * 360 / (int)(swords.size()) ) ;
               }

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
       // cout << adda << "\n" ;
       if ( timer < 120000 ){
            if ( timer >= 1500 && List_enemy.size() < 15 + adda ){
                Enemy* Su = new Enemy();
                Su->setframe( 6 ) ;

                Su->setTexture( tms[ Su->getsernum()-1] , renderer ) ;
                Su->MOVETO( Mine.getX() , Mine.getY() , Su->getSP() ) ;
                List_enemy.push_back(Su) ;
            }
            if ( timer >= 5000 && List_bat.size() < 20 + adda ){
                bat* Su_bat = new bat();
                Su_bat->setframe( 8 ) ;
                Su_bat->setTexture( bats[Su_bat->getsernum()-1] , renderer ) ;
                Su_bat->MOVETO( Mine.getX() , Mine.getY() , Su_bat->getSP() ) ;

                List_bat.push_back(Su_bat) ;
            }
            if ( timer >= 8000 && List_magic.size() < 2 + adda ){
                //cout << 1 <<"\n" ;
                magician* Su_bat = new magician();
                Su_bat->setframe( 5 ) ;

                Su_bat->setTexture( magicians[Su_bat->getsernum()-1] , renderer ) ;
                Su_bat->MOVETO( Mine.getX() , Mine.getY() , Su_bat->getSP() ) ;

                List_magic.push_back(Su_bat) ;
                //cout << List_bat.size() ;
            }
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
                        TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-1" , White , xfont , renderer ) ;
                        damge.push_back( Edamge ) ;
                        Mine.updHP() ;
                        TTF* Mdamge = new TTF() ; Mdamge->setTTFTexture( Mine.getX() , Mine.getY() , "-1" , Red, xfont , renderer ) ;
                        damge.push_back( Mdamge ) ;
                    }

                    for ( int j = 0 ; j < Mine.GetBulletlist().size() ; ++ j ){
                        std::vector<Bullet*> N_list = Mine.GetBulletlist() ;
                        Bullet* Current_Bullet = N_list.at(j) ;
                        if ( Current_Bullet != NULL ){
                            if ( C_enemy->is_exist() && Current_Bullet->is_exist() && C_enemy->Coll(*Current_Bullet) ){
                                C_enemy->updHP() ;
                                Current_Bullet->updHP() ;
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-1" , White , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-8" , White , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-1" , White , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
                        TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-1" , White , xfont , renderer ) ;
                        damge.push_back( Edamge ) ;
                        Mine.updHP() ;
                        TTF* Mdamge = new TTF() ; Mdamge->setTTFTexture( Mine.getX() , Mine.getY() , "-1" , Red, xfont , renderer ) ;
                        damge.push_back( Mdamge ) ;
                    }
                    for ( int j = 0 ; j < Mine.GetBulletlist().size() ; ++ j ){
                        std::vector<Bullet*> N_list = Mine.GetBulletlist() ;
                        Bullet* Current_Bullet = N_list.at(j) ;
                        if ( Current_Bullet != NULL ){
                            if ( C_enemy->is_exist() && Current_Bullet->is_exist() && C_enemy->Coll(*Current_Bullet) ){
                                C_enemy->updHP() ;
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-1" , White , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-8" , White , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-1" , White , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
                        TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-1" , White , xfont , renderer ) ;
                        damge.push_back( Edamge ) ;
                        Mine.updHP() ;
                        TTF* Mdamge = new TTF() ; Mdamge->setTTFTexture( Mine.getX() , Mine.getY() , "-1" , Red, xfont , renderer ) ;
                        damge.push_back( Mdamge ) ;
                    }
                    for ( int j = 0 ; j < Mine.GetBulletlist().size() ; ++ j ){
                        std::vector<Bullet*> N_list = Mine.GetBulletlist() ;
                        Bullet* Current_Bullet = N_list.at(j) ;
                        if ( Current_Bullet != NULL ){
                            if ( C_enemy->is_exist() && Current_Bullet->is_exist() && C_enemy->Coll(*Current_Bullet) ){
                                C_enemy->updHP() ;
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-1" , White , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-8" , White , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( C_enemy->getX() , C_enemy->getY() , "-1" , White , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
                                TTF* Edamge = new TTF() ; Edamge->setTTFTexture( Mine.getX() , Mine.getY() , "-1" , Red , xfont , renderer ) ;
                                damge.push_back( Edamge ) ;
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
        if ( timer >= 120000 && timer <= 123000 ){

            TTF* TIME = new TTF() ;
            TIME->setTTFTexture( 0 , 0 , to_string((123000 - timer) / 1000).c_str() , White , realfont , renderer ) ;
            TIME->setX(500 - TIME->getW() / 2 ) ; TIME->setY(360) ;
            RealrenderTexture( WARN->getTexture() , WARN->getX() ,   WARN->getY(), 0 , 0 , renderer ) ;
            RealrenderTexture( TIME->getTexture() , TIME->getX() ,  TIME->getY() , 0 , 0 , renderer ) ;
        } else
        {
                BackGround = BG ;
                if ( Main_boss->is_exist() ){
                    if ( Boss_bullet_status < 1 && Main_boss->getstatus() == 1 ){
                        kboss * Nkb1 = new kboss() ; kboss * Nkb2 = new kboss() ;kboss * Nkb3 = new kboss() ;
                        Nkb1->setX( Main_boss->getX() + Main_boss->getW() / 2 ) ;
                        Nkb1->setY( Main_boss->getY() + Main_boss->getH() / 2 ) ;
                        Nkb2->setX( Main_boss->getX() + Main_boss->getW() / 2 ) ;
                        Nkb2->setY( Main_boss->getY() + Main_boss->getH() / 2 ) ;
                        Nkb3->setX( Main_boss->getX() + Main_boss->getW() / 2 ) ;
                        Nkb3->setY( Main_boss->getY() + Main_boss->getH() / 2 ) ;
                        Nkb1->MOVETO(500 , 350 , Nkb1->getSP() ) ;
                        Nkb2->MOVETO(500 + 100*ADDX[Main_boss->getpos()], 350 + 100*ADDY[Main_boss->getpos()] , Nkb2->getSP() ) ;
                        Nkb3->MOVETO(500 - 100*ADDX[Main_boss->getpos()], 350 - 100*ADDY[Main_boss->getpos()] , Nkb3->getSP() ) ;
                        Boss_bullet_status = 1 ;
                        Bullet_boss.push_back( Nkb1 ) ; Bullet_boss.push_back( Nkb2 ) ; Bullet_boss.push_back( Nkb3 ) ;
                    }
                    else if ( Main_boss->getstatus() != 1 ) Boss_bullet_status = 0 ;

                    Main_boss->setTexture( Tboss[Main_boss->getstatus()][Main_boss->getsernum()-1] , renderer ) ;
                    Main_boss->updateframe() ;

                    RealrenderTexture( Main_boss->getTexture() , Main_boss->getX()  , Main_boss->getY() , 0 , Main_boss->getflip() , renderer ) ;
                    if ( Main_boss->getstatus() == 0 ) {
                        Main_boss->move() ;
                        //cout << Main_boss->getX() +  Main_boss->getW() / 2 << ' ' << Main_boss->getY() +  Main_boss->getH() / 2  << "\n" ;
                    }

                    if (  Main_boss->Coll( Mine ) ){
                        Main_boss->updHP() ;
                        TTF* Edamge = new TTF() ; Edamge->setTTFTexture( Main_boss->getX() , Main_boss->getY() , "-1" , White , xfont , renderer ) ;
                        damge.push_back( Edamge ) ;
                        Mine.updHP() ;
                        TTF* Mdamge = new TTF() ; Mdamge->setTTFTexture( Mine.getX() , Mine.getY() , "-1" , Red , xfont , renderer ) ;
                        damge.push_back( Mdamge ) ;
                    }
                    //cout << "1.2" << "\n" ;
                    boss* C_enemy = Main_boss ;
                    for ( int j = 0 ; j < Mine.GetBulletlist().size() ; ++ j ){
                            std::vector<Bullet*> N_list = Mine.GetBulletlist() ;
                            Bullet* Current_Bullet = N_list.at(j) ;
                            if ( Current_Bullet != NULL ){
                                if ( C_enemy->is_exist() && Current_Bullet->is_exist() && C_enemy->Coll(*Current_Bullet) ){
                                    C_enemy->updHP() ;
                                    Current_Bullet->updHP() ;
                                    TTF* Edamge = new TTF() ; Edamge->setTTFTexture( Main_boss->getX() , Main_boss->getY() , "-1" , White , xfont , renderer ) ;
                                    damge.push_back( Edamge ) ;
                                }
                            }
                        }
                        //cout << "1.3" << "\n" ;
                        for ( int j = 0 ; j < Mine.Getbomlist().size() ; ++ j ){
                            std::vector<bom*> N_list = Mine.Getbomlist() ;
                            bom* Current_Bullet = N_list.at(j) ;
                            if ( Current_Bullet != NULL ){
                                if ( C_enemy->is_exist() && Current_Bullet->is_exist() && C_enemy->Coll(*Current_Bullet) ){
                                    C_enemy->updHP() ;
                                    TTF* Edamge = new TTF() ; Edamge->setTTFTexture( Main_boss->getX() , Main_boss->getY() , "-1" , White , xfont , renderer ) ;
                                    damge.push_back( Edamge ) ;
                                    Current_Bullet->updHP() ;
                                    if ( Current_Bullet->get_order() == 0 ){
                                        Current_Bullet->upd_order() ;
                                        Current_Bullet->upd_image(renderer , boms[Current_Bullet->get_order()]) ;
                                    }
                                }
                            }
                        }
                        //cout << "1.4" << "\n" ;
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
                                    TTF* Edamge = new TTF() ; Edamge->setTTFTexture( Main_boss->getX() , Main_boss->getY() , "-1" , White , xfont , renderer ) ;
                                    damge.push_back( Edamge ) ;
                                }
                        }

                }

                for ( int i = 0 ; i < Bullet_boss.size() ; ++ i ){

                    std:: vector<kboss*> Cur = Bullet_boss ;
                    kboss* Cur_kboss = Cur.at(i) ;
                    if ( Cur_kboss != NULL ){
                    if ( Cur_kboss->is_exist() ){
                        //cout << Cur_kboss->get_order()-1 ;
                        RealrenderTexture(boss_skill[Cur_kboss->get_order()-1] , Cur_kboss->getX() , Cur_kboss->getY() , 0 , Main_boss->getflip() , renderer ) ;
                        if( Cur_kboss->Coll(Mine) ){
                            Mine.updHP() ;
                            TTF* Mdamge = new TTF() ; Mdamge->setTTFTexture( Mine.getX() , Mine.getY() , "-1" , Red , xfont , renderer ) ;
                            damge.push_back( Mdamge ) ;
                        }
                    }
                    }
                }
                for ( int i = 0 ; i < Bullet_boss.size() ; ++ i ){
                    std :: vector<kboss*> Cur = Bullet_boss ;
                    kboss* Cur_kboss = Cur.at(i) ;
                    if ( Cur_kboss != NULL ){
                    if ( Cur_kboss->is_exist() ){
                        Cur_kboss->move() ; Cur_kboss->upd_order() ;
                    }
                    else{
                          Cur.erase(Cur.begin() + i ) ;
                          Bullet_boss = Cur ;
                          Cur_kboss = NULL ;
                          delete Cur_kboss ;
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
//..............................upddamge.....................................................................
         for ( int i = 0 ; i < damge.size() ; ++ i ){
                std::vector<TTF*> N_list = damge ;
                TTF* Cur = N_list.at(i) ;
                if ( Cur != NULL ){
                if ( Cur->is_exist() ){
                    Cur->updHP() ;
                    RealrenderTexture(Cur->getTexture() , Cur->getX() , Cur->getY() , 0 , 0 , renderer ) ;
                } else {
                        N_list.erase( N_list.begin() + i ) ;
                        damge = N_list ;
                        delete Cur;
                        Cur = NULL ;
                    }
                }
         }
////...........................................................................................................
         CommonFunc::RealrenderTexture( Mine.getweapon()->getTexture() , Mine.getweapon()->getX() ,  Mine.getweapon()->getY() ,  Mine.getweapon()->getangle() , 0 , renderer ) ;
         RealrenderTexture( minelink , 10 ,  10, 0 , 0 , renderer ) ;
         if ( timer <= 120000 ){
            string s = to_string( 120 - timer / 1000 ) ;
            //s += '' ;
            TIMELEFT->setTTFTexture( FTIME->getX() + FTIME->getW() , FTIME->getY()  , s.c_str() , White , cfont , renderer ) ;

            RealrenderTexture( FTIME->getTexture() , FTIME->getX() ,   FTIME->getY(), 0 , 0 , renderer ) ;
            RealrenderTexture( TIMELEFT->getTexture() , TIMELEFT->getX() ,  TIMELEFT->getY() , 0 , 0 , renderer ) ;
         }
         TTF* Q = new TTF() ; Q->setTTFTexture( 0 , 0 , "Press Q to quit" , White , xfont , renderer ) ;
         Q->setX( 1000 - Q->getW() ) ; Q->setY(10) ;
         RealrenderTexture(Q->getTexture() , Q->getX() , Q->getY() , 0 , 0 , renderer ) ;
         for ( int i = 1 ; i <= Mine.getHP() ; ++ i ){
            RealrenderTexture( mineheart , 10 + 50 * i ,  10, 0 , 0 , renderer ) ;
         }

         //if ( timer > )
         SDL_RenderPresent( renderer );
         SDL_Delay(50) ;
    }

   // BackGround = loadTexture("Newbackground.png", this->renderer);
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    CommonFunc::quitSDL(window, renderer);
}
