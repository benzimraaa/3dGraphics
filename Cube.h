#pragma once
#include <vector>
#include "Vec3.h"
#include "LinearTransformation.h"


class Cube
{
    private:
    float shift = 0.0f;
public:
    Cube();
    ~Cube();
    std::vector<Vec3<float>> vertices;
    std::vector<std::pair<int, int>> edges;
    void scale(float factor);
    void shiftZ(float n);
    void transform(LinearTransformation& lt);
};
