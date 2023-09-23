/*!******************************************************************
 * \file      tddaa.cpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par      
 * \date      24-09-2023
 * 
 * \brief     Function definition for allocate and deallocate.
 *********************************************************************/

#include "tddaa.h"

/**
 * @brief Allocates memory for a three-dimensional array of integers.
 *
 * This function allocates memory for a three-dimensional array of integers
 * with the specified number of frames, rows, and columns.
 *
 * @param F The number of frames.
 * @param R The number of rows per frame.
 * @param C The number of columns per row.
 *
 * @return A pointer to the allocated three-dimensional array.
 */
int ***allocate(int F, int R, int C)
{
  // Allocate memory for the element array
  int *element = new int[F * R * C];

  // Allocate memory for the row pointers
  int **row = new int *[F * R];

  // Allocate memory for the frame pointers
  int ***frame = new int **[F];

  // Initialize a two-dimensional array of pointers, representing frames, rows, and elements
  for (int i = 0; i < F; i++) // Loop through frames (F represents the number of frames)
  {
    for (int j = 0; j < R; j++) // Loop through rows (R represents the number of rows per frame)
    {
      // Calculate the index for the current element in the 2D array
      // and assign it to the 'row' array as a pointer to the element.
      // 'element' is the base address, and (i * R + j) represents the offset.
      row[i * R + j] = element + (i * R + j) * C;
    }
    // Assign the 'row' array as a pointer to the current frame in the 'frame' array.
    frame[i] = row + i * R;
  }

  // Return the 'frame' array containing pointers to the 2D array of elements.
  return frame;
}

/**
 * @brief Deallocates memory associated with a three-dimensional array of integers.
 *
 * This function deallocates memory that was previously allocated for a
 * three-dimensional array of integers using the `allocate` function.
 *
 * @param ppp A pointer to the three-dimensional array to be deallocated.
 */
void deallocate(int ***ppp)
{
  delete[] ppp[0][0];
  delete[] ppp[0];
  delete[] ppp;
}
