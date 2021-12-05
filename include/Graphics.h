#pragma once

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"

class Graphics {
private:
    SDL_Event event;
    SDL_Renderer *renderer;
    SDL_Window *window;
    int width, height;
    Uint64 now;
    Uint64 last;
    float dt;

public:
    Graphics(int width, int height);
    ~Graphics();
    void drawPixel(int x, int y, float d); //coordinates x,y of pixel and d for density
    const int update();
    void clearScreen();
    const float getDeltaTime() const;
};