
#include "matrix4.h"

#include <iostream>
#include <cmath>


//------------------------------------------------------------------------------
/// @brief      Set to the identiy matrix
///
/// @return     the updated matrix
///
matrix4& matrix4::id() {
    m_mat = {{
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 }};
    return *this;
}


//------------------------------------------------------------------------------
/// @brief      Add another matrix4 to this vector
///
/// @param[in]  other  The other matrix
///
/// @return     the updated matrix
///
matrix4& matrix4::add(const matrix4& other) {
    m_mat[0] += other.m_mat[0];
    m_mat[1] += other.m_mat[1];
    m_mat[2] += other.m_mat[2];
    m_mat[3] += other.m_mat[3];
    m_mat[4] += other.m_mat[4];
    m_mat[5] += other.m_mat[5];
    m_mat[6] += other.m_mat[6];
    m_mat[7] += other.m_mat[7];
    m_mat[8] += other.m_mat[8];
    m_mat[9] += other.m_mat[9];
    m_mat[10] += other.m_mat[10];
    m_mat[11] += other.m_mat[11];
    m_mat[12] += other.m_mat[12];
    m_mat[13] += other.m_mat[13];
    m_mat[14] += other.m_mat[14];
    m_mat[15] += other.m_mat[15];
    return *this;
}
matrix4& matrix4::operator+=(const matrix4& other) {
    return add(other);
}

//------------------------------------------------------------------------------
/// @brief      Subtract another matrix4 from this vector
///
/// @param[in]  other  The other matrix
///
/// @return     { description_of_the_return_value }
///
matrix4& matrix4::sub(const matrix4& other) {
    m_mat[0] -= other.m_mat[0];
    m_mat[1] -= other.m_mat[1];
    m_mat[2] -= other.m_mat[2];
    m_mat[3] -= other.m_mat[3];
    m_mat[4] -= other.m_mat[4];
    m_mat[5] -= other.m_mat[5];
    m_mat[6] -= other.m_mat[6];
    m_mat[7] -= other.m_mat[7];
    m_mat[8] -= other.m_mat[8];
    m_mat[9] -= other.m_mat[9];
    m_mat[10] -= other.m_mat[10];
    m_mat[11] -= other.m_mat[11];
    m_mat[12] -= other.m_mat[12];
    m_mat[13] -= other.m_mat[13];
    m_mat[14] -= other.m_mat[14];
    m_mat[15] -= other.m_mat[15];
    return *this;
}
matrix4& matrix4::operator-=(const matrix4& other) {
    return sub(other);
}

//------------------------------------------------------------------------------
/// @brief      Scale this matrix
///
/// @param[in]  s     The scale parameter
///
/// @return     { description_of_the_return_value }
///
matrix4& matrix4::scale(scalar s) {
    m_mat[0] *= s;
    m_mat[1] *= s;
    m_mat[2] *= s;
    m_mat[3] *= s;
    m_mat[4] *= s;
    m_mat[5] *= s;
    m_mat[6] *= s;
    m_mat[7] *= s;
    m_mat[8] *= s;
    m_mat[9] *= s;
    m_mat[10] *= s;
    m_mat[11] *= s;
    m_mat[12] *= s;
    m_mat[13] *= s;
    m_mat[14] *= s;
    m_mat[15] *= s;
    return *this;
}
matrix4& matrix4::operator*=(scalar s) {
    return scale(s);
}

