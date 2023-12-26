#ifndef VEC2_H
#define VEC2_H


#include <ostream>
#include <cmath>

template<typename T>
class Vec2
{    
public:
    T x;
    T y;

    Vec2(T x, T y);
    ~Vec2();

    template<typename U>
    Vec2(const Vec2<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    Vec2 operator+(const Vec2& p) const;
    Vec2 operator-(const Vec2& p) const;
    Vec2& operator+=(const Vec2& p);
    Vec2& operator-=(const Vec2& p);
    Vec2<T> operator-() const;
    Vec2 operator*(const float& f) const;
    Vec2 operator/(const float& f) const;
    Vec2& operator*=(const float& f);
    Vec2 rotate(const float& angle) const;
    Vec2 rotate(const float& angle, const Vec2& origin) const;
    float dot(const Vec2& p) const;
    float norm2() const;
    float length() const;
    void setLength(float length);
    Vec2 projectionVector(const Vec2& p) const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vec2<U>& p);

};

template<typename T>
Vec2<T>::Vec2(T x, T y): x(x), y(y) {}

template<typename T>
Vec2<T>::~Vec2() {}

template<typename T>
Vec2<T> Vec2<T>::operator+(const Vec2& p) const
{
    return Vec2<T>(this->x + p.x, this->y + p.y);
}

template<typename T>
Vec2<T> Vec2<T>::operator-(const Vec2& p) const
{
    return Vec2<T>(this->x - p.x, this->y - p.y);
}

template<typename T>
Vec2<T> Vec2<T>::operator-() const {
        return Vec2<T>(-this->x, -this->y);
}
template<typename T>
Vec2<T>& Vec2<T>::operator+=(const Vec2& p)
{
    this->x += p.x;
    this->y += p.y;
    return *this;
}

template<typename T>
Vec2<T>& Vec2<T>::operator-=(const Vec2& p)
{
    this->x -= p.x;
    this->y -= p.y;
    return *this;
}

template<typename T>
Vec2<T> Vec2<T>::operator*(const float& f) const
{
    return Vec2<T>(static_cast<T>(this->x * f), static_cast<T>(this->y * f));
}

template<typename T>
Vec2<T> Vec2<T>::operator/(const float& f) const
{
    return Vec2<T>(static_cast<T>(this->x / f), static_cast<T>(this->y / f));
}

template<typename T>
Vec2<T>& Vec2<T>::operator*=(const float& f)
{
    this->x = static_cast<T>(this->x * f);
    this->y = static_cast<T>(this->y * f);
    return *this;
}

template<typename T>
Vec2<T> Vec2<T>::rotate(const float& angle) const
{
    T newX = static_cast<T>(this->x * cos(angle) - this->y * sin(angle));
    T newY = static_cast<T>(this->x * sin(angle) + this->y * cos(angle));
    return Vec2<T>(newX, newY);
}

template<typename T>
Vec2<T> Vec2<T>::rotate(const float& angle, const Vec2& origin) const
{   
    T dx = this->x - origin.x;
    T dy = this->y - origin.y;

    T newX = static_cast<T>(dx * cos(angle) - dy * sin(angle));
    T newY = static_cast<T>(dx * sin(angle) + dy * cos(angle));
    return Vec2<T>(newX, newY) + origin;
}

template<typename T>
float Vec2<T>::dot(const Vec2& p) const
{
    return static_cast<float>(this->x * p.x + this->y * p.y);
}

template<typename T>
float Vec2<T>::norm2() const
{
    return static_cast<float>(pow(this->x, 2) + pow(this->y, 2));
}

template<typename T>
float Vec2<T>::length() const
{
    return sqrt(norm2());
}

template<typename T>
void Vec2<T>::setLength(float length)
{
    float norm = this->length();
    this->x = static_cast<T>(this->x / norm * length);
    this->y = static_cast<T>(this->y / norm * length);
}

template<typename T>
Vec2<T> Vec2<T>::projectionVector(const Vec2& p) const
{
    return p * (this->dot(p) / p.norm2());
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Vec2<U>& p)
{
    os << "(" << p.x << ", " << p.y << ")";
    return os;
}


#endif // VEC2_H