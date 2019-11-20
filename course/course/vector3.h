#ifndef VECTOR3_H
#define VECTOR3_H
#include<stdio.h>
#include<vector>
#include<math.h>


typedef MyVector<int, 3> vec3;

template <typename T, size_t size>
class MyVector{
public:
    MyVector() {
        for (int i =0; i < size; i++){
            vec[i] = 0;
        }
    }

    T& operator [](size_t n){
        return vec[n];
    }

    T operator [](size_t n) const {
        return vec[n];
    }

    int lenght() {
        return size;
    }

    int lenght2() {
        return size*size;
    }

    MyVector& normalize() const
    {
        T sum = 0;
        for (int i = 0; i < size; i++) {
            sum += vec[i]*vec[i];
        }
        int inv_length = 1.0f / sqrt(sum);
        return (*this * inv_length);
    }

    MyVector& operator += ( const MyVector& v ) {
        for (size_t i = 0; i < size; i++) {
             vec[i] += v[i];
        }
        return *this;
    }

    MyVector& operator -= ( const MyVector& v ) {
        for (size_t i = 0; i < size; i++) {
             vec[i] -= v[i];
        }
        return *this;
    }

    MyVector& operator *= ( const double d ){
        for (size_t i = 0; i < size; i++) {
             vec[i] *= d;
        }
        return *this;
    }

    MyVector& operator /= ( const double d ){
        for (size_t i = 0; i < size; i++) {
             vec[i] /= d;
        }
        return *this;
    }

    MyVector& operator - (){
        for (size_t i = 0; i < size; i++) {
             vec[i] *= -1;
        }
        return *this;
    }

    MyVector operator + (const MyVector& b){
        MyVector a;

        for (size_t i = 0; i < size; i++) {
            a[i] = vec[i] + b[i];
        }
        return a;

    }

    MyVector operator - (const MyVector& b){
        MyVector a;

        for (size_t i = 0; i < size; i++) {
            a[i] = vec[i] - b[i];
        }
        return a;
    }

    MyVector operator * (const double d){
        MyVector a;

        for (size_t i = 0; i < size; i++) {
            a[i] = vec[i]*d;
        }
        return a;
    }

    //скалярное произведение
    T operator * (const MyVector& b){
        T res = 0;
        for (size_t i = 0; i < size; i++) {
            res += vec[i] * b[i];
        }
        return res;
    }

    MyVector operator / (const MyVector& a, const double d){
        MyVector a;

        for (size_t i = 0; i < size; i++) {
            a[i] = vec[i]/d;
        }
        return a;
    }

    bool operator == (const MyVector& b)	 {
        for (size_t i = 0; i < size; i++) {
             if (vec[i] != b[i])
                 return false;
        }
        return true;
    }

    bool operator != ( const MyVector& b){
        return !(*this == b);
    }

private:
    std::vector<T> vec(size);
};


#endif // VECTOR3_H
