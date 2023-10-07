/*!******************************************************************
 * \file      matrix-proxy.hpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      06-10-2023
 *
 * \brief     C++ style API for matrices with proxy classes.
 *********************************************************************/
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
        using size_type = size_t;
        using value_type = T;
        using pointer = T *;

        /**
         * @brief Constructor for creating a Matrix object.
         *
         * @param nr Number of rows.
         * @param nc Number of columns.
         */
        Matrix(size_type nr, size_type nc);

        /**
         * @brief Copy constructor for creating a Matrix object from another Matrix object.
         *
         * @param rhs The Matrix object to be copied.
         */
        Matrix(Matrix const &rhs);

        /**
         * @brief Move constructor for creating a Matrix object by moving the contents of another Matrix object.
         *
         * @param rhs The Matrix object to be moved.
         */
        Matrix(Matrix &&rhs) noexcept;

        /**
         * @brief Constructor for creating a Matrix object from an initializer list of initializer lists.
         *
         * @param list An initializer list of initializer lists containing values of the matrix.
         */
        Matrix(std::initializer_list<std::initializer_list<value_type>>);

        /**
         * @brief Destructor for the Matrix class.
         */
        ~Matrix() noexcept;

        /**
         * @brief Copy assignment operator.
         *
         * @param rhs The Matrix object from which to copy.
         * @return A reference to the updated Matrix object.
         */
        Matrix &operator=(Matrix const &rhs);

        /**
         * @brief Move assignment operator.
         *
         * @param rhs The Matrix object from which to move.
         * @return A reference to the updated Matrix object.
         */
        Matrix &operator=(Matrix &&rhs) noexcept;

        /**
         * @brief Get the number of rows in the Matrix.
         *
         * @return The number of rows.
         */
        size_type get_rows() const noexcept;

        /**
         * @brief Get the number of columns in the Matrix.
         *
         * @return The number of columns.
         */
        size_type get_cols() const noexcept;

    private:
        size_type rows;
        size_type cols;
        pointer data;

    public:
        class Proxy
        {
        public:
            /**
             * @brief Constructor for creating a Proxy object associated with a Matrix and a specific row.
             *
             * @param matrix The Matrix object to associate with the Proxy.
             * @param row The row index.
             */
            Proxy(Matrix &matrix, size_type row);

            /**
             * @brief Access an element in the Proxy object by column index.
             *
             * @param col The column index.
             * @return A reference to the element.
             */
            T &operator[](size_type col);

        private:
            Matrix &matrix;
            size_type row;
        };

        // Proxy class for const operations
        class ConstProxy
        {
        public:
            /**
             * @brief Constructor for creating a ConstProxy object associated with a Matrix and a specific row.
             *
             * @param matrix The Matrix object to associate with the ConstProxy (const reference).
             * @param row The row index.
             */
            ConstProxy(const Matrix &matrix, size_type row);

            /**
             * @brief Access an element in the ConstProxy object by column index (const version).
             *
             * @param col The column index.
             * @return A const reference to the element.
             */
            const T &operator[](size_type col) const;

        private:
            const Matrix &matrix;
            size_type row;
        };

        /**
         * @brief Access a row in the Matrix and return a Proxy object.
         *
         * @param row The row index.
         * @return A Proxy object for the specified row.
         */
        Proxy operator[](size_type row);

        /**
         * @brief Access a row in the Matrix and return a ConstProxy object (const version).
         *
         * @param row The row index.
         * @return A ConstProxy object for the specified row.
         */
        ConstProxy operator[](size_type row) const;

    }; // end of Matrix class

    // Member function definitions
    template <typename T>
    Matrix<T>::Matrix(size_type nr, size_type nc)
        : rows(nr), cols(nc), data(new T[nr * nc])
    {
        if (nr == 0 || nc == 0)
        {
            throw std::invalid_argument("Matrix dimensions must be positive");
        }
    }

    template <typename T>
    Matrix<T>::Matrix(Matrix const &rhs)
        : rows(rhs.rows), cols(rhs.cols), data(new T[rows * cols])
    {
        for (size_t i = 0; i < rows * cols; ++i)
        {
            data[i] = rhs.data[i];
        }
    }

    template <typename T>
    Matrix<T>::Matrix(Matrix<T> &&rhs) noexcept
        : rows(rhs.rows), cols(rhs.cols), data(std::move(rhs.data))
    {
        rhs.rows = 0;
        rhs.cols = 0;
        rhs.data = nullptr;
    }

    template <typename T>
    Matrix<T>::Matrix(std::initializer_list<std::initializer_list<value_type>> initList)
        : rows(initList.size()), cols(rows > 0 ? initList.begin()->size() : 0), data(nullptr)
    {
        // Check if there are rows, otherwise, data remains nullptr.

        // Check that all inner initializer lists have the same number of elements.
        for (const auto &row : initList)
        {
            if (row.size() != cols)
            {
                throw std::runtime_error("bad initializer list");
            }
        }

        // Allocate memory for the matrix data.
        data = new value_type[rows * cols];

        // Copy elements from the initializer list into the allocated memory.
        size_t index = 0;
        for (const auto &row : initList)
        {
            for (const auto &elem : row)
            {
                data[index++] = elem;
            }
        }
    }

    template <typename T>
    Matrix<T>::~Matrix() noexcept
    {
        delete[] data;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator=(const Matrix<T> &rhs)
    {
        if (this == &rhs)
        {
            return *this; // Self-assignment
        }

        // Release the current data
        delete[] data;

        // Copy dimensions
        rows = rhs.rows;
        cols = rhs.cols;

        // Allocate data
        data = new T[rows * cols];

        // Copy elements
        std::copy(rhs.data, rhs.data + (rhs.rows * rhs.cols), data);

        return *this;
    }

    template <typename T>
    Matrix<T> &Matrix<T>::operator=(Matrix<T> &&rhs) noexcept
    {
        if (this == &rhs)
        {
            return *this; // Self-assignment, no action needed
        }

        // Release the current data
        delete[] data;

        // Move dimensions and data from rhs
        rows = rhs.rows;
        cols = rhs.cols;
        data = rhs.data;

        // Reset rhs to a valid state
        rhs.rows = 0;
        rhs.cols = 0;
        rhs.data = nullptr;

        return *this;
    }

    template <typename T>
    typename Matrix<T>::size_type Matrix<T>::get_rows() const noexcept
    {
        return rows;
    }

    template <typename T>
    typename Matrix<T>::size_type Matrix<T>::get_cols() const noexcept
    {
        return cols;
    }

    template <typename T>
    Matrix<T>::Proxy::Proxy(Matrix &matrix, size_type row)
        : matrix(matrix), row(row)
    {
    }

    template <typename T>
    T &Matrix<T>::Proxy::operator[](size_type col)
    {
        size_type index = row * matrix.cols + col;

        return matrix.data[index];
    }

    template <typename T>
    typename Matrix<T>::Proxy Matrix<T>::operator[](size_type row)
    {
        return Proxy(*this, row);
    }

    template <typename T>
    Matrix<T>::ConstProxy::ConstProxy(const Matrix &matrix, size_type row)
        : matrix(matrix), row(row)
    {
    }

    template <typename T>
    const T &Matrix<T>::ConstProxy::operator[](size_type col) const
    {
        size_type index = row * matrix.cols + col;

        return matrix.data[index];
    }

    template <typename T>
    typename Matrix<T>::ConstProxy Matrix<T>::operator[](size_type row) const
    {
        return ConstProxy(*this, row);
    }

    /**
     * @brief Overload of the addition operator for matrices.
     *
     * This function adds two matrices of the same dimensions element-wise and returns the result as a new matrix.
     *
     * @param lhs The left-hand side matrix.
     * @param rhs The right-hand side matrix.
     * @return The result of adding the two matrices.
     * @throws std::invalid_argument if the matrices have different dimensions.
     */
    template <typename T>
    Matrix<T> operator+(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if (lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            throw std::invalid_argument("operands for matrix addition must have same dimensions");
        }

        Matrix<T> result(lhs.get_rows(), lhs.get_cols());

        for (size_t i = 0; i < lhs.get_rows(); ++i)
        {
            for (size_t j = 0; j < lhs.get_cols(); ++j)
            {
                result[i][j] = lhs[i][j] + rhs[i][j];
            }
        }

        return result;
    }

    /**
     * @brief Overload of the subtraction operator for matrices.
     *
     * This function subtracts one matrix from another matrix of the same dimensions element-wise and returns the result as a new matrix.
     *
     * @param lhs The left-hand side matrix.
     * @param rhs The right-hand side matrix.
     * @return The result of subtracting the second matrix from the first matrix.
     * @throws std::invalid_argument if the matrices have different dimensions.
     */
    template <typename T>
    Matrix<T> operator-(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if (lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            throw std::invalid_argument("operands for matrix subtraction must have same dimensions");
        }

        Matrix<T> result(lhs.get_rows(), lhs.get_cols());

        for (size_t i = 0; i < lhs.get_rows(); ++i)
        {
            for (size_t j = 0; j < lhs.get_cols(); ++j)
            {
                result[i][j] = lhs[i][j] - rhs[i][j];
            }
        }

        return result;
    }

    /**
     * @brief Overload of the multiplication operator for matrices.
     *
     * This function multiplies two matrices, where the number of columns in the left operand must match the number of rows in the right operand. It returns the result as a new matrix.
     *
     * @param lhs The left-hand side matrix.
     * @param rhs The right-hand side matrix.
     * @return The result of multiplying the two matrices.
     * @throws std::invalid_argument if the number of columns in the left operand does not match the number of rows in the right operand.
     */
    template <typename T>
    Matrix<T> operator*(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if (lhs.get_cols() != rhs.get_rows())
        {
            throw std::invalid_argument("number of columns in left operand must match number of rows in right operand");
        }

        Matrix<T> result(lhs.get_rows(), rhs.get_cols());

        for (size_t i = 0; i < lhs.get_rows(); ++i)
        {
            for (size_t j = 0; j < rhs.get_cols(); ++j)
            {
                T sum = 0;
                for (size_t k = 0; k < lhs.get_cols(); ++k)
                {
                    sum += lhs[i][k] * rhs[k][j];
                }
                result[i][j] = sum;
            }
        }

        return result;
    }

    /**
     * @brief Overload of the multiplication operator for a scalar and a matrix.
     *
     * This function multiplies a scalar value by each element of a matrix and returns the result as a new matrix.
     *
     * @param lhs The scalar value.
     * @param rhs The matrix.
     * @return The result of multiplying the scalar value with each element of the matrix.
     */
    template <typename T>
    Matrix<T> operator*(T lhs, const Matrix<T> &rhs)
    {
        Matrix<T> result(rhs.get_rows(), rhs.get_cols());

        for (size_t i = 0; i < rhs.get_rows(); ++i)
        {
            for (size_t j = 0; j < rhs.get_cols(); ++j)
            {
                result[i][j] = lhs * rhs[i][j];
            }
        }

        return result;
    }

    /**
     * @brief Overload of the equality comparison operator for matrices.
     *
     * This function checks whether two matrices are equal by comparing their dimensions and elements.
     *
     * @param lhs The left-hand side matrix.
     * @param rhs The right-hand side matrix.
     * @return True if the matrices are equal (have the same dimensions and identical elements), false otherwise.
     */
    template <typename T>
    bool operator==(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        if (lhs.get_rows() != rhs.get_rows() || lhs.get_cols() != rhs.get_cols())
        {
            return false; // Matrices have different dimensions, so they are not equal.
        }

        for (size_t i = 0; i < lhs.get_rows(); ++i)
        {
            for (size_t j = 0; j < lhs.get_cols(); ++j)
            {
                if (lhs[i][j] != rhs[i][j])
                {
                    return false; // Found unequal element, matrices are not equal.
                }
            }
        }

        return true; // All elements are equal, matrices are equal.
    }

    /**
     * @brief Overload of the inequality comparison operator for matrices.
     *
     * This function checks whether two matrices are not equal by negating the result of the equality comparison.
     *
     * @param lhs The left-hand side matrix.
     * @param rhs The right-hand side matrix.
     * @return True if the matrices are not equal (have different dimensions or different elements), false if they are equal.
     */
    template <typename T>
    bool operator!=(const Matrix<T> &lhs, const Matrix<T> &rhs)
    {
        return !(lhs == rhs); // use overload for == to return opposite.
    }
}

#endif
