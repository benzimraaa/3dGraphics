// #include "Star.h"
// #include <cmath>

// Star::Star(int vertices, int innerRadius, int outerRadius, Vec2<int> center, Color color)
//     :Entity(center, color)
// {
//     this->vertices = vertices;
//     this->innerRadius = innerRadius;
//     this->outerRadius = outerRadius;
//     setType("Star");
//     starModel();
// }

// Star::~Star()
// {
// }

// void Star::starModel()
// {
//     vector<Vec2<int>> spoints;
//     float angle = M_PI / vertices;
//     for (int i = 0; i < vertices*2; i++)
//     {
//         int r = (i % 2 == 0 ? outerRadius : innerRadius);
//         int x = r * cos(i * angle);
//         int y = r * sin(i * angle);
//         Vec2<int> p(x, y);
//         spoints.push_back(p);
//     }
//     setPoints(spoints);
// }