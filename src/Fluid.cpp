#include "Fluid.h"

Fluid::Fluid(int w, int h, float diff, Graphics *graphics): height(h), width(w), diff(diff),
density(), initialDensity(), source(), initialHVelocity(), hvelocity(), initialVVelocity(), vvelocity() {
    this->graphics = graphics;
    setSize(w, h);
    initialDensity.assign(size, 0);
    density.assign(size, 0.3);
    initialVVelocity.assign(size, 0);
    initialHVelocity.assign(size, 0);
    source.assign(size, 0);
    source[IX(width/2, height/2, height)] = 30;
    hvelocity.assign(size, 0);
    vvelocity.assign(size, 0);
}

Fluid::~Fluid() {
    density.clear();
    initialDensity.clear();
    initialHVelocity.clear();
    initialVVelocity.clear();
    hvelocity.clear();
    vvelocity.clear();
}



void Fluid::setSize(int w, int h) {
    size = (w+2)*(h+2);
}

void Fluid::addSource(std::vector<float> vector, std::vector<float> source, float dt) {
    for (int i = 0; i < size; i++) {
        vector[i] += dt*source[i];
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

void Fluid::diffuse(std::vector<float> final, std::vector<float> initial, int direction, float dt) {
    float coef = diff * dt * size;

    for (int n = 0; n < 20; n++) {
        for (int i = 1; i < width; i++)
            for (int j = 1; j < height; j++)
                final[IX(i, j, height)] = (initial[IX(i, j, height)] + coef * (final[IX(i-1, j, height)] + final[IX(i+1, j, height)] + final[IX(i, j-1, height)] + final[IX(i, j+1, height)])) / (4*coef + 1);
        setBounds(direction);
    }
}

void Fluid::advect(int direction, float dt) {

    int i, j, i0, j0, i1, j1;
    float x, y, s0, t0, s1, t1, dtw, dth;

    dtw = dt*width;
    dth = dt*height;
    for (i = 1; i <= width; i++) {
        for (j = 1; j <= height; j++) {

            x = i - dtw*hvelocity[IX(i, j, height)];
            y = j - dth*vvelocity[IX(i, j, height)];

            if (x < 0.5)
                x = 0.5;
            else if (x > width + 0.5)
                x = width+0.5;
            i0 = (int) x;
            i1 = i0 + 1;

            if (y < 0.5)
                y = 0.5;
            else if (y > height + 0.5)
                y = height + 0.5;
            j0 = (int) y;
            j1 = j0 + 1;

            s1 = x - i0;
            s0 = 1 - s1;

            t1 = y - j0;
            t0 = 1 - t1;

            density[IX(i, j, height)] = s0*(t0*initialDensity[IX(i0, j0, height)]+t1*initialDensity[IX(i0, j1, height)]) +
                                        s1*(t0*initialDensity[IX(i1, j0, height)]+t1*initialDensity[IX(i1, j1, height)]);
        }
    }

    setBounds(direction);
}

void Fluid::project() {

}

void Fluid::densStep(float dt) {
    addSource(density, source, dt);
    initialDensity.swap(density);
    diffuse(density, initialDensity, 0, dt);
    initialDensity.swap(density);
    advect(0, dt);
}

void Fluid::velStep(float dt) {
    addSource(hvelocity, initialVVelocity, dt);
    addSource(vvelocity, initialVVelocity, dt);

    initialHVelocity.swap(hvelocity);
    diffuse(hvelocity, initialHVelocity, 1, diff);

    initialVVelocity.swap(vvelocity);
    diffuse(vvelocity, initialVVelocity, 2, diff);
}

void Fluid::draw() {
    graphics->clearScreen();
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++){
            graphics->drawPixel(i, j, density[IX(i, j, height)]);
        }
}