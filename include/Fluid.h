#pragma once

#define RAND_MAX 1

#include <stdio.h>
#include "stdafx.h"
#include "Graphics.h"
#include <cmath>
#include <vector>
#include <algorithm>

class Fluid {
private:
    int height;
    int width;
    int size;
    float diff;
    int x, y, xPrev, yPrev;
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
    void addSource(std::vector<float>& vector, std::vector<float>& source, float dt);
    void setBounds(std::vector<float>& vector,int direction);
    void diffuse(std::vector<float>& final, std::vector<float>& initial, int direction, float dt);
    void project();
    void advect(std::vector<float>& vec1, std::vector<float>& vec2, std::vector<float>& vec3, std::vector<float>& vec4, int direction, float dt);
    void velStep(float dt);
    void densStep(float dt);
    void draw();
    void setMouseCoord(int x, int y);
    void addFromUser(int x, int y);

};