
#include "linalg.h"

#include <iomanip>
#include <cmath>
#include <limits>


// A temporary kludge to eliminate compiler warnings
bool s_equal(scalar a, scalar b) {
    return a >= b && a <= b;
}

//------------------------------------------------------------------------------
/// @brief      Floating-point comparison from:
/// http://floating-point-gui.de/errors/comparison/
///
/// @param[in]  a        value 1
/// @param[in]  b        value 2
/// @param[in]  epsilon  The comparison tolerance
///
/// @return     true is they are close enough
///
bool nearly_equal(scalar a, scalar b, scalar epsilon)
{
    scalar abs_a = std::abs(a);
    scalar abs_b = std::abs(b);
    scalar diff  = std::abs(a - b);

    // shortcut, handles infinities
    if (s_equal(a, b)) {
        return true;
    }

    // if a or b is zero (or if both are extremely close to it)
    // relative error is less meaningful
    // --> std::numeric_limits<float>::min() <==> Float.MIN_NORMAL
    else if (s_equal(a, 0) || s_equal(b, 0) || diff < std::numeric_limits<scalar>::min()) {
        return diff < (epsilon * std::numeric_limits<scalar>::min());
    }

    // use relative error
    // --> std::numeric_limits<float>::max() <==> Float.MAX_VALUE
    else {
        return diff / std::min((abs_a+abs_b), std::numeric_limits<scalar>::max()) < epsilon;
    }
}

// Insertion operator for the helper formatting class
std::ostream& operator<<(std::ostream& dest, ScalarFmt const& fmt) {
    dest.setf(std::ios_base::fixed, std::ios_base::floatfield);
    dest.precision(fmt.m_precision);
    dest.width(fmt.m_width);
    return dest;
}
