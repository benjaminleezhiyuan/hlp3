/*!******************************************************************
 * \file      matrix-proxy.hpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      06-10-2023
 *
 * \brief
 *********************************************************************/

// Don't forget file-header and function-level Doxygen documentation blocks!!!

// First, define the class template. Then, define the member functions of the class template
// OUTSIDE the class definition. The automatic grader will not be able to check for this -
// however, the manual grader can. Occurrences of EACH such function defined in the class definition
//  will result in a deduction of ONE LETTER GRADE!!! You're forewarned!!!

// This is how you should implement the assignment:

#ifndef MATRIX_PROXY_HPP
#define MATRIX_PROXY_HPP

// include necessary headers ...
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace HLP3
{
    template <typename T>
    class Matrix
    {
    public:
        // provide common standard library container type definitions
        // with using keyword ...
        using size_type = std::size_t;
        using value_type = T;
        using pointer = T *;

    public:
        // To allow clients to access values in an object m of type Matrix m
        // using m[r][c] syntax, define a proxy class.
        // Note that this nested class is simply a type and has no inherent access
        // to any of outer class' members. Therefore, proxy class definition
        // declares 2 data members: a Matrix& data member that references Matrix
        // object instantiating the proxy object and a size_type data member
        // indicating the matrix row. Suppose a call to Matrix object's member
        // function (*this).op[](r) returns a proxy object constructed with a
        // reference to *this and the value of (row) index.
        // The proxy class will then define an overload of op[](size_type c) to
        // return the value stored in the Matrix object's data store data[r].
        // a second nested proxy class definition for Matrix const&
        // ctors, dtor, copy, and move functions ...
        // Proxy class for non-const operations
        class Proxy
        {
        public:
            Proxy(Matrix &matrix, size_type row)
                : matrix(matrix), row(row) {}

            T &operator[](size_type col)
            {
                if (col >= matrix.cols || row >= matrix.rows)
                    throw std::out_of_range("Matrix index out of range");
                return matrix.data[row * matrix.cols + col];
            }

        private:
            Matrix &matrix;
            size_type row;
        };

        // Proxy class for const operations
        class ConstProxy
        {
        public:
            ConstProxy(const Matrix &matrix, size_type row)
                : matrix(matrix), row(row) {}

            const T &operator[](size_type col) const
            {
                if (col >= matrix.cols || row >= matrix.rows)
                    throw std::out_of_range("Matrix index out of range");
                return matrix.data[row * matrix.cols + col];
            }

        private:
            const Matrix &matrix;
            size_type row;
        };

        Matrix(size_type nr, size_type nc);
        Matrix(Matrix const &rhs);
        Matrix(Matrix &&rhs) noexcept;
        Matrix(std::initializer_list<std::initializer_list<value_type>>);
        ~Matrix() noexcept;
        Matrix &operator=(Matrix const &rhs);
        Matrix &operator=(Matrix &&rhs) noexcept;
        size_type get_rows() const noexcept;
        size_type get_cols() const noexcept;
proxy-class-for-Matrix operator[](size_type r);
proxy-class-for-Matrix-const operator[](size_type r) const;

private:
size_type rows;
size_type cols;
pointer data;
    };
    // declare global functions for following operator overloads:
    // 1. +: adding two Matrix<T> objects
    // 2. -: subtracting two Matrix<T> objects
    // 3. *: multiplying two Matrix<T> objects
    // 4. ==: compare two Matrix<T> objects for equality
    // 5. !=: compare two Matrix<T> objects for inequality
}

#endif
