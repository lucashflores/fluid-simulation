#include "Events.h"

Events::Events(Graphics *graphics, Fluid *fluid): x(0), y(0), mousePressed(false){
    this->graphics = graphics;
    this->fluid = fluid;
}

Events::~Events() {
    graphics = nullptr;
    fluid = nullptr;
}

const int Events::pollEvents() {
    while(SDL_PollEvent(&event) != 0){
        switch(event.type){
            case SDL_QUIT:
                graphics->terminate();
                return 1;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mousePressed = true;
                break;
            case SDL_MOUSEBUTTONUP:
                mousePressed = false;
                break;
            /* case SDL_MOUSEMOTION:
                getMousePosition();
                fluid->setMouseCoord(x, y);
                break; */
        }
    }
    if(mousePressed){
        getMousePosition();
        // printf("x: %d, y: %d\n", x, y);
        fluid->addFromUser(x, y);
    }

    return 0;
}

void Events::getMousePosition() {
    SDL_GetMouseState(&x, &y);
}