//------------------------------------------------------------------------------
/// @brief      Multiply this matrix
///
/// @param[in]  other  The other matrix
///
/// @return     { description_of_the_return_value }
///
matrix4& matrix4::mul(const matrix4& other) {
    auto &m00 = other.m_mat[0], &m01 = other.m_mat[1],
         &m02 = other.m_mat[2], &m03 = other.m_mat[3],

         &m10 = other.m_mat[4], &m11 = other.m_mat[5],
         &m12 = other.m_mat[6], &m13 = other.m_mat[7],

         &m20 = other.m_mat[8], &m21 = other.m_mat[9],
         &m22 = other.m_mat[10], &m23 = other.m_mat[11],

         &m30 = other.m_mat[12], &m31 = other.m_mat[13],
         &m32 = other.m_mat[14], &m33 = other.m_mat[15];

    auto b0  = m_mat[0], b1 = m_mat[1], b2 = m_mat[2], b3 = m_mat[3];
    m_mat[0] = b0 * m00 + b1 * m10 + b2 * m20 + b3 * m30;
    m_mat[1] = b0 * m01 + b1 * m11 + b2 * m21 + b3 * m31;
    m_mat[2] = b0 * m02 + b1 * m12 + b2 * m22 + b3 * m32;
    m_mat[3] = b0 * m03 + b1 * m13 + b2 * m23 + b3 * m33;

    b0 = m_mat[4]; b1 = m_mat[5]; b2 = m_mat[6]; b3 = m_mat[7];
    m_mat[4] = b0 * m00 + b1 * m10 + b2 * m20 + b3 * m30;
    m_mat[5] = b0 * m01 + b1 * m11 + b2 * m21 + b3 * m31;
    m_mat[6] = b0 * m02 + b1 * m12 + b2 * m22 + b3 * m32;
    m_mat[7] = b0 * m03 + b1 * m13 + b2 * m23 + b3 * m33;

    b0 = m_mat[8]; b1 = m_mat[9]; b2 = m_mat[10]; b3 = m_mat[11];
    m_mat[8] = b0 * m00 + b1 * m10 + b2 * m20 + b3 * m30;
    m_mat[9] = b0 * m01 + b1 * m11 + b2 * m21 + b3 * m31;
    m_mat[10] = b0 * m02 + b1 * m12 + b2 * m22 + b3 * m32;
    m_mat[11] = b0 * m03 + b1 * m13 + b2 * m23 + b3 * m33;

    b0 = m_mat[12]; b1 = m_mat[13]; b2 = m_mat[14]; b3 = m_mat[15];
    m_mat[12] = b0 * m00 + b1 * m10 + b2 * m20 + b3 * m30;
    m_mat[13] = b0 * m01 + b1 * m11 + b2 * m21 + b3 * m31;
    m_mat[14] = b0 * m02 + b1 * m12 + b2 * m22 + b3 * m32;
    m_mat[15] = b0 * m03 + b1 * m13 + b2 * m23 + b3 * m33;
    return *this;
}
matrix4& matrix4::operator*=(const matrix4& other) {
    return mul(other);
}

