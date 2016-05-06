//------------------------------------------------------------------------------
/// Testing the vector3 class
///


#include <catch.hpp>

#include <linalg/vector3.h>

SCENARIO ( "The vector3 class can be used for linear algebra", "[linalg][vector3]" ) {

    GIVEN ( "Initial values for vectors" ) {
        scalar a = 0;
        scalar b = 1;
        scalar x = 2, y = 3, z = 4;

        WHEN ( "vector3 objects are constructed with the values" ) {
            vector3 v1;
            vector3 v2(b, b, b);
            vector3 v3(x, y, z);

            THEN ( "The values are set correctly" ) {
                CHECK ( v1.m_vec[0] == Approx( a ) );
                CHECK ( v1.m_vec[1] == Approx( a ) );
                CHECK ( v1.m_vec[2] == Approx( a ) );

                CHECK ( v2.m_vec[0] == Approx( b ) );
                CHECK ( v2.m_vec[1] == Approx( b ) );
                CHECK ( v2.m_vec[2] == Approx( b ) );

                CHECK ( v3.m_vec[0] == Approx( x ) );
                CHECK ( v3.m_vec[1] == Approx( y ) );
                CHECK ( v3.m_vec[2] == Approx( z ) );
            }
        }
    }

    GIVEN ( "A vector3" ) {
        scalar a = 1, b = 2, c = 3;
        vector3 v_orig(a, b, c);

        WHEN ( "A new vector3 is created using compiler defined methods" ) {
            vector3 v_copy_cons(v_orig);
            v_copy_cons.m_vec[2] = a;

            vector3 v_copy_assign(1, 1, 1);
            v_copy_assign = v_orig;
            v_copy_assign.m_vec[2] = b;

            auto v_cloned = v_orig.clone();
            v_cloned.x() += c;

            THEN ( "A new but unique vector3 is constructed" ) {
                CHECK ( v_orig.m_vec[0] == Approx( a ) );
                CHECK ( v_orig.m_vec[1] == Approx( b ) );
                CHECK ( v_orig.m_vec[2] == Approx( c ) );

                CHECK ( v_copy_cons.m_vec[0] == Approx( a ) );
                CHECK ( v_copy_cons.m_vec[1] == Approx( b ) );
                CHECK ( v_copy_cons.m_vec[2] == Approx( a ) );

                CHECK ( v_copy_assign.m_vec[0] == Approx( a ) );
                CHECK ( v_copy_assign.m_vec[1] == Approx( b ) );
                CHECK ( v_copy_assign.m_vec[2] == Approx( b ) );

                CHECK ( v_cloned.m_vec[0] == Approx( a+c ) );
                CHECK ( v_cloned.m_vec[1] == Approx( b ) );
                CHECK ( v_cloned.m_vec[2] == Approx( c ) );
            }
        }
    }

    GIVEN ( "A vector and two copies of that vector" ) {
        vector3 v1(1, 2, 3.14f);
        vector3 v2(v1);
        vector3 v3(v1);

        WHEN ( "One copy is altered" ) {
            v3.m_vec[1] += 1;

            THEN ( "The checks for equality and inequality function correctly" ) {
                CHECK ( v1 == v2 );
                CHECK ( v1 != v3 );
            }

        }
    }

    GIVEN ( "A vector3 with non-zero values" ) {
        vector3 v(10, 11, 12);

        WHEN ( "The 'zero' method is called" ) {
            v.zero();

            THEN ( "The vector3 values are all set to zero" ) {
                CHECK ( v == vector3() );
            }
        }
    }

    GIVEN ( "A vector3 with any arbitrary values" ) {
        vector3 v(10, 11, 12);

        WHEN ( "The 'set' method is called" ) {
            scalar x = -1, y = -11, z = -111;
            v.set(x, y, z);

            THEN ( "The vector3 values are all set to the given values" ) {
                CHECK ( v == vector3(x, y, z) );
            }
        }
    }

    GIVEN ( "Two vector3 with any arbitrary values" ) {
        scalar x1 = 10, y1 = 20, z1 = 30,
               x2 = 99, y2 = 98, z2 = 97;
        vector3 v1(x1, y1, z1);
        vector3 v2(x2, y2, z2);

        vector3 v3(v1);
        vector3 v4(v2);

        WHEN ( "The 'add' method (and operator) is called on the first vector" ) {
            v1.add(v2);
            v3 += v4;

            THEN ( "The first vector is updated and the second is not changed" ) {
                CHECK ( v1 == vector3(x1+x2, y1+y2, z1+z2) );
                CHECK ( v2 == vector3(x2, y2, z2) );
                CHECK ( v3 == v1 );
            }
        }
    }

    GIVEN ( "Two vector3 with any arbitrary values" ) {
        scalar x1 = 10, y1 = 20, z1 = 30,
               x2 = 99, y2 = 98, z2 = 97;
        vector3 v1(x1, y1, z1);
        vector3 v2(x2, y2, z2);

        vector3 v3(v1);
        vector3 v4(v2);

        WHEN ( "The 'sub' method (and operator) is called on the first vector" ) {
            v1.sub(v2);
            v3 -= v4;

            THEN ( "The first vector is updated and the second is not changed" ) {
                CHECK ( v1 == vector3(x1-x2, y1-y2, z1-z2) );
                CHECK ( v2 == vector3(x2, y2, z2) );
                CHECK ( v3 == v1 );
            }
        }
    }

    GIVEN ( "A vector3 with any arbitrary values" ) {
        scalar x = -1.222f, y = -11.222f, z = -111.222f;
        vector3 v1(x, y, z);
        vector3 v2(v1);

        WHEN ( "The 'scale' method (and operator) is called" ) {
            scalar s = 34.4f;
            v1.scale(s);
            v2 *= s;

            THEN ( "The vector3 values are all set to the appropriate values" ) {
                CHECK ( v1 == vector3(x*s, y*s, z*s) );
                CHECK ( v2 == v1 );
            }
        }
    }

    GIVEN ( "A vector3 with any arbitrary values" ) {
        scalar x = -1.222f, y = -11.222f, z = -111.222f;
        vector3 v(x, y, z);

        WHEN ( "The 'len' and 'len2' methods are called" ) {
            auto len = v.len();
            auto len2 = v.len2();

            auto len2_correct = x*x + y*y + z*z;
            auto len_correct = std::sqrt(len2_correct);

            THEN ( "Length and squared length values are returned" ) {
                CHECK ( len  == Approx( len_correct ) );
                CHECK ( len2 == Approx( len2_correct ) );

            }
        }
    }

    GIVEN ( "A vector3 with any arbitrary values" ) {
        scalar x = -1.222f, y = -11.222f, z = -111.222f;
        vector3 v(x, y, z);

        WHEN ( "The 'normalize' method is called" ) {
            vector3 v_scaled(v);
            v.normalize();

            v_scaled.scale(1/v_scaled.len());

            THEN ( "The vector3 is normalized" ) {
                CHECK ( v == v_scaled );
            }
        }
    }

    GIVEN ( "Two vector3 with any arbitrary values" ) {
        scalar x1 = 10, y1 = 20, z1 = 30,
               x2 = 99, y2 = 98, z2 = 97;
        vector3 v1(x1, y1, z1);
        vector3 v2(x2, y2, z2);

        WHEN ( "The 'dot' method is called on the first vector" ) {
            auto dot_value = v1.dot(v2);
            auto dot_correct = x1*x2 + y1*y2 + z1*z2;

            THEN ( "The dot product of the two vectors is returned" ) {
                CHECK ( dot_value == Approx( dot_correct ) );
            }
        }
    }

    GIVEN ( "Two vector3 with any arbitrary values" ) {
        scalar x1 = 10, y1 = 20, z1 = 30,
               x2 = 99, y2 = 98, z2 = 97;
        vector3 v1(x1, y1, z1);
        vector3 v2(x2, y2, z2);

        WHEN ( "The 'cross' method is called on the first vector" ) {
            // From Wolfram
            scalar x_correct = -1000, y_correct = 2000, z_correct = -1000;
            v1.cross(v2);

            THEN ( "The dot product of the two vectors is returned" ) {
                CHECK ( v1 == vector3(x_correct, y_correct, z_correct) );
            }
        }
    }

    GIVEN ( "Two vector3 with any arbitrary values" ) {
        scalar x1 = 1, y1 = 2, z1 = 3,
               x2 = 11, y2 = 12, z2 = 13;
        vector3 v1(x1, y1, z1);
        vector3 v2(x2, y2, z2);

        WHEN ( "The 'lerp' method is called on the first vector" ) {
            scalar alpha_val = 0.2f;
            v1.lerp(v2, alpha_val);

            auto x_correct = x1 * (1 - alpha_val) + x2 * alpha_val;
            auto y_correct = y1 * (1 - alpha_val) + y2 * alpha_val;
            auto z_correct = z1 * (1 - alpha_val) + z2 * alpha_val;

            THEN ( "The correct lerp product of the two vectors is returned" ) {
                CHECK ( v1 == vector3(x_correct, y_correct, z_correct) );
            }
        }
    }

    GIVEN ( "Two vector3 with any arbitrary values" ) {
        scalar x1 = 1, y1 = 2, z1 = 3,
               x2 = 11, y2 = 12, z2 = 13;
        vector3 v1(x1, y1, z1);
        vector3 v2(x2, y2, z2);

        WHEN ( "The non-mutating operators are called (+, -, *)" ) {
            auto v3 = v1 + v2;
            auto v4 = v1 - v2;

            scalar s = 0.2f;
            auto v5 = v1 * s;
            auto v6 = s * v1;

            THEN ( "New vector3 objects are created with the correct data" ) {
                CHECK ( v3 == vector3(x1+x2, y1+y2, z1+z2) );
                CHECK ( v4 == vector3(x1-x2, y1-y2, z1-z2) );
                CHECK ( v5 == vector3(x1*s, y1*s, z1*s) );
                CHECK ( v6 == v5 );
            }
        }
    }

}
