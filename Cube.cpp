#include "Cube.h"

Cube::Cube()
{
    vertices.push_back(Vec3<float>(-1, -1, -1));
    vertices.push_back(Vec3<float>(1, -1, -1));
    vertices.push_back(Vec3<float>(1, 1, -1));
    vertices.push_back(Vec3<float>(-1, 1, -1));
    vertices.push_back(Vec3<float>(-1, -1, 1));
    vertices.push_back(Vec3<float>(1, -1, 1));
    vertices.push_back(Vec3<float>(1, 1, 1));
    vertices.push_back(Vec3<float>(-1, 1, 1));

    edges.push_back(std::pair<int, int>(0, 1));
    edges.push_back(std::pair<int, int>(0, 4));
    edges.push_back(std::pair<int, int>(0, 3));
    edges.push_back(std::pair<int, int>(1, 2));
    edges.push_back(std::pair<int, int>(1, 5));
    edges.push_back(std::pair<int, int>(2, 3));
    edges.push_back(std::pair<int, int>(2, 6));
    edges.push_back(std::pair<int, int>(3, 7));
    edges.push_back(std::pair<int, int>(4, 5));
    edges.push_back(std::pair<int, int>(4, 7));
    edges.push_back(std::pair<int, int>(5, 6));
    edges.push_back(std::pair<int, int>(6, 7));

}

Cube::~Cube()
{
}

void Cube::scale(float factor)
{
    for (auto& vertex : vertices)
    {
        vertex.x *= factor;
        vertex.y *= factor;
        vertex.z *= factor;
    }
}

void Cube::shiftZ(float n)
{
    shift += n;
    for (auto& vertex : vertices)
    {
        vertex.z += n;
    }
}

void Cube::transform(LinearTransformation &lt)
{
    for (auto& vertex : vertices)
    {   
        // shift z back
        vertex.z -= shift;
        vertex = lt * vertex;
        // shift z forward
        vertex.z += shift;
    }
}
