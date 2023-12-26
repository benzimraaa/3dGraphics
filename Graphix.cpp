#include "Graphix.h"
#include <iostream>

const char* FILE_PATH = "/home/mefathim-tech-25/Downloads/whoosh-cinematic-161021.wav";

Graphix::Graphix(int width, int height) : 
    width(width), height(height), 
    pixels(width, std::vector<Color>(height, Color(0, 0, 0)))
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    }

    window = SDL_CreateWindow(
        "SDL Canvas Example",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr) {
        SDL_Log("Unable to create window: %s", SDL_GetError());
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        SDL_Log("Unable to create renderer: %s", SDL_GetError());
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

Graphix::~Graphix() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphix::putPixel(int x, int y, const Color& color, bool isTransformed) {
    
    if (!isTransformed)
    {
        Vec3<float> p(x, y);
        p = screenTransformation(p);
        x = p.x;
        y = p.y;
    }
    Vec3<int> p(x, y);
    coordinateTransformation(p);

    if (p.x >= 0 && p.x < width && p.y >= 0 && p.y < height) {
        pixels[p.x][p.y] = color;}
}


void Graphix::drawLine(const Vec3<float> &p, const Vec3<float> &q, const Color &color) {

    auto tempP = p.homogeneous();
    auto tempQ = q.homogeneous();

    auto p1 = screenTransformation(tempP);
    auto p2 = screenTransformation(tempQ);

    int x0 = p1.x;
    int y0 = p1.y;

    int x1 = p2.x;
    int y1 = p2.y;

    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;

    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);

    int err = dx + dy;
    while (true)
    {
        putPixel(x0, y0, color);
        int e2 = 2 * err;
        if (e2 >= dy)
        /* e_xy+e_x > 0 */
        {
            if (x0 == x1) break;
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx){
            /* e_xy+e_y < 0 */
            if (y0 == y1) break;
            err += dx;
            y0 += sy;
        }

    }
    
    

}

void Graphix::drawEllipse(const Vec3<int> &center, int radiusX, int radiusY, const Color &color)
{
    long x = -radiusX;
    long y = 0; 
    long e2 = radiusY;
    long dx = (1 + 2 * x) * e2 * e2;
    long dy = x * x;    
    long err = dx + dy;

    while (x <= 0)
    {
        putPixel(center.x - x, center.y + y, color);
        putPixel(center.x + x, center.y + y, color);
        putPixel(center.x + x, center.y - y, color);
        putPixel(center.x - x, center.y - y, color);
        e2 = 2 * err;
        if (e2 >= dx)
        {
            x++;
            err += dx += 2 * radiusY * radiusY;
        }
        if (e2 <= dy)
        {
            y++;
            err += dy += 2 * radiusX * radiusX;
        }
    }
    while (y++ < radiusY)
    {
        putPixel(center.x, center.y + y, color);
        putPixel(center.x, center.y - y, color);
    }
    
    
}

void Graphix::drawPolygon(const std::vector<Vec3<int>> &points, const Color &color)
{
    for (int i = 0; i < points.size() - 1; ++i) {
        drawLine(points[i], points[i + 1], color);
    }
    drawLine(points[points.size() - 1], points[0], color);
}

void Graphix::render() {
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            SDL_SetRenderDrawColor(renderer, pixels[x][y].getRed(), pixels[x][y].getGreen(), pixels[x][y].getBlue(), pixels[x][y].getAlpha());
            SDL_RenderDrawPoint(renderer, x, y);
        }
    }
    SDL_RenderPresent(renderer);

}

void Graphix::coordinateTransformation(Vec3<int> &p)
{
    Vec3<int> center(width / 2, height / 2);
    p.y *= -1;
    p += center;
    
}

Vec3<float> Graphix::screenTransformation(Vec3<float> &p) const
{
    Vec3<float> q(width / 2, height / 2);
    q.x *= p.x;
    q.y *= p.y;
    return q;
}

void Graphix::rotateSpace(float angle)
{
}

void Graphix::clear()
{
    pixels = std::vector<std::vector<Color>>(width, std::vector<Color>(height, Color(0, 0, 0)));
}
