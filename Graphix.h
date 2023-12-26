#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "Color.cpp"
#include "Vec3.h"

class Graphix {
public:
    Graphix(int width, int height);
    ~Graphix();

    void putPixel(int x, int y, const Color& color = Color(0, 0, 0), bool isTransformed = true);
    void drawLine(const Vec3<float>& p1, const Vec3<float>& p2, const Color& color = Color(255, 255, 255));
    void drawEllipse(const Vec3<int>& center, int radiusX, int radiusY, const Color& color = Color(255, 255, 255));
    void drawPolygon(const std::vector<Vec3<int>>& points, const Color& color = Color(255, 255, 255));  // Draw a polygon with the given points
    void render();
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    void coordinateTransformation(Vec3<int>& p);
    Vec3<float> screenTransformation(Vec3<float>& p) const;
    void rotateSpace(float angle);
    void clear();
    Uint32 lastUpdateTime = SDL_GetTicks();
    


private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width;
    int height;
    std::vector<std::vector<Color>> pixels;
};
