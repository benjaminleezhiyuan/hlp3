#ifndef QUEUE_HPP
#define QUEUE_HPP

namespace HLP3
{

  class Queue
  {
  public:
    using value_type = char;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = unsigned long;

    // No default constructor
    Queue() = delete;

    // Constructor with capacity
    Queue(size_type capacity);

    // Copy constructor
    Queue(const Queue &other);

    // Destructor
    ~Queue();

    // Copy assignment operator
    Queue &operator=(const Queue &other);

    // Return pointer to queue buffer
    const_pointer c_buff() const;

    bool empty() const;         // Check if the queue is empty
    bool full() const;          // Check if the queue is full
    size_type size() const;     // Return the current size of the queue
    size_type capacity() const; // Return the capacity of the queue

    // Add new element to the buffer
    void push(const value_type &element);

    // Rmove oldest element in buffer
    void pop();

    // Accessor and mutator for oldest element
    reference front();

    // Accessor only for oldest element
    const_reference front() const;

    // Accessor and mutator for newest element
    reference back();

    // Accesor only for newest element
    const_reference back() const;

    // Return indices to oldest element
    size_type front_index() const;

    // Return indices to newest element
    size_type back_index() const;

    // Swap current object of type Queue with another object of type Queue
    void swap(Queue &other);

  private:
    size_type head;
    size_type tail;
    size_type _capacity;
    size_type current_size;
    pointer buffer;
  };

  // declare necessary non-member function(s) ...

  // Swap two objects of type Queue
  void swap(Queue &first, Queue &second);

}
#endif
