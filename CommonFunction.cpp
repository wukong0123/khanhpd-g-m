#include "CommonFunction.hpp"

void CommonFunc::logErrorAndExit(const char* msg, const char* error){
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

SDL_Window* CommonFunc::initSDL(int SCREEN_WIDTH, int SCREEN_HEIGHT, const char* WINDOW_TITLE){



    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
        logErrorAndExit( "SDL_image error:", IMG_GetError());
    if( TTF_Init() == -1 )
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );


    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        printf("Failed to init SDL\n");
    }

    Mix_OpenAudio(22050 , MIX_DEFAULT_FORMAT , 2 , 4096 ) ;

    return window;
}

SDL_Renderer* CommonFunc::createRenderer(SDL_Window* window){

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}

void CommonFunc::quitSDL(SDL_Window* window, SDL_Renderer* renderer){

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();
    TTF_Quit() ;
    Mix_Quit() ;
    exit(0) ;

}
double CommonFunc::getangle( int x , int y ){
    return atan2(x , -y) * (180.0 / M_PI) ;
}
void CommonFunc::waitUntilKeyPressed(){
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}
int CommonFunc::genRDNumber( int l , int r ){
    return l + (rand() % (r - l + 1));
}
void CommonFunc::renderTexture(SDL_Texture *texture, double x, double y, SDL_Renderer* renderer){

	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	SDL_RenderCopy(renderer, texture, NULL, &dest);
}
pair<int,int> CommonFunc::getPosmovemouse( int x , int y, int W, int H, int _vector_x , int _vector_y , double _size_W , double _size_H ){
    int mid_x = x + W/2 ;
    int mid_y = y + H/2 ;
    double radius = ( W * W + H * H ) / 4 ;
    _vector_x*= 50 ; _vector_y *= 50 ;
    double fakeradius = (_vector_x * _vector_x + _vector_y* _vector_y) / 4 ;

        _vector_x = mid_x + _vector_x / fakeradius * radius - _size_W / 2;
        _vector_y = mid_y + _vector_y / fakeradius * radius - _size_H / 2 ;
    return (pair<int,int>){_vector_x , _vector_y } ;
}
void CommonFunc::ProrenderTexture(SDL_Texture *texture, double x, double y, double tox , double toy , double W , double H , double nW , double nH , SDL_Renderer* renderer){

	SDL_Rect dest;
    SDL_Rect newdest ;
	dest.x = x; dest.y = y;
	dest.w = W ; dest.h = H ;
	newdest.x = tox ; newdest.y = toy ;
	newdest.w = nW ; newdest.h = nH ;
	SDL_RenderCopy(renderer, texture, &dest , &newdest );
}
void CommonFunc::RealrenderTexture(SDL_Texture *texture, double x, double y, double angle , bool o , SDL_Renderer* renderer){

    SDL_Rect dest;
    dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopyEx( renderer , texture , NULL , &dest , angle , NULL , ( o == 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL )) ;
}

void CommonFunc::swordrenderTexture(SDL_Texture *texture, int midx , int midy , double x, double y,  double angle , bool o , SDL_Renderer* renderer){

    SDL_Point Point ;
    SDL_Rect dest;
    Point.x = midx ; Point.y = midy ;
    dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
    SDL_RenderCopyEx( renderer , texture , NULL , &dest , angle , &Point , ( o == 0 ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL )) ;
}
SDL_Texture* CommonFunc::loadTexture(const char *filename, SDL_Renderer* renderer){

	SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
	if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

	return texture;
}
bool CommonFunc::IS_ATC(int a , int b , int x , int y , int z , int t ){
    return ( x <= a && a <= z && y <= b && b <= t ) ;
}
