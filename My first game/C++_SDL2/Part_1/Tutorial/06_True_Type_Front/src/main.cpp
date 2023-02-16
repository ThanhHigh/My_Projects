
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <string>
#include <stdio.h>

//Texture wrapper class
class LTexture
{
    public:
    //Initializes variables
        LTexture();

    //Deallocates memory
        ~LTexture();

    //Loads image at specified path
        bool loadFromFile( std::string path );

    //Creates image from font string
        bool loadFromRenderedText( std::string textureText, SDL_Color textColor );

    //Deallocates texture
        void free();

    //Set color modulation
        void setColor( Uint8 red, Uint8 green, Uint8 blue );

    //Set blending
        void setBlendMode( SDL_BlendMode blending );

    //Set alpha modulation
        void setAlpha( Uint8 alpha );

    //Renders texture at given point
        void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    //Gets image dimensions
        int getWidth();
        int getHeight();

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
    //Delocate
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        std::cout << "Unable to load image ! Error: " << SDL_GetError() << std::endl;
    }
    else
    {
        //Create texture from surface pixels
        
    }
}
int main(int argc, char* args[])
{
    
    return 0;
}