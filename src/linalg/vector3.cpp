
#include "vector3.h"

#include <iostream>
#include <cmath>


//------------------------------------------------------------------------------
/// @brief      Set all values to zero
///
/// @return     return the updated vector3
///
vector3& vector3::zero() {
    m_vec = {{0, 0, 0}};
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Set all values to the given values
///
/// @param[in]  x     first coordinate value
/// @param[in]  y     second coordinate value
/// @param[in]  z     third coordinate value
///
/// @return     return the updated vector
///
vector3& vector3::set(scalar x, scalar y, scalar z) {
    m_vec = {{x, y, z}};
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Add another vector3 to this vector
///
/// @param[in]  other  The other vector3 to add
///
/// @return     return the updated vector
///
vector3& vector3::add(const vector3& other) {
    m_vec[0] += other.m_vec[0];
    m_vec[1] += other.m_vec[1];
    m_vec[2] += other.m_vec[2];
    return *this;
}
vector3& vector3::operator+=(const vector3& other) {
    return add(other);
}

//------------------------------------------------------------------------------
/// @brief      Subtract another vector3 from this vector
///
/// @param[in]  other  The other vector4 to subtract from this
///
/// @return     return the updated vector
///
vector3& vector3::sub(const vector3& other) {
    m_vec[0] -= other.m_vec[0];
    m_vec[1] -= other.m_vec[1];
    m_vec[2] -= other.m_vec[2];
    return *this;
}
vector3& vector3::operator-=(const vector3& other) {
    return sub(other);
}

//------------------------------------------------------------------------------
/// @brief      Scale this vector
///
/// @param[in]  s     the scaling value
///
/// @return     return the updated vector
///
vector3& vector3::scale(scalar s) {
    m_vec[0] *= s;
    m_vec[1] *= s;
    m_vec[2] *= s;
    return *this;
}
vector3& vector3::operator*=(scalar s) {
    return scale(s);
}

//------------------------------------------------------------------------------
/// @brief      Normalize this vector
///
/// @return     the updated vector
///
vector3& vector3::normalize() {
    auto len_squared = len2();
    if (len_squared > 0) {
        scale(1 / std::sqrt(len_squared));
    }
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Cross product this vector with another vector
///
/// @param[in]  other  The other vector3
///
/// @return     the updated vector
///
vector3& vector3::cross(const vector3& other) {
    auto ax = m_vec[0], ay = m_vec[1], az = m_vec[2],
         bx = other.m_vec[0], by = other.m_vec[1], bz = other.m_vec[2];
    m_vec[0] = ay * bz - az * by;
    m_vec[1] = az * bx - ax * bz;
    m_vec[2] = ax * by - ay * bx;
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Linearly interpolate between this and another vector
///
/// @param[in]  other  The other vector3
/// @param[in]  alpha  The interpolation ratio [0, 1]
///
/// @return     the updated vector3
///
vector3& vector3::lerp(const vector3& other, scalar alpha) {
    m_vec[0] += (other.m_vec[0] - m_vec[0]) * alpha;
    m_vec[1] += (other.m_vec[1] - m_vec[1]) * alpha;
    m_vec[2] += (other.m_vec[2] - m_vec[2]) * alpha;
    return *this;
}

//------------------------------------------------------------------------------
/// @brief      Return the magnitude/length of this vector
///
/// @return     the length of this vector
///
scalar vector3::len() const {
    return std::sqrt(len2());
}

//------------------------------------------------------------------------------
/// @brief      Return the squared magnitude/length of this vector
///
/// @return     the squared length of this vector
///
scalar vector3::len2() const {
    return dot(*this);
}

//------------------------------------------------------------------------------
/// @brief      Return the dot product of this vector with another vector
///
/// @param[in]  other  The other vector3
///
/// @return     the dot product between two vectors
///
scalar vector3::dot(const vector3& other) const {
    return m_vec[0] * other.m_vec[0]
         + m_vec[1] * other.m_vec[1]
         + m_vec[2] * other.m_vec[2];
}

// Insertion operator for the vector3 class
std::ostream& operator<<(std::ostream& out, const vector3& v) {
    out << "[ "
        << ScalarFmt() << v.m_vec[0] << "  "
        << ScalarFmt() << v.m_vec[1] << "  "
        << ScalarFmt() << v.m_vec[2] << " ]";
    return out;
}

// (Approximately) Compare two vectors for equality
bool operator==(const vector3& lhs, const vector3& rhs) {
    return nearly_equal(lhs.m_vec[0], rhs.m_vec[0])
        && nearly_equal(lhs.m_vec[1], rhs.m_vec[1])
        && nearly_equal(lhs.m_vec[2], rhs.m_vec[2]);
}
bool operator!=(const vector3& lhs, const vector3& rhs) { return !operator==(lhs,rhs); }

// Perform typical algebraic operations on vectors
vector3 operator+(vector3 lhs, const vector3& rhs) { return lhs += rhs; }
vector3 operator-(vector3 lhs, const vector3& rhs) { return lhs -= rhs; }
vector3 operator*(vector3 lhs, scalar rhs) { return lhs *= rhs; }
vector3 operator*(scalar lhs, vector3 rhs) { return rhs *= lhs; }
