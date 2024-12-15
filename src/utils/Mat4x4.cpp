#include "Mat4x4.hpp"


Mat4x4::Mat4x4() {
    for (int i = 0; i < 4;i++)
        for (int j = 0; j < 4;j++)
            m[i][j] = 0.0f;
}


Mat4x4::Mat4x4(std::initializer_list<float>  _m) {
    auto* it = _m.begin();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = *it++;
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

Mat4x4 Mat4x4::perspectiveProjection(float width, float height, float viewAngle, float znear, float zfar) {
    Mat4x4 m;
    float inverseAspectRatio = height / width;
    float fov = 1.0f / tanf(viewAngle / 2.0f); /// field of view
    float q1 =  (-zfar - znear)/ (znear - zfar);
    float q2 =  2 * znear * zfar / (znear - zfar);
    m.m[0][0] = fov * inverseAspectRatio;
    m.m[1][1] = fov;
    m.m[2][2] = q1;
    m.m[2][3] = q2;
    m.m[3][2] = 1;
    return m;
}

Mat4x4 Mat4x4::screenTransform(float width, float height) {
    Mat4x4 m = Mat4x4::identity();
    m.m[0][0] = m.m[0][3] = width * 0.5f;
    m.m[1][1] = m.m[1][3] = height * 0.5f;
    return m;
}
Mat4x4 Mat4x4::translation(float x, float y, float z) {
    Mat4x4 m = Mat4x4::identity();
    m.m[0][3] = x;
    m.m[1][3] = y;
    m.m[2][3] = z;
    return m;
};


Mat4x4 Mat4x4::rotationX(float theta) {
	Mat4x4 m = identity();
    m.m[1][1] = cosf(theta);
    m.m[2][1] = sinf(theta);
    m.m[1][2] = -sinf(theta);
    m.m[2][2] = cosf(theta);
    return m;
}

Mat4x4 Mat4x4::rotationY(float theta) {
    Mat4x4 m = identity();
    m.m[0][0] = cosf(theta);
    m.m[2][0] = sinf(theta);
    m.m[0][2] = -sinf(theta);
    m.m[2][2] = cosf(theta);
    return m;
}

Mat4x4 Mat4x4::rotationZ(float theta) {
    Mat4x4 m = identity();
    m.m[0][0] = cosf(theta);
    m.m[1][0] = sinf(theta);
    m.m[0][1] = -sinf(theta);
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
                m.m[i][j] += (this->m[i][k] * other.m[k][j]);
    return m;
}

