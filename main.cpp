#include "Graphics.h"
#include "Events.h"
#include "Fluid.h"
#include <stdio.h>
#include <chrono>
#include <time.h>
#include "windows.h"

int main() {
    const int width = 960, height = 640;
    const float scaleX = 8, scaleY = 8;
    bool pause = false;
    Graphics *graphics = new Graphics(width, height, scaleX, scaleY);
    const float diffusion = 0.0001;
    Fluid *fluid = new Fluid(width/scaleX, height/scaleY, diffusion, graphics, scaleX, scaleY);
    Events *events = new Events(graphics, fluid, &pause);
    
    float dt{0};

    srand(time(NULL));

    while(1){
        if(events->pollEvents())
            break;
        graphics->update();
        dt = graphics->getDeltaTime();
        //printf("%.5f\r", dt);
        if(!pause){
            fluid->velStep(dt);
            fluid->densStep(dt);
        }
        fluid->draw();
    }
    delete graphics;
    delete fluid;
    return 0;
}