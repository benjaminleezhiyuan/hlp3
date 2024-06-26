/*!******************************************************************
 * \file      bitset.hpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      12-09-2023
 *
 * \brief     This file contains the implementation for bitset clone
 *********************************************************************/

namespace HLP3
{
    /**
     * @brief Default constructor.
     * Allocates memory and sets all bits to false based on the size.
     */
    template <unsigned int N>
    bitset<N>::bitset()
    {
        // Allocate memory for the data array and initialize all bits to false.
        data = new bool[N];
        for (unsigned int i = 0; i < N; ++i)
        {
            data[i] = false;
        }
    }

    /**
     * @brief Destructor, deletes memory allocated.
     */
    template <unsigned int N>
    bitset<N>::~bitset()
    {
        // Deallocate the memory used by the data array.
        delete[] data;
    }

    /**
     * @brief Sets the bit at the given index to true.
     * @param index The index of the bit to set.
     */
    template <unsigned int N>
    void bitset<N>::set(unsigned int index)
    {
        if (index < N)
        {
            data[index] = true;
        }
        else
        {
            // Handle out-of-bounds error by throwing an exception.
            throw std::out_of_range("Index out of bounds.");
        }
    }

    /**
     * @brief Sets the bit at the given index to the specified value.
     * @param index The index of the bit to set.
     * @param value The value to set the bit to.
     */
    template <unsigned int N>
    void bitset<N>::set(unsigned int index, bool value)
    {
        if (index < N)
        {
            data[index] = value;
        }
        else
        {
            // Handle out-of-bounds error by throwing an exception.
            throw std::out_of_range("Index out of bounds.");
        }
    }

    /**
     * @brief Resets the bit at the given index to false.
     * @param index The index of the bit to reset.
     */
    template <unsigned int N>
    void bitset<N>::reset(unsigned int index)
    {
        if (index < N)
        {
            data[index] = false;
        }
        else
        {
            // Handle out-of-bounds error by throwing an exception.
            throw std::out_of_range("Index out of bounds.");
        }
    }

    /**
     * @brief Flips the bit at the given index.
     * @param index The index of the bit to flip.
     */
    template <unsigned int N>
    void bitset<N>::flip(unsigned int index)
    {
        if (index < N)
        {
            data[index] = !data[index];
        }
        else
        {
            // Handle out-of-bounds error by throwing an exception.
            throw std::out_of_range("Index out of bounds.");
        }
    }

    /**
     * @brief Counts the number of bits set to true.
     * @return The number of bits set to true.
     */
    template <unsigned int N>
    unsigned int bitset<N>::count() const
    {
        unsigned int trueCount = 0;

        for (unsigned int i = 0; i < N; ++i)
        {
            if (data[i])
            {
                trueCount++;
            }
        }

        return trueCount;
    }

    /**
     * @brief Returns the size of the bitset.
     * @return The size of the bitset.
     */
    template <unsigned int N>
    unsigned int bitset<N>::size() const
    {
        return N;
    }

    /**
     * @brief Tests the value of the bit at the given index.
     * @param index The index of the bit to test.
     * @return The value of the bit at the given index.
     */
    template <unsigned int N>
    bool bitset<N>::test(unsigned int index) const
    {
        if (index < N)
        {
            return data[index];
        }
        else
        {
            // Handle out-of-bounds error by throwing an exception.
            throw std::out_of_range("Index out of bounds.");
        }
    }
    /**
     * @brief Converts the bitset to a string using default characters ('0' and '1').
     * @return The string representation of the bitset.
     */
    /**
     * @brief Converts the bitset to a string.
     * @param falseChar Character to represent false bits.
     * @param trueChar Character to represent true bits.
     * @return The string representation of the bitset.
     */
    template <unsigned int N>
    std::string bitset<N>::to_string() const
    {
        std::string result;
        for (int i = N - 1; i >= 0; --i)
        {
            result.push_back(data[i] ? '1' : '0');
        }
        return result;
    }

    /**
     * @brief Converts the bitset to a string.
     * @param sameChar Character to represent both true and false bits.
     * @return The string representation of the bitset.
     */
    template <unsigned int N>
    std::string bitset<N>::to_string(char sameChar) const
    {
        std::string result;
        for (int i = N - 1; i >= 0; --i)
        {
            result.push_back(data[i] ? '1' : sameChar);
        }
        return result;
    }

    /**
     * @brief Converts the bitset to a string using default characters ('0' and '1').
     * @return The string representation of the bitset.
     */
    template <unsigned int N>
    std::string bitset<N>::to_string(char falseChar, char trueChar) const
    {
        std::string result;
        for (int i = N - 1; i >= 0; --i)
        {
            result.push_back(data[i] ? trueChar : falseChar);
        }
        return result;
    }

    /**
     * @brief Access the value of the bit at the given index.
     * @param index The index of the bit to access.
     * @return The value of the bit at the given index.
     */
    template <unsigned int N>
    bool bitset<N>::operator[](unsigned int index) const
    {
        if (index < N)
        {
            return data[index];
        }
        // You can choose to handle an out-of-bounds index differently if needed.
        return false;
    }

} // end of namespace HLP3
