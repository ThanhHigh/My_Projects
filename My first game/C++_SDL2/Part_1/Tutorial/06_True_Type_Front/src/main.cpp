
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>

const int SCREEN_WIDTH = 840;
const int SCREEN_HEIGHT = 480;

//Texture wrapper class
class LTexture
{
    public:
    //Initializes variables
        LTexture();

    //Deallocates memory
        ~LTexture();

    // //Loads image at specified path
    //     bool loadFromFile( std::string path );

    //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

    //Deallocates texture
        void free();


    // //Set blending
    //     void setBlendMode( SDL_BlendMode blending );

    // //Set alpha modulation
    //     void setAlpha( Uint8 alpha );

    //Renders texture at given point
        void render(int x, int y,  SDL_Color texColour, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    //Gets image dimensions
        inline int getWidth(){ return mWidth; }
        inline int getHeight(){ return mHeight; }

    private:
        //The actual hardware texture
        SDL_Texture* mTexture;

        //Image dimensions
        int mWidth;
        int mHeight;

};

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font* gFont = NULL;

//Rendered texture
LTexture gTextTexture;

//texture which will be generated from the font.
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );

    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );

        if (mTexture == NULL) 
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimension
            mHeight = textSurface->h;
            mWidth = textSurface->w;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return mTexture != NULL;
}

LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;
    mHeight = 0;
    mWidth = 0;
}

LTexture::~LTexture()
{

}

void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y,  SDL_Color texColour, SDL_Rect* clip, double angle, SDL_Point* center , SDL_RendererFlip flip)
{

        //Render text
        if( !gTextTexture.loadFromRenderedText( "StartGame", texColour ) )
        {
            printf( "Failed to render text texture!\n" );
        }


    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Open the font
    gFont = TTF_OpenFont( "res/font.ttf", 40 );
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    // else
    // {
    //     //Render text
    //     SDL_Color textColor = { 120, 40, 20, 230 };
    //     if( !gTextTexture.loadFromRenderedText( "StartGame", textColor ) )
    //     {
    //         printf( "Failed to render text texture!\n" );
    //         success = false;
    //     }
    // }

    return success;
}

void close()
{
    //Free loaded images
    gTextTexture.free();

    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

    //Destroy window    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool init()
{
    //Initilize
    bool success = true;
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    else{
    //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 60, 60, 30, 230 );
            
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                //Initialize TTF loading
                if (TTF_Init() != 0)
                {
                    printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool checkMouseCollision(int x, int y, SDL_Rect destRect)
{
    //AA BB
    if ((x >= destRect.x && x <= (destRect.x + destRect.w)) && (y >= destRect.y && (y <= destRect.y + destRect.h))) return true;
    else return false;
}


int main(int argc, char* args[])
{
    if ( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //main loop
            bool quit = false;
            SDL_Event e;

            const SDL_Colour UNMOUSE_COLOUR = {40, 20, 40, 120};
            const SDL_Colour MOUSED_COLOUR = {60, 10, 60, 220};
            SDL_Colour color = UNMOUSE_COLOUR;
             //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    //If mouse event happened
                    if( e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP )
                    {
                        //Get mouse position
                        int x, y;
                        SDL_GetMouseState( &x, &y );
                        int curHeight = gTextTexture.getHeight();
                        int curWidth = gTextTexture.getWidth();
                        SDL_Rect StartRect = {100, 100, curWidth, curHeight};
                        if (checkMouseCollision(x, y, StartRect)) 
                        {
                            color = MOUSED_COLOUR;
                        }
                        else
                        {
                            color = UNMOUSE_COLOUR;
                        }
                    }

                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 230, 230, 250, 250);
                SDL_RenderClear( gRenderer );
                //Rect

                //Render current frame
                gTextTexture.render( 100, 100, color);

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
        }
    }
    
    close();
    return 0;
}











