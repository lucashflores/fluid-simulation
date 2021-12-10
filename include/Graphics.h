#pragma once

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

class Graphics {
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    int width, height;
    Uint64 now;
    Uint64 last;
    float dt;

public:
    Graphics(int width, int height, float scaleX, float scaleY);
    ~Graphics();
    void drawPixel(int x, int y, float d, float v); //coordinates x,y of pixel and d for density
    void update();
    void clearScreen();
    const float getDeltaTime() const;
    void terminate();
};