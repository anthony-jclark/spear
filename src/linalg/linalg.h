
#ifndef _LINALG_H_
#define _LINALG_H_

#include <iosfwd>

// An alias for easily testing float vs double
using scalar = float;


//------------------------------------------------------------------------------
/// @brief      A formating class for scalar values. I will eventually move
/// this to a utility file.
///
class ScalarFmt
{
    int m_width;
    int m_precision;

public:
    ScalarFmt(int width=8, int precision=2)
        : m_width(width)
        , m_precision(precision)
    {}
    friend std::ostream& operator<<(std::ostream& dest, ScalarFmt const& format);
};


// A temporary kludge to eliminate compiler warnings
bool s_equal(scalar a, scalar b);

// Floating-point comparison from:
bool nearly_equal(scalar a, scalar b, scalar epsilon=0.00001f);

#endif
