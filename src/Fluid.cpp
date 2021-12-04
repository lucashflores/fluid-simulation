#include "Fluid.h"

Fluid::Fluid(int w, int h, float diff): height(h), width(w), diff(diff), density(), initialDensity(), source(), hvelocity(), vvelocity() {
    setSize(w, h);
    density.assign(size, 0);
    source.assign(size, 0);
    hvelocity.assign(size, 0);
    vvelocity.assign(size, 0);
}

Fluid::~Fluid() {
    density.clear();
    initialDensity.clear();
    source.clear();
    hvelocity.clear();
    vvelocity.clear();
}



void Fluid::setSize(int w, int h) {
    size = (w+2)*(h+2);
}

void Fluid::addSource(float dt) {
    for (int i = 0; i < size; i++) {
        density[i] += dt*source[i];
    }
}

void Fluid::setBounds(int direction) {
    /*
    1 - horizontal
    2 - vertical
    */
    for (int i = 1; i <= width; i++) {
        density[IX(0, i, height)] = direction == 1? -density[IX(1, i, height)]:density[IX(1, i, height)];
        density[IX(width + 1, i, height)] = direction == 1? -density[IX(width, i, height)]:density[IX(width, i, height)];
    }
    for (int i = 1; i <= height; i++) {
        density[IX(i, 0, height)] = direction == 2? -density[IX(i, 1, height)]:density[IX(i, 1, height)];
        density[IX(i, height + 1, height)] = direction == 2? -density[IX(i, height, height)]:density[IX(i, height, height)];
    }
    //Canto superior esquerdo
    density[IX(0, 0, height)] = (density[IX(0, 1, height)] + density[IX(1, 0, height)])/2;
    //Canto superior direito
    density[IX(width + 1, 0, height)] = (density[IX(width + 1, 1, height)] + density[IX(width, 0, height)])/2;
    //Canto inferior esquerdo
    density[IX(0, height + 1, height)] = (density[IX(0, height, height)] + density[IX(1, height + 1, height)])/2;
    //Canto inferior direito
    density[IX(width + 1, height + 1, height)] = (density[IX(width, height + 1, height)] + density[IX(width + 1, height, height)])/2;

}

