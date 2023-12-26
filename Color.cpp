#ifndef COLOR_H
#define COLOR_H
#include <SDL2/SDL_stdinc.h>

// A simple class to represent a color
class Color {
public:
    Color(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255) : r(r), g(g), b(b), a(a) {}

    Uint8 getRed() const { return r; }
    Uint8 getGreen() const { return g; }
    Uint8 getBlue() const { return b; }
    Uint8 getAlpha() const { return a; }

private:
    Uint8 r, g, b, a;
};
#endif // COLOR_H
