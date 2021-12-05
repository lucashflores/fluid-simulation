#include "Graphics.h"
#include "Fluid.h"

int main() {
    Graphics *graphics = new Graphics(400, 400);
    graphics->drawPixel(200, 200, 1);
    while(1){
        graphics->update();
    }

    return 0;
}