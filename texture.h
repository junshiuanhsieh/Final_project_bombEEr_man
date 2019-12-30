#ifndef BOMBEER_MAN_TEXTURE_H
#define BOMBEER_MAN_TEXTURE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

using namespace std;

class Texture{
    public:
        Texture();
        ~Texture();
        void loadFromFile(string path);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);

        #if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
            bool loadFromRenderedText(string textureText, SDL_Color textColor );
        #endif

        void free();
        void render(SDL_Rect* dest, SDL_Rect* clip=NULL, bool big = 0);

    private:
        SDL_Texture* mTexture;
        int mWidth;
        int mHeight;
};

#endif //BOMBEER_MAN_TEXTURE_H
