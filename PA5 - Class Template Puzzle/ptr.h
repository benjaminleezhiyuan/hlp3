/*!******************************************************************
 * \file      ptr.h
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      30-10-2023
 *
 * \brief     This file contains the declaration and implementation of a Ptr class.
 *********************************************************************/

#include <iostream> // std::ostream

// TODO: Don't include any other C and C++ standard library headers!!!

#ifndef PTR_H
#define PTR_H

namespace HLP3
{

  // partially defined class template Ptr
  template <typename T>
  class Ptr
  {
  private:
    T *p; // DO NOT AMEND!!!
  public:
    Ptr() = delete;                  // DO NOT AMEND!!!
    Ptr(Ptr &&) = delete;            // DO NOT AMEND!!!
    Ptr &operator=(Ptr &&) = delete; // DO NOT AMEND!!!
    explicit Ptr(T *_p) : p{_p} {}   // DO NOT AMEND!!!
    ~Ptr()
    {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
      delete p;
    } // DO NOT AMEND!!!

    T *get() const { return p; } // DO NOT AMEND!!!

    // Copy constructor to create a copy of another Ptr object.
    Ptr(const Ptr &other) : p(new T(*other.p)) {}

    // Copy assignment operator to assign one Ptr object to another of the same type.
    Ptr &operator=(const Ptr &other)
    {
      if (this != &other) // Ensures not assigning to itself.
      {
        delete p; // Deletes the current data.
        p = new T(*other.p); // Copies the data from the other Ptr.
      }
      return *this; // Returns a reference to the updated object.
    }

    // Conversion assignment operator - assigns from Ptr<U> to Ptr<T>.
    template <typename U>
    Ptr &operator=(const Ptr<U> &other)
    {
      delete p; // Deletes the current data.
      p = new T(*other.get()); // Copies the data from Ptr<U>.
      return *this; // Returns a reference to the updated object.
    }

    // Conversion constructor from Ptr<U> to Ptr<T>.
    template <typename U>
    Ptr(const Ptr<U> &other) : p(new T(*other.get())) {}

    // Overloaded dereference operator to allow access to the encapsulated data.
    T &operator*() const
    {
      return *p;
    }

    // Overloaded arrow operator to access the encapsulated data's members.
    T *operator->() const
    {
      return p;
    }

    // Overloaded comparison operator (Equality) to compare two Ptr objects.
    bool operator==(const Ptr &other) const
    {
      return p == other.p;
    }

    /*
    Your task is to extend this partially defined class template Ptr with six (6) member functions
    that will enable the unit tests in driver source file ptr-driver.cpp to successfully compile and
    link to generate an executable file that will then generate the correct output for each unit test.

    Carefully read the unit tests in driver source file ptr-driver.cpp to determine the member functions that
    you must declare and define for class template Ptr.
    The driver source file contains the expected output and provides hints to the member functions that you
    must implement to successfully complete the puzzle.

    If you don't implement the required functions [again there are six such functions], it is possible to
    obtain the same results as described in the driver. However, in such cases, the online grader will
    reject your submission.

    You can define the member functions inline or outside the class template definition!!!
    */
  };

} // end namespace HLP3

#endif // #ifndef PTR_H