//------------------------------------------------------------------------------
/// @brief      Rotate this matrix
/// http://www.euclideanspace.com/maths/geometry/rotations/conversions/angleToMatrix/
///
/// @param[in]  rads  The angle to rotate by (in radians)
/// @param[in]  axis  The axis to rotate around
///
/// @return     { description_of_the_return_value }
///
matrix4& matrix4::rotate(scalar rads, vector3 axis) {
    auto &x = axis.x(), &y = axis.y(), &z = axis.z(), len = axis.len();

    if (nearly_equal(len, 0)) {
        return *this;
    }
    axis.normalize();

    auto c = std::cos(rads);
    auto s = std::sin(rads);
    auto t = 1 - c;

    auto a00 = m_mat[0], a01 = m_mat[1], a02 = m_mat[2], a03 = m_mat[3],
         a10 = m_mat[4], a11 = m_mat[5], a12 = m_mat[6], a13 = m_mat[7],
         a20 = m_mat[8], a21 = m_mat[9], a22 = m_mat[10], a23 = m_mat[11];

    // Construct the elements of the rotation matrix
    auto b00 = x * x * t + c,
         b01 = y * x * t + z * s,
         b02 = z * x * t - y * s,
         b10 = x * y * t - z * s,
         b11 = y * y * t + c,
         b12 = z * y * t + x * s,
         b20 = x * z * t + y * s,
         b21 = y * z * t - x * s,
         b22 = z * z * t + c;

    // Perform rotation-specific matrix multiplication
    m_mat[0] = a00 * b00 + a10 * b01 + a20 * b02;
    m_mat[1] = a01 * b00 + a11 * b01 + a21 * b02;
    m_mat[2] = a02 * b00 + a12 * b01 + a22 * b02;
    m_mat[3] = a03 * b00 + a13 * b01 + a23 * b02;
    m_mat[4] = a00 * b10 + a10 * b11 + a20 * b12;
    m_mat[5] = a01 * b10 + a11 * b11 + a21 * b12;
    m_mat[6] = a02 * b10 + a12 * b11 + a22 * b12;
    m_mat[7] = a03 * b10 + a13 * b11 + a23 * b12;
    m_mat[8] = a00 * b20 + a10 * b21 + a20 * b22;
    m_mat[9] = a01 * b20 + a11 * b21 + a21 * b22;
    m_mat[10] = a02 * b20 + a12 * b21 + a22 * b22;
    m_mat[11] = a03 * b20 + a13 * b21 + a23 * b22;
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Invert this matrix
///
/// @return     { description_of_the_return_value }
///
matrix4& matrix4::invert() {
    auto a00 = m_mat[0], a01 = m_mat[1], a02 = m_mat[2], a03 = m_mat[3],
         a10 = m_mat[4], a11 = m_mat[5], a12 = m_mat[6], a13 = m_mat[7],
         a20 = m_mat[8], a21 = m_mat[9], a22 = m_mat[10], a23 = m_mat[11],
         a30 = m_mat[12], a31 = m_mat[13], a32 = m_mat[14], a33 = m_mat[15];

    auto b00 = a00 * a11 - a01 * a10,
         b01 = a00 * a12 - a02 * a10,
         b02 = a00 * a13 - a03 * a10,
         b03 = a01 * a12 - a02 * a11,
         b04 = a01 * a13 - a03 * a11,
         b05 = a02 * a13 - a03 * a12,
         b06 = a20 * a31 - a21 * a30,
         b07 = a20 * a32 - a22 * a30,
         b08 = a20 * a33 - a23 * a30,
         b09 = a21 * a32 - a22 * a31,
         b10 = a21 * a33 - a23 * a31,
         b11 = a22 * a33 - a23 * a32;

    // Calculate the determinant
    auto det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
    if (nearly_equal(det, 0)) {
        return *this;
    }
    det = static_cast<scalar>(1.0) / det;

    m_mat[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
    m_mat[1] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
    m_mat[2] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
    m_mat[3] = (a22 * b04 - a21 * b05 - a23 * b03) * det;
    m_mat[4] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
    m_mat[5] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
    m_mat[6] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
    m_mat[7] = (a20 * b05 - a22 * b02 + a23 * b01) * det;
    m_mat[8] = (a10 * b10 - a11 * b08 + a13 * b06) * det;
    m_mat[9] = (a01 * b08 - a00 * b10 - a03 * b06) * det;
    m_mat[10] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
    m_mat[11] = (a21 * b02 - a20 * b04 - a23 * b00) * det;
    m_mat[12] = (a11 * b07 - a10 * b09 - a12 * b06) * det;
    m_mat[13] = (a00 * b09 - a01 * b07 + a02 * b06) * det;
    m_mat[14] = (a31 * b01 - a30 * b03 - a32 * b00) * det;
    m_mat[15] = (a20 * b03 - a21 * b01 + a22 * b00) * det;
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Transpose this matrix
///
/// @return     { description_of_the_return_value }
///
matrix4& matrix4::transpose() {
    auto a01 = m_mat[1], a02 = m_mat[2], a03 = m_mat[3],
         a12 = m_mat[6], a13 = m_mat[7],
         a23 = m_mat[11];

    m_mat[1] = m_mat[4];
    m_mat[2] = m_mat[8];
    m_mat[3] = m_mat[12];
    m_mat[4] = a01;
    m_mat[6] = m_mat[9];
    m_mat[7] = m_mat[13];
    m_mat[8] = a02;
    m_mat[9] = a12;
    m_mat[11] = m_mat[14];
    m_mat[12] = a03;
    m_mat[13] = a13;
    m_mat[14] = a23;
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Set this matrix to "look at" the target from the "eye" position
///
/// @param[in]  eye     The position to look from
/// @param[in]  target  The target to look at
/// @param[in]  up      The direction of up from eye
///
/// @return     { description_of_the_return_value }
///
matrix4& matrix4::look_at(const vector3& eye, const vector3& target, const vector3& up) {
    auto zaxis = target.clone().sub(eye).normalize(),
         xaxis = up.clone().cross(zaxis).normalize(),
         yaxis = zaxis.clone().cross(xaxis).normalize();

    auto x = -xaxis.dot(eye),
         y = -yaxis.dot(eye),
         z = -zaxis.dot(eye);

    m_mat[0] = xaxis.x();
    m_mat[1] = yaxis.x();
    m_mat[2] = zaxis.x();
    m_mat[3] = 0;

    m_mat[4] = xaxis.y();
    m_mat[5] = yaxis.y();
    m_mat[6] = zaxis.y();
    m_mat[7] = 0;

    m_mat[8] = xaxis.z();
    m_mat[9] = yaxis.z();
    m_mat[10] = zaxis.z();
    m_mat[11] = 0;

    m_mat[12] = x;
    m_mat[13] = y;
    m_mat[14] = z;
    m_mat[15] = 1;
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Set this matrix as a specified perspective
/// https://developer.mozilla.org/en-US/docs/Web/API/WebGL_API/WebGL_model_view_projection
///
/// @param[in]  fovy    The filed of view (based on y-axis)
/// @param[in]  aspect  The aspect ratio
/// @param[in]  near    The distance to the near plane
/// @param[in]  far     The distance to the far plane
///
/// @return     { description_of_the_return_value }
///
matrix4& matrix4::perspective(scalar fovy, scalar aspect, scalar near, scalar far) {
    auto f = 1 / std::tan(fovy / 2),
         depth_inv = 1 / (near - far);

    m_mat[0] = f / aspect;
    m_mat[1] = 0;
    m_mat[2] = 0;
    m_mat[3] = 0;

    m_mat[4] = 0;
    m_mat[5] = f;
    m_mat[6] = 0;
    m_mat[7] = 0;

    m_mat[8] = 0;
    m_mat[9] = 0;
    m_mat[10] = (near + far) * depth_inv;
    m_mat[11] = -1;

    m_mat[12] = 0;
    m_mat[13] = 0;
    m_mat[14] = near * far * depth_inv * 2;
    m_mat[15] = 0;
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Set the values of a 3x3 matrix to the normal of this matrix
///
/// @param      out   The output 3x3 matrix
///
void matrix4::set_as_normal(scalar out[9]) const {
    auto &a00 = m_mat[0], &a01 = m_mat[1], &a02 = m_mat[2], &a03 = m_mat[3],
         &a10 = m_mat[4], &a11 = m_mat[5], &a12 = m_mat[6], &a13 = m_mat[7],
         &a20 = m_mat[8], &a21 = m_mat[9], &a22 = m_mat[10], &a23 = m_mat[11],
         &a30 = m_mat[12], &a31 = m_mat[13], &a32 = m_mat[14], &a33 = m_mat[15];

    auto b00 = a00 * a11 - a01 * a10,
         b01 = a00 * a12 - a02 * a10,
         b02 = a00 * a13 - a03 * a10,
         b03 = a01 * a12 - a02 * a11,
         b04 = a01 * a13 - a03 * a11,
         b05 = a02 * a13 - a03 * a12,
         b06 = a20 * a31 - a21 * a30,
         b07 = a20 * a32 - a22 * a30,
         b08 = a20 * a33 - a23 * a30,
         b09 = a21 * a32 - a22 * a31,
         b10 = a21 * a33 - a23 * a31,
         b11 = a22 * a33 - a23 * a32;

    // Calculate the determinant
    auto det = b00 * b11 - b01 * b10 + b02 * b09 + b03 * b08 - b04 * b07 + b05 * b06;
    if (nearly_equal(det, 0)) {
        return;
    }
    det = static_cast<scalar>(1.0) / det;

    out[0] = (a11 * b11 - a12 * b10 + a13 * b09) * det;
    out[1] = (a12 * b08 - a10 * b11 - a13 * b07) * det;
    out[2] = (a10 * b10 - a11 * b08 + a13 * b06) * det;

    out[3] = (a02 * b10 - a01 * b11 - a03 * b09) * det;
    out[4] = (a00 * b11 - a02 * b08 + a03 * b07) * det;
    out[5] = (a01 * b08 - a00 * b10 - a03 * b06) * det;

    out[6] = (a31 * b05 - a32 * b04 + a33 * b03) * det;
    out[7] = (a32 * b02 - a30 * b05 - a33 * b01) * det;
    out[8] = (a30 * b04 - a31 * b02 + a33 * b00) * det;
}

// Insertion operator for the matrix4 class
std::ostream& operator<<(std::ostream& out, const matrix4& v) {
    out << "[ "
        << ScalarFmt() << v.m_mat[0] << "  "
        << ScalarFmt() << v.m_mat[1] << "  "
        << ScalarFmt() << v.m_mat[2] << "  "
        << ScalarFmt() << v.m_mat[3] << "\n  "

        << ScalarFmt() << v.m_mat[4] << "  "
        << ScalarFmt() << v.m_mat[5] << "  "
        << ScalarFmt() << v.m_mat[6] << "  "
        << ScalarFmt() << v.m_mat[7] << "\n  "

        << ScalarFmt() << v.m_mat[8] << "  "
        << ScalarFmt() << v.m_mat[9] << "  "
        << ScalarFmt() << v.m_mat[10] << "  "
        << ScalarFmt() << v.m_mat[11] << "\n  "

        << ScalarFmt() << v.m_mat[12] << "  "
        << ScalarFmt() << v.m_mat[13] << "  "
        << ScalarFmt() << v.m_mat[14] << "  "
        << ScalarFmt() << v.m_mat[15] << " ]";
    return out;
}

// (Approximately) Compare two vectors for equality
bool operator==(const matrix4& lhs, const matrix4& rhs) {
    return nearly_equal(lhs.m_mat[0], rhs.m_mat[0])
        && nearly_equal(lhs.m_mat[1], rhs.m_mat[1])
        && nearly_equal(lhs.m_mat[2], rhs.m_mat[2])
        && nearly_equal(lhs.m_mat[3], rhs.m_mat[3])
        && nearly_equal(lhs.m_mat[4], rhs.m_mat[4])
        && nearly_equal(lhs.m_mat[5], rhs.m_mat[5])
        && nearly_equal(lhs.m_mat[6], rhs.m_mat[6])
        && nearly_equal(lhs.m_mat[7], rhs.m_mat[7])
        && nearly_equal(lhs.m_mat[8], rhs.m_mat[8])
        && nearly_equal(lhs.m_mat[9], rhs.m_mat[9])
        && nearly_equal(lhs.m_mat[10], rhs.m_mat[10])
        && nearly_equal(lhs.m_mat[11], rhs.m_mat[11])
        && nearly_equal(lhs.m_mat[12], rhs.m_mat[12])
        && nearly_equal(lhs.m_mat[13], rhs.m_mat[13])
        && nearly_equal(lhs.m_mat[14], rhs.m_mat[14])
        && nearly_equal(lhs.m_mat[15], rhs.m_mat[15]);

}
bool operator!=(const matrix4& lhs, const matrix4& rhs) { return !operator==(lhs,rhs); }

// Perform typical algebraic operations on vectors
matrix4 operator+(matrix4 lhs, const matrix4& rhs) { return lhs += rhs; }
matrix4 operator-(matrix4 lhs, const matrix4& rhs) { return lhs -= rhs; }
matrix4 operator*(matrix4 lhs, const matrix4& rhs) { return lhs *= rhs; }
matrix4 operator*(matrix4 lhs, scalar rhs) { return lhs *= rhs; }
matrix4 operator*(scalar lhs, matrix4 rhs) { return rhs *= lhs; }
