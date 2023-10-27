/*!******************************************************************
 * \file      polynomial.tpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par      
 * \date      24-10-2023
 * 
 * \brief     Class member definitions for polynomial arithmatic.
 *********************************************************************/

namespace HLP3
{

  // Define member functions of class template Polynomial ...

  template <typename T, int N>
  T Polynomial<T, N>::operator()(T a) const
  {
    T result = coefficients[N]; // Start with the highest-order term

    for (int i = N - 1; i >= 0; i--)
    {
      result = result * a + coefficients[i]; // Horner's method for polynomial evaluation
    }

    return result;
  }

  template <typename T, int N>
  template <int M>
  Polynomial<T, N + M> Polynomial<T, N>::operator*(const Polynomial<T, M> &other) const
  {
    static_assert(std::is_same<T, T>::value, "Coefficient types must be the same.");

    Polynomial<T, N + M> result;

    for (int i = 0; i <= N; i++)
    {
      for (int j = 0; j <= M; j++)
      {
        result[i + j] += coefficients[i] * other[j];
      }
    }

    return result;
  }

  template <typename T, int N>
  Polynomial<T, N>::Polynomial()
  {
    // Initialize all coefficients to zero
    for (int i = 0; i <= N; i++)
    {
      coefficients[i] = T(); // T() initializes to the default value (e.g., 0 for numeric types)
    }
  }

  template <typename T, int N>
  template <typename U>
  Polynomial<T, N>::Polynomial(const Polynomial<U, N> &other)
  {
    // Verify that the degrees of the two polynomials are the same
    static_assert(N == N, "Polynomial degrees must be the same.");

    // Copy coefficients from the other polynomial with potential type conversion
    for (int i = 0; i <= N; i++)
    {
      coefficients[i] = static_cast<T>(other[i]);
    }
  }

  template <typename T, int N>
  T &Polynomial<T, N>::operator[](int idx)
  {
    return coefficients[idx];
  }

  template <typename T, int N>
  const T &Polynomial<T, N>::operator[](int idx) const
  {
    return coefficients[idx];
  }

  // DON'T CHANGE/EDIT THE FOLLOWING DEFINITION:
  template <typename T, int N>
  std::ostream &operator<<(std::ostream &out, Polynomial<T, N> const &pol)
  {
    out << pol[0] << " ";
    for (int i = 1; i <= N; ++i)
    {
      if (pol[i] != 0)
      { // skip terms with zero coefficients
        if (pol[i] > 0)
        {
          out << "+";
        }
        if (pol[i] == 1)
        {
        }
        else if (pol[i] == -1)
        {
          out << "-";
        }
        else
        {
          out << pol[i] << "*";
        }
        out << "x^" << i << " ";
      }
    }
    return out;
  }

} // end namespace HLP3
