#pragma once

#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include <vector>
#include "Graphics.h"
#include "Fluid.h"
#include <stdio.h>

class Events{
private:
    SDL_Event event;
    Graphics *graphics;
    Fluid *fluid;
    int x, y;
    bool mousePressed;

public:
    Events(Graphics *graphics, Fluid *fluid);
    ~Events();
    const int pollEvents(); //returns 1 if exit is requested, 0 otherwise
    void getMousePosition();
};