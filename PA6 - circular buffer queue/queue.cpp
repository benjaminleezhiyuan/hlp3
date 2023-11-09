#include "queue.hpp"

namespace HLP3
{
    // Constructor with capacity
    Queue::Queue(size_type _capacity) : head(0), tail(0), _capacity(_capacity), current_size(0)
    {
        buffer = new value_type[_capacity];
    }

    // Copy constructor
    Queue::Queue(const Queue &other) : head(other.head), tail(other.tail), _capacity(other._capacity), current_size(other.current_size)
    {
        buffer = new value_type[_capacity];
        for (size_type i = 0; i < current_size; ++i)
        {
            buffer[i] = other.buffer[i];
        }
    }

    // Copy assignment operator
    Queue &Queue::operator=(const Queue &other)
    {
        // Avoid self-assignment
        delete[] buffer; // Free the existing memory

        head = other.head;
        tail = other.tail;
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

    // Destructor
    Queue::~Queue()
    {
        delete[] buffer;
    }

    // Definition of c_buff member function
    Queue::const_pointer Queue::c_buff() const
    {
        return buffer;
    }

    bool Queue::empty() const
    {
        return current_size == 0;
    }

    bool Queue::full() const
    {
        return current_size == _capacity;
    }

    Queue::size_type Queue::size() const
    {
        return current_size;
    }

    Queue::size_type Queue::capacity() const
    {
        return _capacity;
    }

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

    void Queue::pop()
    {
        if (!empty())
        {
            head = (head + 1) % _capacity; // Increment head
            --current_size;                // Decrement size
        }
    }

    Queue::reference Queue::front()
    {

        return buffer[head];
    }

    Queue::const_reference Queue::front() const
    {

        return buffer[head];
    }

    Queue::reference Queue::back()
    {

        return buffer[((head + current_size - 1) % _capacity)];
    }

    Queue::const_reference Queue::back() const
    {

        return buffer[((head + current_size - 1) % _capacity)];
    }

    Queue::size_type Queue::front_index() const
    {
        return head;
    }

    Queue::size_type Queue::back_index() const
    {
        return (head + current_size) % _capacity;
    }

    void Queue::swap(Queue &other)
    {
        // Swap the individual data members
        size_type temp_head = head;
        head = other.head;
        other.head = temp_head;

        size_type temp_tail = tail;
        tail = other.tail;
        other.tail = temp_tail;

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

    void swap(Queue &first, Queue &second)
    {
        first.Queue::swap(second);
    }
}
