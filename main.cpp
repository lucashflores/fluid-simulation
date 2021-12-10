#include "Graphics.h"
#include "Events.h"
#include "Fluid.h"
#include <stdio.h>
#include <chrono>
#include <time.h>
#include "windows.h"

int main() {
    const int width = 240, height = 160;
    Graphics *graphics = new Graphics(width, height);
    const float diffusion = 0.00001;
    Fluid *fluid = new Fluid(width, height, diffusion, graphics);
    Events *events = new Events(graphics, fluid);
    
    float dt{0};

    srand(time(NULL));

    while(1){
        if(events->pollEvents())
            break;
        graphics->update();
        dt = graphics->getDeltaTime();
        //printf("%.5f\r", dt);
        fluid->velStep(dt);
        fluid->densStep(dt);
        fluid->draw();
    }
    delete graphics;
    delete fluid;
    return 0;
}