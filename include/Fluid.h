#pragma once

#include "stdafx.h"
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
public:
    Fluid(int w, int h, float diff);
    ~Fluid();
    void setSize(int w, int h);
    void addSource(float dt);
    void diffuse(float dt);
    void project();
    void abvect();
    void setBounds(int direction);

};