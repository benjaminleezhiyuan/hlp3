/*!******************************************************************
 * \file      polynomial.h
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      24-10-2023
 *
 * \brief     Polynomial class declaration and member function declaration
 *            for polynomial arithmatic.
 *********************************************************************/

#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream> // std::ostream

namespace HLP3
{
    // declare class template Polynomial
    template <typename T, int N>
    class Polynomial
    {
    public:
        /**
         * @brief Evaluate the polynomial at a given value.
         *
         * @param a The value at which the polynomial should be evaluated.
         * @return The result of the polynomial evaluation at 'a'.
         */
        T operator()(T a) const; // evaluate polynomial at x = a

        /**
         * @brief Multiply this polynomial by another polynomial.
         *
         * @tparam M The degree of the other polynomial.
         * @param other The other polynomial to multiply with.
         * @return A new polynomial representing the product of the two polynomials.
         */
        template <int M>
        Polynomial<T, N + M>
        operator*(const Polynomial<T, M> &other) const; // multiply operator

        /**
         * @brief Default Constructor.
         *
         * This constructor creates a new polynomial, initializing it as a zero polynomial.
         */
        Polynomial(); // default ctor

        /**
         * @brief Constructor to create a polynomial from another polynomial of a different coefficient type.
         *
         * @tparam U The coefficient type of the other polynomial.
         * @param other The other polynomial to create a new polynomial from.
         */
        template <typename U>
        Polynomial(const Polynomial<U, N> &other); // single argument

        /**
         * @brief Modifiable Subscript Operator.
         *
         * @param idx The index of the coefficient to access and modify.
         * @return A reference to the coefficient at the specified index.
         */
        T &operator[](int idx); // modifiable subscript overload

        /**
         * @brief Non-Modifiable Subscript Operator.
         *
         * @param idx The index of the coefficient to access.
         * @return A constant reference to the coefficient at the specified index.
         */
        const T &operator[](int idx) const; // non modifiable subscript overload

    private:
        T coefficients[N + 1]; // coefficients of the polynomial
    };
}

#include "polynomial.tpp"

#endif
