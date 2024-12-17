/*
Written by Peter Bosch
 under BSD license at github.com/peterbjornx/cppmath
 */

#ifndef CPPMATH_VEC3_H
#define CPPMATH_VEC3_H

#include <iostream>
#include "math/tmath.h"

template<class K>
class vec3 {
public:
    K x,y,z;

    vec3() { x = 0; y = 0; z = 0; }

    vec3( K x, K y, K z) : x(x), y(y), z(z) {};

    const K& operator[](int i) const {
        switch( i ) {
            case 0:
                return x;
            case 1:
                return y;
            default:
                return z;
        }
    }

    K& operator[](int i) {
        switch( i ) {
            case 0:
                return x;
            case 1:
                return y;
            default:
                return z;
        }
    }

    /* Scalar multiplication */

    vec3<K> operator*=( const K &s ) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    vec3<K> operator/=( const K &s ) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
    }

    vec3<K> operator*( const K &b ) const {
        vec3<K> r = *this;
        r *= b;
        return r;
    }

    vec3<K> operator/( const K &b ) const {
        vec3<K> r = *this;
        r /= b;
        return r;
    }

    /* Vector sum, difference */

    vec3<K> & operator+=( const vec3<K> &b ) {
        x += b.x;
        y += b.y;
        z += b.z;
    }

    vec3<K> & operator-=( const vec3<K> &b ) {
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    vec3<K> operator+( const vec3<K> &b ) const {
        vec3<K> r = *this;
        r += b;
        return r;
    }

    vec3<K> operator-( const vec3<K> &b ) const {
        vec3<K> r = *this;
        r -= b;
        return r;
    }

    vec3<K> operator-( ) const {
        return vec3<K>(-x,-y,-z);
    }

    /* Inner product */

    K operator*( const vec3<K> &b ) const {
        return x*b.x + y*b.y + z*b.z;
    }

    /* Cross product */

    vec3<K> cross( const vec3<K> &b) const {
        vec3<K> r = *this;
        r.x = y * b.z - z * b.y;
        r.y = z * b.x - x * b.z;
        r.z = x * b.y - y * b.x;
        return r;
    }

    /* Norm */
    K norm() const {
        return tsqrt(*this * *this);
    }

    /* Normalize */
    vec3<K> &normalize() {
        *this /= norm();
        return *this;
    }

    vec3<K> normal() const {
        return *this / norm();
    }

    vec3<float> toFloat() const {
        return vec3<float>(x,y,z);
    }

};

template<class K>
std::ostream& operator<<(std::ostream& os, const vec3<K>& dt)
{
    os << '[' <<dt.x << ' ' << dt.y << ' ' << dt.z << ']';
    return os;
}


#endif //CPPMATH_VEC3_H
