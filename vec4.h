/*
Written by Peter Bosch
 under BSD license at github.com/peterbjornx/cppmath
 */

#ifndef CPPMATH_VEC4_H
#define CPPMATH_VEC4_H

#include <iostream>
#include "tmath.h"
#include <math/vec3.h>

template<class K>
class vec4 {
public:
    K x,y,z,w;

    vec4() { x = 0; y = 0; z = 0; w = 0; }

    vec4( K x, K y, K z, K w) : x(x), y(y), z(z), w(w) {};

    const K& operator[](int i) const {
        switch( i ) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return w;
        }
    }

    K& operator[](int i) {
        switch( i ) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                return w;
        }
    }

    /* Scalar multiplication */

    vec4<K> operator*=( const K &s ) {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
    }

    vec4<K> operator/=( const K &s ) {
        x /= s;
        y /= s;
        z /= s;
        w /= s;
        return *this;
    }

    vec4<K> operator*( const K &b ) const {
        vec4<K> r = *this;
        r *= b;
        return r;
    }

    vec4<K> operator/( const K &b ) const {
        vec4<K> r = *this;
        r /= b;
        return r;
    }

    /* Vector sum, difference */

    vec4<K> & operator+=( const vec4<K> &b ) {
        x += b.x;
        y += b.y;
        z += b.z;
        w += b.w;
    }

    vec4<K> & operator-=( const vec4<K> &b ) {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        w -= b.w;
        return *this;
    }

    vec4<K> operator+( const vec4<K> &b ) const {
        vec4<K> r = *this;
        r += b;
        return r;
    }

    vec4<K> operator-( const vec4<K> &b ) const {
        vec4<K> r = *this;
        r -= b;
        return r;
    }

    vec4<K> operator-( ) const {
        return vec4<K>(-x,-y,-z,-w);
    }

    /* Inner product */

    K operator*( const vec4<K> &b ) const {
        return x*b.x + y*b.y + z*b.z + w*b.w;
    }

    /* Cross product */

    vec4<K> cross( const vec4<K> &b) const {
        vec4<K> r = *this;
        r.x = y * b.z - z * b.y;
        r.y = z * b.x - x * b.z;
        r.z = x * b.y - y * b.x;
        r.w = w;
        return r;
    }

    /* Norm */
    K norm() const {
        return tsqrt(*this * *this);
    }

    /* Normalize */
    vec4<K> &normalize() {
        *this /= norm();
        return *this;
    }

    vec4<K> normal() const {
        return *this / norm();
    }

    /* Conversion */
    vec4<float> toFloat() const {
        return vec4<float>(x,y,z,w);
    }

    vec3<K> toVec3() const {
        return vec3<K>(x,y,z);
    }

};

template<class K>
std::ostream& operator<<(std::ostream& os, const vec4<K>& dt)
{
    os << '[' <<dt.x << ' ' << dt.y << ' ' << dt.z << ' ' << dt.w << ']';
    return os;
}


#endif //CPPMATH_VEC3_H
