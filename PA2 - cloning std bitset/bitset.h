/*!******************************************************************
 * \file      bitset.h
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      12-09-2023
 *
 * \brief
 *********************************************************************/
#ifndef BITSET_H
#define BITSET_H

namespace HLP3
{
    /**
     * @brief A fixed-size sequence of N bits.
     */
    template <unsigned int N>
    class bitset
    {
    private:
        bool *data; ///< Dynamic array to hold the bits.

    public:
        /**
         * @brief Default constructor.
         */
        bitset();

        /**
         * @brief Destructor.
         */
        ~bitset();

        /**
         * @brief Sets the bit at the given index to true.
         * @param index The index of the bit to set.
         */
        void set(unsigned int index);

        /**
         * @brief Sets the bit at the given index to the specified value.
         * @param index The index of the bit to set.
         * @param value The value to set the bit to.
         */
        void set(unsigned int index, bool value);

        /**
         * @brief Resets the bit at the given index to false.
         * @param index The index of the bit to reset.
         */
        void reset(unsigned int index);

        /**
         * @brief Flips the bit at the given index.
         * @param index The index of the bit to flip.
         */
        void flip(unsigned int index);

        /**
         * @brief Counts the number of bits set to true.
         * @return The number of bits set to true.
         */
        unsigned int count() const;

        /**
         * @brief Returns the size of the bitset.
         * @return The size of the bitset.
         */
        unsigned int size() const;

        /**
         * @brief Tests the value of the bit at the given index.
         * @param index The index of the bit to test.
         * @return The value of the bit at the given index.
         */
        bool test(unsigned int index) const;

        /**
         * @brief Converts the bitset to a string.
         * @param falseChar Character to represent false bits.
         * @param trueChar Character to represent true bits.
         * @return The string representation of the bitset.
         */
        std::string to_string(char falseChar, char trueChar) const;

        /**
         * @brief Converts the bitset to a string.
         * @param sameChar Character to represent both true and false bits.
         * @return The string representation of the bitset.
         */
        std::string to_string(char sameChar) const;

        /**
         * @brief Converts the bitset to a string using default characters ('0' and '1').
         * @return The string representation of the bitset.
         */
        std::string to_string() const;

        /**
         * @brief Access the value of the bit at the given index.
         * @param index The index of the bit to access.
         * @return The value of the bit at the given index.
         */
        bool operator[](unsigned int index) const;
    };
}

#include "bitset.hpp"
#endif
