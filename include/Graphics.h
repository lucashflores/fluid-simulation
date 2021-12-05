#pragma once

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

class Graphics {
private:
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int width, height;

public:
    Graphics(int width, int height);
    ~Graphics();
    void drawPixel(int x, int y, float d); //coordinates x,y of pixel and d for density
    void update();
};