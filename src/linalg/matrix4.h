
#ifndef _MATRIX4_H_
#define _MATRIX4_H_

#include "linalg.h"
#include "vector3.h"

class matrix4
{
public:
    // The values are stored in an array
    scalar m_mat[16];

public: // Constructors ---------------------------------------------

    matrix4()
        : m_mat {
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1 }
    {}

public: // Interface methods ----------------------------------------

    // Set to the identiy matrix
    void eye();

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
    matrix4& rotate(scalar rads, const vector3& axis);

    // Invert this matrix
    matrix4& invert();

    // Transpose this matrix
    matrix4& transpose();

    // Set the values of a 3x3 matrix to the normal of this matrix
    void set_as_normal(scalar out[9]);

    // Set this matrix to "look at" the target from the "eye" position
    matrix4& look_at(const vector3& eye, const vector3& target, const vector3& up);

    // Set this matrix as a specified perspective
    matrix& perspective(scalar fovy, scalar aspect, scalar near, scalar far);

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


#endif
