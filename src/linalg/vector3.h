
#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "linalg.h"

#include <iosfwd>
#include <array>

using vec_array = std::array<scalar, 3>;

//------------------------------------------------------------------------------
/// @brief      This class defines a three dimentional vector that can be
/// used to perform linear algebra operations.
///
class vector3
{
public:
    vec_array m_vec;

public: // Constructors ---------------------------------------------

    vector3()
        : m_vec{{0, 0, 0}}
    {}

    vector3(const vec_array& vec)
        : m_vec(vec)
    {}

    vector3(scalar x, scalar y, scalar z)
        : m_vec{{x, y, z}}
    {}

    vector3 clone() const {
        return {*this};
    }

public: // Accessor methods -----------------------------------------

    scalar& x() { return m_vec[0]; };
    scalar& y() { return m_vec[1]; };
    scalar& z() { return m_vec[2]; };

    scalar x() const { return m_vec[0]; };
    scalar y() const { return m_vec[1]; };
    scalar z() const { return m_vec[2]; };

public: // Mutating interface methods -------------------------------

    // Set all values to zero
    vector3& zero();

    // Set all values to the given values
    vector3& set(scalar x, scalar y, scalar z);

    // Add another vector3 to this vector
    vector3& add(const vector3& other);
    vector3& operator+=(const vector3& other);

    // Subtract another vector3 from this vector
    vector3& sub(const vector3& other);
    vector3& operator-=(const vector3& other);

    // Scale this vector
    vector3& scale(scalar s);
    vector3& operator*=(scalar s);

    // Normalize this vector
    vector3& normalize();

    // Cross product this vector with another vector
    vector3& cross(const vector3& other);

    // Linearly interpolate between this and another vector
    vector3& lerp(const vector3& other, scalar alpha=0.5);

public: // Information interface mthods -----------------------------

    // Return the magnitude/length of this vector
    scalar len() const;

    // Return the squared magnitude/length of this vector
    scalar len2() const;

    // Return the dot product of this vector with another vector
    scalar dot(const vector3& other) const;

};

// Perform typical algebraic operations on vectors
std::ostream& operator<<(std::ostream& out, const vector3& v);
bool operator==(const vector3& lhs, const vector3& rhs);
bool operator!=(const vector3& lhs, const vector3& rhs);
vector3 operator+(vector3 lhs, const vector3& rhs);
vector3 operator-(vector3 lhs, const vector3& rhs);
vector3 operator*(vector3 lhs, scalar rhs);
vector3 operator*(scalar lhs, vector3 rhs);

#endif
