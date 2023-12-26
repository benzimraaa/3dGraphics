#pragma once
#include "Vec3.h"

class LinearTransformation
{
private:
    float matrix[3][3];
public:
    LinearTransformation(
            float m00, float m01, float m02,
            float m10, float m11, float m12,
            float m20, float m21, float m22
        ) {
            matrix[0][0] = m00; matrix[0][1] = m01; matrix[0][2] = m02;
            matrix[1][0] = m10; matrix[1][1] = m11; matrix[1][2] = m12;
            matrix[2][0] = m20; matrix[2][1] = m21; matrix[2][2] = m22;
        }
    static LinearTransformation identity(){
        return {1.0f, 0.0f, 0.0f,
                0.0f, 1.0f, 0.0f,
                0.0f,0.0f, 1.0f};
    }
    static LinearTransformation RotationX(float angle){
        return {1.0f, 0.0f, 0.0f,
                0.0f, cos(angle), -sin(angle),
                0.0f, sin(angle), cos(angle)};
    }
    static LinearTransformation RotationY(float angle){
        return {cos(angle), 0.0f, sin(angle),
                0.0f, 1.0f, 0.0f,
                -sin(angle), 0.0f, cos(angle)};
    }
    static LinearTransformation RotationZ(float angle){
        return {cos(angle), -sin(angle), 0.0f,
                sin(angle), cos(angle), 0.0f,
                0.0f, 0.0f, 1.0f};
    }

    Vec3<float> operator*(const Vec3<float>& v) const{
        return {v.x * matrix[0][0] + v.y * matrix[0][1] + v.z * matrix[0][2],
                v.x * matrix[1][0] + v.y * matrix[1][1] + v.z * matrix[1][2],
                v.x * matrix[2][0] + v.y * matrix[2][1] + v.z * matrix[2][2]};
    }

    LinearTransformation operator*(const LinearTransformation& other) const{
        return {matrix[0][0] * other.matrix[0][0] + matrix[0][1] * other.matrix[1][0] + matrix[0][2] * other.matrix[2][0],
                matrix[0][0] * other.matrix[0][1] + matrix[0][1] * other.matrix[1][1] + matrix[0][2] * other.matrix[2][1],
                matrix[0][0] * other.matrix[0][2] + matrix[0][1] * other.matrix[1][2] + matrix[0][2] * other.matrix[2][2],
                matrix[1][0] * other.matrix[0][0] + matrix[1][1] * other.matrix[1][0] + matrix[1][2] * other.matrix[2][0],
                matrix[1][0] * other.matrix[0][1] + matrix[1][1] * other.matrix[1][1] + matrix[1][2] * other.matrix[2][1],
                matrix[1][0] * other.matrix[0][2] + matrix[1][1] * other.matrix[1][2] + matrix[1][2] * other.matrix[2][2],
                matrix[2][0] * other.matrix[0][0] + matrix[2][1] * other.matrix[1][0] + matrix[2][2] * other.matrix[2][0],
                matrix[2][0] * other.matrix[0][1] + matrix[2][1] * other.matrix[1][1] + matrix[2][2] * other.matrix[2][1],
                matrix[2][0] * other.matrix[0][2] + matrix[2][1] * other.matrix[1][2] + matrix[2][2] * other.matrix[2][2]};
    }
};
