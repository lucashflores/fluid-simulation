#include "Graphics.h"
#include "Fluid.h"
#include <stdio.h>

int main() {
    const int width = 320, height = 200;
    Graphics *graphics = new Graphics(width, height);
    const float diffusion = 0.3;
    Fluid *fluid = new Fluid(width, height, diffusion, graphics);
    float dt{0};

    while(1){
        if(graphics->update())
            break;
        dt = graphics->getDeltaTime();
        // printf("%.2f\r", dt);
        fluid->densStep(dt);
        fluid->draw();
    }
    delete graphics;
    return 0;
}