#ifndef Vec3_H
#define Vec3_H


#include <ostream>
#include <cmath>

template<typename T>
class Vec3
{    
public:
    T x;
    T y;
    T z;

    Vec3(T x, T y, T z);
    Vec3(T x, T y);
    ~Vec3();

    template<typename U>
    Vec3(const Vec3<U>& other) : x(static_cast<T>(other.x)), y(static_cast<T>(other.y)) {}
    Vec3 operator+(const Vec3& p) const;
    Vec3 operator-(const Vec3& p) const;
    Vec3& operator+=(const Vec3& p);
    Vec3& operator-=(const Vec3& p);
    Vec3<T> operator-() const;
    Vec3 operator*(const float& f) const;
    Vec3 operator/(const float& f) const;
    Vec3& operator*=(const float& f);
    Vec3 rotate(const float& angle) const;
    Vec3 rotate(const float& angle, const Vec3& origin) const;
    float dot(const Vec3& p) const;
    float norm2() const;
    float length() const;
    void setLength(float length);
    Vec3 projectionVector(const Vec3& p) const;
    Vec3<float> homogeneous() const;

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vec3<U>& p);

};

template<typename T>
Vec3<T>::Vec3(T x, T y, T z): x(x), y(y), z(z) {}

template<typename T>
Vec3<T>::Vec3(T x, T y): x(x), y(y), z(1) {}

template<typename T>
Vec3<T>::~Vec3() {}

template<typename T>
Vec3<T> Vec3<T>::operator+(const Vec3& p) const
{
    return Vec3<T>(this->x + p.x, this->y + p.y, this->z + p.z);
}

template<typename T>
Vec3<T> Vec3<T>::operator-(const Vec3& p) const
{
    return Vec3<T>(this->x - p.x, this->y - p.y, this->z - p.z);
}

template<typename T>
Vec3<T> Vec3<T>::operator-() const {
        return Vec3<T>(-this->x, -this->y, -this->z);
}
template<typename T>
Vec3<T>& Vec3<T>::operator+=(const Vec3& p)
{
    this->x += p.x;
    this->y += p.y;
    this->z += p.z;
    return *this;
}

template<typename T>
Vec3<T>& Vec3<T>::operator-=(const Vec3& p)
{
    this->x -= p.x;
    this->y -= p.y;
    this->z -= p.z;
    return *this;
}

template<typename T>
Vec3<T> Vec3<T>::operator*(const float& f) const
{
    return Vec3<T>(static_cast<T>(this->x * f), 
                   static_cast<T>(this->y * f), 
                   static_cast<T>(this->z * f)
                   );
}

template<typename T>
Vec3<T> Vec3<T>::operator/(const float& f) const
{
    return Vec3<T>(static_cast<T>(this->x / f), 
                   static_cast<T>(this->y / f),
                   static_cast<T>(this->z / f)
                   );
}

template<typename T>
Vec3<T>& Vec3<T>::operator*=(const float& f)
{
    this->x = static_cast<T>(this->x * f);
    this->y = static_cast<T>(this->y * f);
    this->z = static_cast<T>(this->z * f);
    return *this;
}



template<typename T>
float Vec3<T>::dot(const Vec3& p) const
{
    return static_cast<float>(this->x * p.x + this->y * p.y + this->z * p.z);
}

template<typename T>
float Vec3<T>::norm2() const
{
    return static_cast<float>(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
}

template<typename T>
float Vec3<T>::length() const
{
    return sqrt(norm2());
}

template<typename T>
void Vec3<T>::setLength(float length)
{
    float norm = this->length();
    this->x = static_cast<T>(this->x / norm * length);
    this->y = static_cast<T>(this->y / norm * length);
    this->z = static_cast<T>(this->z / norm * length);
}

template<typename T>
Vec3<T> Vec3<T>::projectionVector(const Vec3& p) const
{
    return p * (this->dot(p) / p.norm2());
}

template <typename T>
Vec3<float> Vec3<T>::homogeneous() const
{
    // if z == 0
    if (this->z == 0)
    {
        return Vec3<T>(0,0,0);
    }
    return Vec3<float>(this->x / this->z, this->y / this->z, 1);
}

template<typename U>
std::ostream& operator<<(std::ostream& os, const Vec3<U>& p)
{
    os << "(" << p.x << ", " << p.y << ", " << p.z << ")";
    return os;
}


#endif // Vec3_H