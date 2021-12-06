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
    std::vector<float> initialHVelocity;
    std::vector<float> hvelocity;
    std::vector<float> initialVVelocity;
    std::vector<float> vvelocity;
    Graphics *graphics;
public:
    Fluid(int w, int h, float diff, Graphics *graphics);
    ~Fluid();
    void setSize(int w, int h);
    void addSource(std::vector<float> vector, std::vector<float> source, float dt);
    void setBounds(int direction);
    void diffuse(std::vector<float> final, std::vector<float> initial, int direction, float dt);
    void project();
    void advect(int direction, float dt);
    void velStep(float dt);
    void densStep(float dt);
    void draw();

};