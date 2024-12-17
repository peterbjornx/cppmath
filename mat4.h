/*
Written by Peter Bosch
 under BSD license at github.com/cppmath
 */

#ifndef CPPMATH_MAT4_H
#define CPPMATH_MAT4_H

#include <math.h>
#include "math/vec3.h"
#include "math/vec4.h"

template<class K>
class mat4 {
public:
    K a[16];



    static mat4<K> zero() {
        return mat4<K>();
    }

    static mat4<K> identity() {
        return mat4<K>().set_identity();
    }

    static mat4<K> translation( K x , K y, K z ) {
        return mat4<K>().set_translation( x, y, z );
    }

    static mat4<K> translation( vec3<K> vec ) {
        return mat4<K>().set_translation( vec );
    }

    static mat4<K> perspective( K fov, K far, K near ) {
        return mat4<K>().set_perspective( fov, far, near );
    }

    mat4<K> &set_zero() {
        for ( int i = 0; i < 16; i++ )
            a[i] = 0.;
        return *this;
    }

    mat4<K> &set_identity() {
        set_zero();
        for ( int i = 0; i < 16; i += 5 )
            a[i] = 1.;
        return *this;
    }

    mat4<K> &set_translation( K x, K y, K z ) {
        set_identity();
        translate( x, y, z );
        return *this;
    }

    mat4<K> &set_translation( vec3<K> v ) {
        set_identity();
        translate( v );
        return *this;
    }

    mat4<K> &translate( K x, K y, K z ) {
        a[12] += x * a[15];
        a[13] += y * a[15];
        a[14] += z * a[15];
        return *this;
    }

    mat4<K> &translate(const vec3<double> v) {
        return translate( v.x, v.y, v.z );
    }

    mat4<K> &set_perspective( K fov, K far, K near ) {
        K S = ttan( fov * M_PI / 360. );
        set_zero();
        /* X,X */
        a[0]  = 1/S;
        /* Y,Y */
        a[5]  = 1/S;
        /* Z,Z */
        a[10] = ( far + near ) / ( far - near );
        /* W,Z */
        a[11] = 1.;
        /* Z,W */
        a[14] =  -2. * ( far * near ) / ( far - near );
        return *this;
    }

    mat4() {
        set_zero();
    }

    /* Matrix sum, difference */

    mat4<K> & operator+=( const mat4<K> &b ) {
        for ( int i = 0; i < 16; i++ )
            a[i] += b.a[i];
    }

    mat4<K> & operator-=( const mat4<K> &b ) {
        for ( int i = 0; i < 16; i++ )
            a[i] -= b.a[i];
    }

    mat4<K> operator+( const mat4<K> &b ) const {
        mat4<K> r = *this;
        r += b;
        return r;
    }

    mat4<K> operator-( const mat4<K> &b ) const {
        mat4<K> r = *this;
        r -= b;
        return r;
    }

    /* Matrix multiplication */

    mat4<K> operator*( const mat4<K> &b ) {
        mat4<K> c;
        for (int i = 0; i < 4; i++) /* row */
            for (int j = 0; j < 4; j++) /* col */
                for (int k = 0; k < 4; k++)
                    c.a[i + j * 4] += a[i + k * 4] * b.a[k + j * 4];
        return c;
    }

    mat4<K> & operator*=( const mat4<K> &b ) {
        *this = *this * b;
        return *this;
    }

    /* Vector (post-) multiplication */

    vec3<K> operator*( const vec3<K> &b ) const {
        vec3<K> r;
        for (int i = 0; i < 3; i++) /* row */ {
            for (int k = 0; k < 3; k++)
                r[i] += a[i + k * 4] * b[k];
            r[i] += a[i + 3 * 4] * 1.;
        }
        return r;
    }

    vec4<K> operator*( const vec4<K> &b ) const {
        vec4<K> r;
        for (int i = 0; i < 4; i++) /* row */
            for (int k = 0; k < 4; k++)
                r[i] += a[i + k * 4] * b[k];
        return r;
    }

    mat4<float> asFloat( ) const {
        mat4<float> f;
        for ( int i = 0; i < 16; i++ )
            f.a[i] = a[i];
        return f;
    }
};

template<class K>
vec3<K> operator*( const vec3<K> &a, const mat4<K> &b ) {
    vec3<K> r;
    for (int i = 0; i < 3; i++) /* col */ {
        for (int k = 0; k < 3; k++)
            r[i] += a[k] * b.a[k + i * 4];
        r[i] += b[3 + i * 4];
    }
    return r;
}

template<class K>
vec3<K> & operator*=( const vec3<K> &a, const mat4<K> &b ) {
    a = a * b;
    return a;
}

template<class K>
vec3<K> & operator*=( const mat4<K> &a, const vec3<K> &b ) {
    a = a * b;
    return a;
}

template<class K>
vec4<K> operator*( const vec4<K> &a, const mat4<K> &b ) {
    vec4<K> r;
    for (int i = 0; i < 4; i++) /* row */
        for (int k = 0; k < 4; k++)
            r[i] += a[k] * b.a[k + i * 4];
    return r;
}

template<class K>
vec4<K> & operator*=( const vec4<K> &a, const mat4<K> &b ) {
    a = a * b;
    return a;
}

template<class K>
vec4<K> & operator*=( const mat4<K> &a, const vec4<K> &b ) {
    a = a * b;
    return a;
}

#endif //CPPMATH_MAT4_H
