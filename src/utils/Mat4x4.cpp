#include "Mat4x4.hpp"
#include <iostream>

Mat4x4::Mat4x4() {
    for (int i = 0; i < 4;i++)
        for (int j = 0; j < 4;j++)
            m[i][j] = 0.0f;
}

Mat4x4::Mat4x4(float _m[4][4]) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = _m[i][j];
}

void Mat4x4::print() const { /// for debugging :))  
    std::cout << "\n(\n";
    for (int i = 0;i < 4;i++) {
        std::cout << " (";
        for (int j = 0;j < 4;j++) std::cout << this->m[i][j] << ((j<3)?", ":"");
        std::cout << ")\n";
    }
    std::cout << ")\n";
}


Mat4x4 Mat4x4::identity() {
    Mat4x4 m;
    for (int i = 0;i < 4;i++) m.m[i][i] = 1.0f;
    return m;
}

Mat4x4 Mat4x4::projection(float width, float height, float viewAngle = acos(-1)/2.0f, float znear = 0.1f, float zfar = 1000.0f) {
    Mat4x4 m;
    float aspectRatio = height / width;
    float fov = 1.0f / tanf(viewAngle / 2.0f); /// field of view
    float q = zfar / (zfar - znear);
    m.m[0][0] = aspectRatio*fov;
    m.m[1][1] = fov;
    m.m[2][2] = q;
    m.m[2][3] = 1;
    m.m[3][2] = -znear * q;
    return m;
}
Mat4x4 Mat4x4::translation(float x, float y, float z) {
    Mat4x4 m;
    m.m[3][0] = x;
    m.m[3][1] = y;
    m.m[3][2] = z;
    return m;
};

Mat4x4 Mat4x4::rotationX(float theta) {
	Mat4x4 m = identity();
    m.m[1][1] = cosf(theta);
    m.m[1][2] = sinf(theta);
    m.m[2][1] = -sinf(theta);
    m.m[2][2] = cosf(theta);

    return m;
}

Mat4x4 Mat4x4::rotationY(float theta) {
    Mat4x4 m = identity();
    m.m[0][0] = cosf(theta);
    m.m[0][2] = sinf(theta);
    m.m[2][0] = -sinf(theta);
    m.m[2][2] = cosf(theta);
    return m;
}

Mat4x4 Mat4x4::rotationZ(float theta) {
    Mat4x4 m = identity();
    m.m[0][0] = cosf(theta);
    m.m[0][1] = sinf(theta);
    m.m[1][0] = -sinf(theta);
    m.m[1][1] = cosf(theta);
    return m;
}

Mat4x4 Mat4x4::operator = (const Mat4x4 &other) {
    for (int i = 0;i < 4; i++)
        for (int j = 0; j < 4; j++)
            this->m[i][j] = other.m[i][j];
    return *this;
}

Mat4x4& Mat4x4:: operator *= (const Mat4x4& other) {
    Mat4x4 m;
    for (int i = 0;i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                m.m[i][j] += this->m[i][k] * other.m[k][j];
    *this = m;
    return *this;
}

Mat4x4 Mat4x4::operator * (const Mat4x4& other) {
    Mat4x4 m;
    for (int i = 0;i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                m.m[i][j] += this->m[i][k] * other.m[k][j];
    return m;
}