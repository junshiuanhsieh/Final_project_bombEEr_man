#include "texture.h"
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;

Texture::Texture(){
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

Texture::~Texture(){
    free();
}

void Texture::loadFromFile( std::string path ){
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    //SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0, 0) );
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    mWidth = loadedSurface->w;
    mHeight = loadedSurface->h;
    SDL_FreeSurface(loadedSurface);
    mTexture = newTexture;
    //if(mTexture == NULL) cout << "fail to load" << endl;
}
void Texture::setBlendMode( SDL_BlendMode blending ){
    SDL_SetTextureBlendMode( mTexture, blending );
}

void Texture::setAlpha( Uint8 alpha ){
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool Texture::loadFromRenderedText(string textureText, SDL_Color textColor){
	free();
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
	mWidth = textSurface->w;
	mHeight = textSurface->h;
	SDL_FreeSurface( textSurface );
	return mTexture != NULL;
}
#endif

void Texture::free(){
    if( mTexture != NULL ){
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void Texture::render(SDL_Rect* dest, SDL_Rect* clip, bool big){
    if(big){
        SDL_Rect newdest;
        newdest.x = dest->x - (dest->w/20);
        newdest.y = dest->y - (dest->h/20);
        newdest.w = dest->w + (dest->w/20)*2;
        newdest.h = dest->h + (dest->h/20)*2;
        SDL_RenderCopy( gRenderer, mTexture, clip, &newdest);
    }
    else SDL_RenderCopy( gRenderer, mTexture, clip, dest);
}