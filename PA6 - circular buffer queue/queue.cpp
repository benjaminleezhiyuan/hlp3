/*!******************************************************************
 * \file      queue.cpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      09-11-2023
 *
 * \brief     This file contains definition for Queue class circular buffer
 *********************************************************************/

#include "queue.hpp"

namespace HLP3
{
    /**
     * @brief Constructor for the Queue class.
     * @param _capacity The maximum capacity of the queue.
     */
    Queue::Queue(size_type _capacity) : head(0), _capacity(_capacity), current_size(0)
    {
        buffer = new value_type[_capacity];
    }

    /**
     * @brief Copy constructor for the Queue class.
     * @param other The Queue object to be copied.
     */
    Queue::Queue(const Queue &other) : head(other.head), _capacity(other._capacity), current_size(other.current_size)
    {
        buffer = new value_type[_capacity];
        for (size_type i = 0; i < current_size; ++i)
        {
            buffer[i] = other.buffer[i];
        }
    }

    /**
     * @brief Copy assignment operator for the Queue class.
     * @param other The Queue object to be copied.
     * @return Reference to the updated Queue object.
     */
    Queue &Queue::operator=(const Queue &other)
    {
        // Avoid self-assignment
        delete[] buffer; // Free the existing memory

        head = other.head;
        _capacity = other._capacity;
        current_size = other.current_size;

        buffer = new value_type[_capacity]; // Allocate new memory

        // Copy elements
        for (size_type i = 0; i < _capacity; ++i)
        {
            buffer[i] = other.buffer[i];
        }

        return *this;
    }

    /**
     * @brief Destructor for the Queue class.
     * Deallocates the memory used for the buffer.
     */
    Queue::~Queue()
    {
        delete[] buffer;
    }

    /**
     * @brief Provides a constant pointer to the buffer.
     *
     * @return Pointer to the buffer of constant type.
     */
    Queue::const_pointer Queue::c_buff() const
    {
        return buffer;
    }

    /**
     * @brief Checks whether the queue is empty.
     *
     * @return True if the queue is empty, false otherwise.
     */
    bool Queue::empty() const
    {
        return current_size == 0;
    }

    /**
     * @brief Checks whether the queue is full.
     *
     * @return True if the queue is full, false otherwise.
     */
    bool Queue::full() const
    {
        return current_size == _capacity;
    }

    /**
     * @brief Retrieves the current size of the queue.
     *
     * @return The number of elements currently stored in the queue.
     */
    Queue::size_type Queue::size() const
    {
        return current_size;
    }

    /**
     * @brief Retrieves the capacity of the queue.
     *
     * @return The maximum number of elements that can be stored in the queue.
     */
    Queue::size_type Queue::capacity() const
    {
        return _capacity;
    }

    /**
     * @brief Adds a new element to the queue.
     *
     * @param element The element to be added.
     */
    void Queue::push(const value_type &element)
    {
        if (full())
        {
            head = (head + 1) % _capacity; // Increment head and when it reaches N set to 0 (% -capacity)
        }

        else
        {
            // If not full, increment size
            ++current_size;
        }

        // Add the new element at the tail
        back() = element;
    }

    /**
     * @brief Removes the oldest element from the queue.
     *
     * If the queue is not empty, this function removes the oldest element.
     * The head of the queue is incremented, and the size is decremented.
     */
    void Queue::pop()
    {
        if (!empty())
        {
            head = (head + 1) % _capacity; // Increment head
            --current_size;                // Decrement size
        }
    }

    /**
     * @brief Accessor and mutator for the oldest element in the queue.
     *
     * @return A reference to the oldest element in the queue.
     */
    Queue::reference Queue::front()
    {

        return buffer[head];
    }

    /**
     * @brief Accessor for the oldest element in the queue.
     *
     * @return A const reference to the oldest element in the queue.
     */
    Queue::const_reference Queue::front() const
    {

        return buffer[head];
    }

    /**
     * @brief Accessor and mutator for the newest element in the queue.
     *
     * @return A reference to the newest element in the queue.
     */
    Queue::reference Queue::back()
    {

        return buffer[((head + current_size - 1) % _capacity)];
    }

    /**
     * @brief Accessor for the newest element in the queue.
     *
     * @return A constant reference to the newest element in the queue.
     */
    Queue::const_reference Queue::back() const
    {

        return buffer[((head + current_size - 1) % _capacity)];
    }

    /**
     * @brief Get the index of the oldest element in the queue.
     *
     * @return The index of the oldest element.
     */
    Queue::size_type Queue::front_index() const
    {
        return head;
    }

    /**
     * @brief Get the index of the newest element in the queue.
     *
     * @return The index of the newest element.
     */
    Queue::size_type Queue::back_index() const
    {
        return (head + current_size) % _capacity;
    }

    /**
     * @brief Swaps the contents of this Queue with another Queue.
     *
     * @param other The Queue object to swap with.
     *
     * This function swaps the contents of the current Queue object with another Queue object.
     * It exchanges the values of the individual data members and swaps the internal buffer pointers.
     * The operation is performed in constant time and does not involve any element-wise data copying.
     */
    void Queue::swap(Queue &other)
    {
        // Swap the individual data members
        size_type temp_head = head;
        head = other.head;
        other.head = temp_head;

        size_type temp_capacity = _capacity;
        _capacity = other._capacity;
        other._capacity = temp_capacity;

        size_type temp_size = current_size;
        current_size = other.current_size;
        other.current_size = temp_size;

        // Swap the buffer
        value_type *temp_buffer = buffer;
        buffer = other.buffer;
        other.buffer = temp_buffer;
    }

    /**
     * @brief Swaps the contents of two Queue objects.
     *
     * @param first The first Queue to be swapped.
     * @param second The second Queue to be swapped.
     *
     * This non-member function swaps the contents of two Queue objects by calling the member function
     * Queue::swap for the first Queue object, which exchanges the values of the individual data members
     * and the internal buffer pointers. The operation is performed in constant time and does not involve
     * any element-wise data copying.
     */
    void swap(Queue &first, Queue &second)
    {
        first.Queue::swap(second);
    }
}
