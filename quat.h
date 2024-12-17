/*
Written by Peter Bosch
 under BSD license at github.com/cppmath
 */
#ifndef CPPMATH_QUAT_H
#define CPPMATH_QUAT_H

#include <iostream>
#include "math/mat4.h"
#include "mat4.h"

template<class K>
class quat {
public:
    K s,i,j,k;

    quat() { s = 1; i = 0; j = 0; k = 0; }

    quat( K s, K i, K j, K k) : s(s), i(i), j(j), k(k) {};

    quat( K s, vec3<K> v ) : s(s), i(v.x), j(v.y), k(v.z) {};

    K& operator[](int n) const {
        switch( n ) {
            case 0:
                return s;
            case 1:
                return i;
            case 2:
                return j;
            default:
                return k;
        }
    }

    /* Scalar multiplication */

    quat<K> operator*=( const K &_s ) {
        s *= _s;
        i *= _s;
        j *= _s;
        k *= _s;
        return *this;
    }

    quat<K> operator/=( const K &_s ) {
        s /= _s;
        i /= _s;
        j /= _s;
        k /= _s;
        return *this;
    }

    quat<K> operator*( const K &b ) const {
        quat<K> r = *this;
        r *= b;
        return r;
    }

    quat<K> operator/( const K &b ) const {
        quat<K> r = *this;
        r /= b;
        return r;
    }

    /* Vector sum, difference */

    quat<K> & operator+=( const quat<K> &b ) {
        s += b.s;
        i += b.i;
        j += b.j;
        k += b.k;
    }

    quat<K> & operator-=( const quat<K> &b ) {
        s -= b.s;
        i -= b.i;
        j -= b.j;
        k -= b.k;
        return *this;
    }

    quat<K> operator+( const quat<K> &b ) {
        quat<K> r = *this;
        r += b;
        return r;
    }

    quat<K> operator-( const quat<K> &b ) {
        quat<K> r = *this;
        r -= b;
        return r;
    }

    quat<K> operator-( ) const {
        return quat<K>(-s,-i,-j,-k);
    }

    /* Conjugate */

    quat<K> operator~( ) const {
        return quat<K>(s,-i,-j,-k);
    }

    /* Quaternion product */

    quat<K> operator*( const quat<K> &b ) const {
        quat<K> r;
        r.s = s * b.s - i * b.i - j * b.j - k * b.k;
        r.i = s * b.i + i * b.s + j * b.k - k * b.j;
        r.j = s * b.j + j * b.s + k * b.i - i * b.k;
        r.k = s * b.k + k * b.s + i * b.j - j * b.i;
        return r;
    }

    quat<K> & operator*=( const quat<K> &b ) {
        *this = *this * b;
        return *this;
    }

    /* Dot/inner product */

    K dot( const quat<K> &b ) const {
        return s * b.s + i * b.i + j * b.j + k * b.k;
    }

    /* Inverse */

    quat<K> operator!( ) {
        return (~*this) / dot(*this);
    }

    /* Norm */

    K norm() const {
        return tsqrt(dot(*this));
    }

    /* Normalize */

    quat<K> &normalize() {
        *this /= norm();
        return *this;
    }

    quat<K> normal() const {
        return *this / norm();
    }

    mat4<K> to_matrix() const {
        quat<K> n = normal();
        mat4<K> res;
        res.a[0] = 1. - 2. * n.j * n.j - 2. * n.k * n.k;
        res.a[1] =      2. * n.i * n.j + 2. * n.k * n.s;
        res.a[2] =      2. * n.i * n.k - 2. * n.j * n.s;
        res.a[3] = 0;

        res.a[4] =      2. * n.i * n.j - 2. * n.k * n.s;
        res.a[5] = 1. - 2. * n.i * n.i - 2. * n.k * n.k;
        res.a[6] =      2. * n.j * n.k + 2. * n.i * n.s;
        res.a[7] = 0;

        res.a[8] =      2. * n.i * n.k + 2. * n.j * n.s;
        res.a[9] =      2. * n.j * n.k - 2. * n.i * n.s;
        res.a[10]= 1. - 2. * n.i * n.i - 2. * n.j * n.j;
        res.a[11]= 0;

        res.a[12] = 0;
        res.a[13] = 0;
        res.a[14] = 0;
        res.a[15] = 1.;

        return res;
    }

    /* Converting initializers */

    static quat<K> axis_angle(K angle, vec3<K> axis) {
        return quat<K>(
            tcos(angle / 2.),
            axis * tsin(angle / 2.)
            );
    }

    static quat<K> euler(vec3<K> euler) {
        return
            axis_angle( euler.y, vec3<K>(0,1,0) ) *
            axis_angle( euler.x, vec3<K>(1,0,0) ) *
            axis_angle( euler.z, vec3<K>(0,0,1)  );
    }

};

template<class K>
std::ostream& operator<<(std::ostream& os, const quat<K>& dt)
{
    os << '[' <<dt.s << " + i" << dt.i << " + j" << dt.j << " + k" << dt.k << ']';
    return os;
}


#endif //CPPMATH_QUAT_H
