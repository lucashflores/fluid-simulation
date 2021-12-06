#pragma once

#include "stdafx.h"
#include "Graphics.h"
#include <vector>

class Fluid {
private:
    int height;
    int width;
    int size;
    float diff;
    std::vector<float> source;
    std::vector<float> initialDensity;
    std::vector<float> density;
    std::vector<float> hvelocity;
    std::vector<float> vvelocity;
    Graphics *graphics;
public:
    Fluid(int w, int h, float diff, Graphics *graphics);
    ~Fluid();
    void setSize(int w, int h);
    void addSource(float dt);
    void setBounds(int direction);
    void diffuse(int direction, float dt);
    void project();
    void advect();
    void densStep(float dt);
    void draw();

};