#include "Fluid.h"

Fluid::Fluid(int w, int h, float diff, Graphics *graphics, float scaleX, float scaleY): height(h), width(w), diff(diff),
density(), initialDensity(), initialHVelocity(), hvelocity(), initialVVelocity(), vvelocity(), x(), y(), xPrev(), yPrev(), scaleX(scaleX), scaleY(scaleY){
    this->graphics = graphics;
    setSize(w, h);
    initialDensity.assign(size, 0);
    density.assign(size, 0);
    initialVVelocity = std::vector<float>(size, 0);
    initialHVelocity = std::vector<float>(size, 0);
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

void Fluid::addSource(std::vector<float>& vector, std::vector<float>& source, float dt) {
    for (int i = 0; i < size; i++) {
        // vector[i] += dt*source[i];
        vector[i] -= 1*dt;
    }
}

void Fluid::setBounds(std::vector<float>& vector, int direction) {
    /*
    1 - horizontal
    2 - vertical
    */
    for (int i = 1; i <= width; i++) {
        vector[IX(i, 0, width)] = direction == 2? -vector[IX(i, 1, width)]:vector[IX(i, 1, width)];
        vector[IX(i, height + 1, width)] = direction == 2? -vector[IX(i, height, width)]:vector[IX(i, height, width)];
    }

    for (int i = 1; i <= height; i++) {
        vector[IX(0, i, width)] = direction == 1? -vector[IX(1, i, width)]:vector[IX(1, i, width)];
        vector[IX(width + 1, i, width)] = direction == 1? -vector[IX(width, i, width)]:vector[IX(width, i, width)];
    }


    //Canto superior esquerdo
    vector[IX(0, 0, width)] = (vector[IX(0, 1, width)] + vector[IX(1, 0, width)])/2;
    //Canto superior direito
    vector[IX(width + 1, 0, width)] = (vector[IX(width + 1, 1, width)] + vector[IX(width, 0, width)])/2;
    //Canto inferior esquerdo
    vector[IX(0, height + 1, width)] = (vector[IX(0, height, width)] + vector[IX(1, height + 1, width)])/2;
    //Canto inferior direito
    vector[IX(width + 1, height + 1, width)] = (vector[IX(width, height + 1, width)] + vector[IX(width + 1, height, width)])/2;
    
}

void Fluid::diffuse(std::vector<float>& final, std::vector<float>& initial, int direction, float dt) {
    float coef = diff * dt * size;

    for (int n = 0; n < 16; n++) {
        for (int i = 1; i <= width; i++)
            for (int j = 1; j <= height; j++)
                final[IX(i, j, width)] = (initial[IX(i, j, width)] + coef * (final[IX(i-1, j, width)] + final[IX(i+1, j, width)] + final[IX(i, j-1, width)] + final[IX(i, j+1, width)])) / (4*coef + 1);
        setBounds(final, direction);
    }
}

void Fluid::advect(std::vector<float>& vec1, std::vector<float>& vec2, std::vector<float>& vec3, std::vector<float>& vec4, int direction, float dt) {

    int i, j, i0, j0, i1, j1;
    float x, y, s0, t0, s1, t1, dtw, dth;

    dtw = dt*width;
    dth = dt*height;
    for (i = 1; i <= width; i++) {
        for (j = 1; j <= height; j++) {

            x = i - dtw*vec3[IX(i, j, width)];
            y = j - dth*vec4[IX(i, j, width)];

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

            vec1[IX(i, j, width)] = s0*(t0*vec2[IX(i0, j0, width)]+t1*vec2[IX(i0, j1, width)]) +
                                        s1*(t0*vec2[IX(i1, j0, width)]+t1*vec2[IX(i1, j1, width)]);
        }
    }

    setBounds(vec1, direction);
}

void Fluid::densStep(float dt) {
    addSource(density, initialDensity, dt);
    initialDensity.swap(density);
    diffuse(density, initialDensity, 0, dt);
    initialDensity.swap(density);
    advect(density, initialDensity, hvelocity, vvelocity, 0, dt);
}

void Fluid::velStep(float dt) {
    // addSource(hvelocity, initialHVelocity, dt);
    // addSource(vvelocity, initialVVelocity, dt);

    initialHVelocity.swap(hvelocity);
    diffuse(hvelocity, initialHVelocity, 1, diff);

    initialVVelocity.swap(vvelocity);
    diffuse(vvelocity, initialVVelocity, 2, diff);

    project();

    initialHVelocity.swap(hvelocity);
    initialVVelocity.swap(vvelocity);

    advect(hvelocity, initialHVelocity, initialHVelocity, initialVVelocity, 1, dt);
    advect(vvelocity, initialVVelocity, initialHVelocity, initialVVelocity, 2, dt);

    project();
}

void Fluid::project() {
    int i, j, k;
    float h = 1/(sqrt(size));
    for ( i=1 ; i<=width ; i++ ) {
        for ( j=1 ; j<=height ; j++ ) {
            initialVVelocity[IX(i,j,width)] = -0.5*h*(hvelocity[IX(i+1,j,width)]-hvelocity[IX(i-1,j,width)]+ //TALVEZ MUDAR O hv para hw
            vvelocity[IX(i,j+1,width)]-vvelocity[IX(i,j-1,width)]);
            initialHVelocity[IX(i,j,width)] = 0;
        }
    }
    setBounds(initialVVelocity, 0);
    setBounds(initialHVelocity, 0);
    for ( k=0 ; k<20 ; k++ ) {
        for ( i=1 ; i<=width ; i++ ) {
            for ( j=1 ; j<=height ; j++ ) {
                initialHVelocity[IX(i,j,width)] = (initialVVelocity[IX(i,j,width)]+initialHVelocity[IX(i-1,j,width)]+initialHVelocity[IX(i+1,j,width)]+
                initialHVelocity[IX(i,j-1,width)]+initialHVelocity[IX(i,j+1,width)])/4;
            }
        }   
        setBounds(initialHVelocity, 0);
    }
    for ( i=1 ; i<=width ; i++ ) {
        for ( j=1 ; j<=height ; j++ ) {
            hvelocity[IX(i,j,width)] -= 0.5*(initialHVelocity[IX(i+1,j,width)]-initialHVelocity[IX(i-1,j,width)])/h;
            vvelocity[IX(i,j,width)] -= 0.5*(initialHVelocity[IX(i,j+1,width)]-initialHVelocity[IX(i,j-1,width)])/h;
        }
    }
    //CONFERIR DEPOIS!!!!!
    setBounds(hvelocity, 2);
    setBounds(vvelocity, 1);
}

void Fluid::draw() {
    graphics->clearScreen();
    for (int i = 1; i <= width; i++)
        for (int j = 1; j <= height; j++){
            if (density[IX(i, j, width)] > 255)
                density[IX(i, j, width)] = 255;
            else if (density[IX(i, j, width)] < 0)
                density[IX(i, j, width)] = 0;
            if (density[IX(i, j, width)] != 0) {
                //printf("%f\n", density[IX(i, j, height)]);
                graphics->drawPixel(i-1, j-1, density[IX(i, j, width)]);
            }
                
        }
}

void Fluid::setMouseCoord(int x, int y) {
    xPrev = this->x;
    yPrev = this->y;
    this->x = x / scaleX + 1;
    this->y = y / scaleY + 1;
    if(this->x == 0) this->x = 1;
    if(this->y == 0) this->y = 1;
}

void Fluid::addFromUser(int x, int y) {
    setMouseCoord(x, y);
    const float velScale = 5;
    density[IX(this->x, this->y, width)] += 255;
    //printf("%f\n", density[IX(this->x, this->y, width)]);
    vvelocity[IX(this->x, this->y, width)] += velScale * scaleY * (this->y - yPrev);
    hvelocity[IX(this->x, this->y, width)] += velScale * scaleX * (this->x - xPrev);
}