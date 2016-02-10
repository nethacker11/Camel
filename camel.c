#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>

int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *currentTex = NULL;
SDL_Texture *penguin = NULL;



int init()
{
	//Initialization flag
	int success = 1;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = 0;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = 0;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
			if( renderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = 0;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = 0;
				}
			}
		}
	}

	return success;
}

SDL_Texture* loadTexture( char *path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}




int main() {

    if ( !init() ) {

        printf("failed to initialize\n");
        exit(1);
    }

    currentTex = loadTexture("img/camel.bmp");
    penguin = loadTexture("img/penguin.png");

    SDL_Rect camelRect;
    camelRect.x = 0;
    camelRect.y = 100;
    camelRect.w = SCREEN_WIDTH;
    camelRect.h = SCREEN_HEIGHT;

    SDL_Rect destRect;
    destRect.x = 50;
    destRect.y = 50;
    destRect.w = 100;
    destRect.h = 100;


    int up = 0; int down = 0; int left = 0; int right = 0;
    int quit = 0;
    //Event handler
    SDL_Event e;

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = 1;
            }

            
            if (e.type == SDL_KEYDOWN) {

                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        up = 1;
                        break;
                    case SDLK_DOWN:
                        down = 1;
                        break;
                    case SDLK_LEFT:
                        left = 1;
                        break;
                    case SDLK_RIGHT:
                        right = 1;
                        break;
                    default:
                        ;
                }
            }

            if (e.type == SDL_KEYUP) {

                switch(e.key.keysym.sym) {
                    case SDLK_UP:
                        up = 0;
                        break;
                    case SDLK_DOWN:
                        down = 0;
                        break;
                    case SDLK_LEFT:
                        left = 0;
                        break;
                    case SDLK_RIGHT:
                        right = 0;
                        break;
                    default:
                        ;
                }
            }
 
        }


        if (up) { if (destRect.y == 0) {;} else {destRect.y -= 1;} }
        if (down) { if (destRect.y == (SCREEN_HEIGHT - destRect.h)) {;} else {destRect.y += 1;} }
        if (right) { if (destRect.x == (SCREEN_WIDTH - destRect.w)) {;} else {destRect.x += 1;} }
        if (left) { if (destRect.x == 0) {;} else {destRect.x-= 1;} }


        //Clear screen
        SDL_RenderClear( renderer );

        //Render texture to screen
        SDL_RenderCopy( renderer, currentTex, NULL, &camelRect );
        SDL_RenderCopy( renderer, penguin, NULL, &destRect );

        //Update screen
        SDL_RenderPresent( renderer );
    }

}




