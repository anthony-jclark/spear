//------------------------------------------------------------------------------
/// Testing the matrix4 class
///


#include <catch.hpp>

#include <linalg/matrix4.h>

#include <iostream>

SCENARIO ( "The matrix4 class can be used for linear algebra", "[linalg][matrix4]" ) {

    GIVEN ( "A default constructed matrix4" ) {
        matrix4 m;

        WHEN ( "The values are left unchanged" ) {

            THEN ( "The matrix is the identity matrix" ) {
                CHECK ( m.m_mat[0] == Approx( 1 ) );
                CHECK ( m.m_mat[1] == Approx( 0 ) );
                CHECK ( m.m_mat[2] == Approx( 0 ) );
                CHECK ( m.m_mat[3] == Approx( 0 ) );

                CHECK ( m.m_mat[4] == Approx( 0 ) );
                CHECK ( m.m_mat[5] == Approx( 1 ) );
                CHECK ( m.m_mat[6] == Approx( 0 ) );
                CHECK ( m.m_mat[7] == Approx( 0 ) );

                CHECK ( m.m_mat[8] == Approx( 0 ) );
                CHECK ( m.m_mat[9] == Approx( 0 ) );
                CHECK ( m.m_mat[10] == Approx( 1 ) );
                CHECK ( m.m_mat[11] == Approx( 0 ) );

                CHECK ( m.m_mat[12] == Approx( 0 ) );
                CHECK ( m.m_mat[13] == Approx( 0 ) );
                CHECK ( m.m_mat[14] == Approx( 0 ) );
                CHECK ( m.m_mat[15] == Approx( 1 ) );
            }
        }
    }

    GIVEN ( "A matrix4 and two copies of that matrix4" ) {
        matrix4 m1(mat_array({{1,2.7f,3.14f,4,5,6,7,8,9,0,1,2,3,4,5,6}}));
        matrix4 m2(m1);
        matrix4 m3(m1);

        WHEN ( "One copy is altered" ) {
            m3.m_mat[1] += 1;

            THEN ( "The checks for equality and inequality function correctly" ) {
                CHECK ( m1 == m2 );
                CHECK ( m1 != m3 );
            }

        }
    }

    GIVEN ( "A matrix4 with some arbitrary values" ) {
        mat_array vals = {{1,2.7f,3.14f,4,5,6,7,8,9,0,1,2,3,4,5,6}};
        matrix4 m_orig(vals);

        WHEN ( "A new matrix4 is created using compiler defined methods" ) {
            matrix4 m_copy_cons(m_orig);

            matrix4 m_copy_assign;
            m_copy_assign = m_orig;

            auto m_cloned = m_orig.clone();

            THEN ( "A new, identical matrix4 is constructed" ) {
                CHECK ( m_copy_cons == m_orig );
                CHECK ( m_copy_assign == m_orig );
                CHECK ( m_cloned == m_orig );
            }
        }

        AND_WHEN ( "The new matrices are altered" ) {
            matrix4 m_copy_cons(m_orig);
            m_copy_cons.m_mat[10] = -1;

            matrix4 m_copy_assign;
            m_copy_assign = m_orig;
            m_copy_assign.m_mat[10] = -1;

            auto m_cloned = m_orig.clone();
            m_cloned.m_mat[10] += -1;

            matrix4 m_correct(vals);

            THEN ( "The original matrix is unaffected" ) {
                CHECK ( m_orig == m_correct );
                CHECK ( m_copy_cons != m_orig );
                CHECK ( m_copy_assign != m_orig );
                CHECK ( m_cloned != m_orig );
            }
        }
    }

    GIVEN ( "A matrix4 that is not the identity matrix" ) {
        matrix4 m(mat_array({{1,2.7f,3.14f,4,5,6,7,8,9,0,1,2,3,4,5,6}}));

        WHEN ( "The 'id' method is called" ) {
            m.id();

            THEN ( "The matrix4 values are set to identity" ) {
                CHECK ( m == matrix4() );
            }
        }
    }

    GIVEN ( "Two matrix4s with any arbitrary values" ) {
        mat_array vals1 = {{1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6}};
        matrix4 m1(vals1);

        mat_array vals2 = {{1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2}};
        matrix4 m2(vals2);

        matrix4 m3(m1);

        mat_array vals_1plus2;
        for (auto i = 0u; i < 16; ++i) {
            vals_1plus2[i] = vals1[i] + vals2[i];
        }
        matrix4 m_correct(vals_1plus2);

        WHEN ( "The 'add' method (and operator) is called on the first matrix" ) {
            m1.add(m2);
            m3 += m2;

            THEN ( "The first matrix is updated and the second is not changed" ) {
                CHECK ( m1 == m_correct );
                CHECK ( m2 == matrix4(vals2) );
                CHECK ( m3 == m1 );
            }
        }
    }

    GIVEN ( "Two matrix4 with any arbitrary values" ) {
        mat_array vals1 = {{1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6}};
        matrix4 m1(vals1);

        mat_array vals2 = {{1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2}};
        matrix4 m2(vals2);

        matrix4 m3(m1);

        mat_array vals_1minus2;
        for (auto i = 0u; i < 16; ++i) {
            vals_1minus2[i] = vals1[i] - vals2[i];
        }
        matrix4 m_correct(vals_1minus2);

        WHEN ( "The 'sub' method (and operator) is called on the first matrix" ) {
            m1.sub(m2);
            m3 -= m2;

            THEN ( "The first matrix is updated and the second is not changed" ) {
                CHECK ( m1 == m_correct );
                CHECK ( m2 == matrix4(vals2) );
                CHECK ( m3 == m1 );
            }
        }
    }

    GIVEN ( "A matrix4 with any arbitrary values" ) {
        mat_array vals1 = {{1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6}};
        matrix4 m1(vals1);
        matrix4 m2(m1);

        WHEN ( "The 'scale' method (and operator) is called" ) {
            scalar s = 34.4f;
            m1.scale(s);
            m2 *= s;

            matrix4 m_scale(vals1);
            for (auto& v : m_scale.m_mat) {
                v *= s;
            }

            THEN ( "The matrix4 values are all set to the appropriate values" ) {
                CHECK ( m1 == m_scale );
                CHECK ( m2 == m1 );
            }
        }
    }

    GIVEN ( "A two matrices with any arbitrary values" ) {
        mat_array vals1 = {{1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6}};
        matrix4 m1(vals1);

        mat_array vals2 = {{1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2}};
        matrix4 m2(vals2);

        matrix4 m3(m1);

        WHEN ( "The 'mul' method (and operator) is called" ) {
            m1.mul(m2);
            m3 *= m2;

            matrix4 m_mul(mat_array({{17,17,17,17,41,41,41,41,15,15,15,15,29,29,29,29}}));

            THEN ( "The matrix4 values are all set to the appropriate values" ) {
                CHECK ( m1 == m_mul );
                CHECK ( m2 == matrix4(vals2) );
                CHECK ( m3 == m1 );
            }
        }
    }

    GIVEN ( "An invertible matrix4 with any arbitrary values" ) {
        matrix4 m(mat_array({{1,2.7f,3.14f,4,5,6,7,8,9,0,1,2,3,4,5,6}}));

        WHEN ( "The 'invert' method is called" ) {
            m.invert();
            matrix4 mat_inv(mat_array({{
                -1.2556093730879716e-15f, 0.2f, 0.1f, -0.3f,
                2.38095f, 1.58095f, 0.1f, -3.72857f,
                -4.7619f, -0.761905f, -0.5f, 4.35714f,
                2.38095f, -0.519048f, 0.3f, -0.828571f
            }}));

            THEN ( "The matrix4 values are set to the inverse" ) {
                for (auto i = 0u; i < 16; ++i) {
                    CHECK ( m.m_mat[i] == Approx( mat_inv.m_mat[i]) );
                }
            }
        }
    }

    GIVEN ( "A matrix4 with any arbitrary values" ) {
        matrix4 m(mat_array({{1,2.7f,3.14f,4,5,6,7,8,9,0,1,2,3,4,5,6}}));

        WHEN ( "The 'transpose' method is called" ) {
            m.transpose();
            mat_array vals_T = {{1,5,9,3,2.7f,6,0,4,3.14f,7,1,5,4,8,2,6}};

            THEN ( "The matrix4 values are set to the transpose" ) {
                CHECK ( m == matrix4(vals_T) );
            }
        }
    }

    GIVEN ( "A matrix4 with any arbitrary values" ) {
        matrix4 m;

        WHEN ( "The 'look_at' method is called" ) {
            vector3 eye(1, 2, 3);
            vector3 target(-1, -1, -1);
            vector3 up(0, 0.5, 1);
            m.look_at(eye, target, up);

            matrix4 m_translate(mat_array({{
                1,        0,        0,        0,
                0,        1,        0,        0,
                0,        0,        1,        0,
                -eye.x(), -eye.y(), -eye.z(), 1
            }}));

            auto zaxis = target.clone().sub(eye).normalize();
            auto xaxis = up.clone().cross(zaxis).normalize();
            auto yaxis = zaxis.clone().cross(xaxis).normalize();
            matrix4 m_rotation(mat_array({{
                xaxis.x(), yaxis.x(), zaxis.x(), 0,
                xaxis.y(), yaxis.y(), zaxis.y(), 0,
                xaxis.z(), yaxis.z(), zaxis.z(), 0,
                0,         0,         0,         1
            }}));

            auto m_lookat = m_translate * m_rotation;

            THEN ( "The matrix4 values are set to the correct values" ) {
                for (auto i = 0u; i < 16; ++i) {
                    CHECK ( m.m_mat[i] == Approx( m_lookat.m_mat[i]) );
                }
            }
        }
    }

    GIVEN ( "Two matrix4 with any arbitrary values" ) {
        mat_array vals1 = {{1,2,3,4,5,6,7,8,9,0,1,2,3,4,5,6}};
        matrix4 m1(vals1);

        mat_array vals2 = {{1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,2}};
        matrix4 m2(vals2);

        WHEN ( "The non-mutating operators are called (+, -, *)" ) {
            auto m3 = m1 + m2;
            auto m4 = m1 - m2;
            auto m5 = m1 * m2;

            scalar s = 0.2f;
            auto m6 = m1 * s;
            auto m7 = s * m1;

            mat_array vals_1plus2, vals_1minus2, vals_1scale;
            for (auto i = 0u; i < 16; ++i) {
                vals_1plus2[i] = vals1[i] + vals2[i];
                vals_1minus2[i] = vals1[i] - vals2[i];
                vals_1scale[i] = vals1[i] * s;
            }

            // From WolframAlpha
            // {{1,2,3,4}, {5,6,7,8}, {9,0,1,2}, {3,4,5,6}} *
            // {{1,1,1,1}, {1,1,1,1}, {2,2,2,2}, {2,2,2,2}} =
            // {{17,17,17,17}, {41,41,41,41}, {15,15,15,15}, {29,29,29,29}}
            mat_array vals_1mult2 = {{17,17,17,17,41,41,41,41,15,15,15,15,29,29,29,29}};

            THEN ( "New matrix4 objects are created with the correct data" ) {
                CHECK ( m3 == matrix4(vals_1plus2) );
                CHECK ( m4 == matrix4(vals_1minus2) );
                CHECK ( m5 == matrix4(vals_1mult2) );
                CHECK ( m6 == matrix4(vals_1scale) );
                CHECK ( m7 == m6 );
            }
        }
    }

}
