
#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "linalg.h"
#include "vector3.h"

#include <iosfwd>
#include <array>

using mat_array = std::array<scalar, 16>;

//------------------------------------------------------------------------------
/// @brief      This class defines a 4x4 matrix that can be
/// used to perform linear algebra operations.
///
class matrix4
{
public:
    mat_array m_mat;

public: // Constructors ---------------------------------------------

    matrix4()
        : m_mat {{
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1 }}
    {}

    matrix4(const mat_array& mat)
        : m_mat(mat)
    {}

    matrix4 clone() const {
        return {*this};
    }

public: // Interface methods ----------------------------------------

    // Set to the identiy matrix
    matrix4& id();

    // Add another matrix4 to this vector
    matrix4& add(const matrix4& other);
    matrix4& operator+=(const matrix4& other);

    // Subtract another matrix4 from this vector
    matrix4& sub(const matrix4& other);
    matrix4& operator-=(const matrix4& other);

    // Scale this matrix
    matrix4& scale(scalar s);
    matrix4& operator*=(scalar s);

    // Multiply this matrix
    matrix4& mul(const matrix4& other);
    matrix4& operator*=(const matrix4& other);

    // Rotate this matrix
    matrix4& rotate(scalar rads, vector3 axis);

    // Invert this matrix
    matrix4& invert();

    // Transpose this matrix
    matrix4& transpose();

    // Set this matrix to "look at" the target from the "eye" position
    matrix4& look_at(const vector3& eye, const vector3& target, const vector3& up);

    // Set this matrix as a specified perspective
    matrix4& perspective(scalar fovy, scalar aspect, scalar near, scalar far);

public: // Information interface mthods -----------------------------

    // Set the values of a 3x3 matrix to the normal of this matrix
    void set_as_normal(scalar out[9]) const;

};

// Perform typical algebraic operations on vectors
std::ostream& operator<<(std::ostream& out, const matrix4& v);
bool operator==(const matrix4& lhs, const matrix4& rhs);
bool operator!=(const matrix4& lhs, const matrix4& rhs);
matrix4 operator+(matrix4 lhs, const matrix4& rhs);
matrix4 operator-(matrix4 lhs, const matrix4& rhs);
matrix4 operator*(matrix4 lhs, const matrix4& rhs);
matrix4 operator*(matrix4 lhs, scalar rhs);
matrix4 operator*(scalar lhs, matrix4 rhs);


#endif
