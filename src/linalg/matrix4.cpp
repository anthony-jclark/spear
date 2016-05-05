
#include "matrix4.h"

#include <iostream>
#include <cmath>


//------------------------------------------------------------------------------
/// @brief      Set to the identiy matrix
///
void matrix4::eye() {
    m_values = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1 };
}


//------------------------------------------------------------------------------
/// @brief      Add another matrix4 to this vector
///
/// @param[in]  other  The other matrix
///
/// @return     return the updated matrix
///
matrix4& matrix4::add(const matrix4& other) {
    m_values[0] += other.m_values[0];
    m_values[1] += other.m_values[1];
    m_values[2] += other.m_values[2];
    m_values[3] += other.m_values[3];
    m_values[4] += other.m_values[4];
    m_values[5] += other.m_values[5];
    m_values[6] += other.m_values[6];
    m_values[7] += other.m_values[7];
    m_values[8] += other.m_values[8];
    m_values[9] += other.m_values[9];
    m_values[10] += other.m_values[10];
    m_values[11] += other.m_values[11];
    m_values[12] += other.m_values[12];
    m_values[13] += other.m_values[13];
    m_values[14] += other.m_values[14];
    m_values[15] += other.m_values[15];
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
    m_values[0] -= other.m_values[0];
    m_values[1] -= other.m_values[1];
    m_values[2] -= other.m_values[2];
    m_values[3] -= other.m_values[3];
    m_values[4] -= other.m_values[4];
    m_values[5] -= other.m_values[5];
    m_values[6] -= other.m_values[6];
    m_values[7] -= other.m_values[7];
    m_values[8] -= other.m_values[8];
    m_values[9] -= other.m_values[9];
    m_values[10] -= other.m_values[10];
    m_values[11] -= other.m_values[11];
    m_values[12] -= other.m_values[12];
    m_values[13] -= other.m_values[13];
    m_values[14] -= other.m_values[14];
    m_values[15] -= other.m_values[15];
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
    m_values[0] *= s;
    m_values[1] *= s;
    m_values[2] *= s;
    m_values[3] *= s;
    m_values[4] *= s;
    m_values[5] *= s;
    m_values[6] *= s;
    m_values[7] *= s;
    m_values[8] *= s;
    m_values[9] *= s;
    m_values[10] *= s;
    m_values[11] *= s;
    m_values[12] *= s;
    m_values[13] *= s;
    m_values[14] *= s;
    m_values[15] *= s;
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
    auto m00 = m.d[0], m01 = m.d[1], m02 = m.d[2], m03 = m.d[3],
    m10 = m.d[4], m11 = m.d[5], m12 = m.d[6], m13 = m.d[7],
    m20 = m.d[8], m21 = m.d[9], m22 = m.d[10], m23 = m.d[11],
    m30 = m.d[12], m31 = m.d[13], m32 = m.d[14], m33 = m.d[15];

    auto b0  = this.d[0], b1 = this.d[1], b2 = this.d[2], b3 = this.d[3];

    this.d[0] = b0 * m00 + b1 * m10 + b2 * m20 + b3 * m30;
    this.d[1] = b0 * m01 + b1 * m11 + b2 * m21 + b3 * m31;
    this.d[2] = b0 * m02 + b1 * m12 + b2 * m22 + b3 * m32;
    this.d[3] = b0 * m03 + b1 * m13 + b2 * m23 + b3 * m33;

    b0 = this.d[4]; b1 = this.d[5]; b2 = this.d[6]; b3 = this.d[7];
    this.d[4] = b0 * m00 + b1 * m10 + b2 * m20 + b3 * m30;
    this.d[5] = b0 * m01 + b1 * m11 + b2 * m21 + b3 * m31;
    this.d[6] = b0 * m02 + b1 * m12 + b2 * m22 + b3 * m32;
    this.d[7] = b0 * m03 + b1 * m13 + b2 * m23 + b3 * m33;

    b0 = this.d[8]; b1 = this.d[9]; b2 = this.d[10]; b3 = this.d[11];
    this.d[8] = b0 * m00 + b1 * m10 + b2 * m20 + b3 * m30;
    this.d[9] = b0 * m01 + b1 * m11 + b2 * m21 + b3 * m31;
    this.d[10] = b0 * m02 + b1 * m12 + b2 * m22 + b3 * m32;
    this.d[11] = b0 * m03 + b1 * m13 + b2 * m23 + b3 * m33;

    b0 = this.d[12]; b1 = this.d[13]; b2 = this.d[14]; b3 = this.d[15];
    this.d[12] = b0 * m00 + b1 * m10 + b2 * m20 + b3 * m30;
    this.d[13] = b0 * m01 + b1 * m11 + b2 * m21 + b3 * m31;
    this.d[14] = b0 * m02 + b1 * m12 + b2 * m22 + b3 * m32;
    this.d[15] = b0 * m03 + b1 * m13 + b2 * m23 + b3 * m33;
    return this;
}
matrix4& matrix4::operator*=(const matrix4& other) {
    return mul(other);
}

    // Rotate this matrix
matrix4& matrix4::rotate(scalar rads, const vector3& axis) {

}

    // Invert this matrix
matrix4& matrix4::invert() {

}

    // Transpose this matrix
matrix4& matrix4::transpose() {

}

    // Set the values of a 3x3 matrix to the normal of this matrix
void matrix4::set_as_normal(scalar out[9]) {

}

    // Set this matrix to "look at" the target from the "eye" position
matrix4& matrix4::look_at(const vector3& eye, const vector3& target, const vector3& up) {

}

    // Set this matrix as a specified perspective
matrix4& matrix4::perspective(scalar fovy, scalar aspect, scalar near, scalar far) {

}

};

// Perform typical algebraic operations on vectors
std::ostream& operator<<(std::ostream& out, const matrix4& v);
inline bool operator==(const matrix4& lhs, const matrix4& rhs);
inline bool operator!=(const matrix4& lhs, const matrix4& rhs);
inline matrix4 operator+(matrix4 lhs, const matrix4& rhs);
inline matrix4 operator-(matrix4 lhs, const matrix4& rhs);
inline matrix4 operator*(const matrix4& lhs, scalar rhs);
inline matrix4 operator*(scalar lhs, const matrix4& rhs);
inline matrix4 operator*(const matrix4& lhs, const matrix4& rhs);
inline matrix4 operator*(const matrix4& lhs, const matrix4& rhs);
