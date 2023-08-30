/*!******************************************************************
 * \file      splitter.h
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par      
 * \date      30-08-2023
 * 
 * \brief  
 *********************************************************************/

#ifndef SPLITTER_H
#define SPLITTER_H

#include <stddef.h> // size_t definition

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
  E_BAD_SOURCE = 1,
  E_BAD_DESTINATION,
  E_NO_MEMORY,
  E_SMALL_SIZE,
  E_NO_ACTION,
  E_SPLIT_SUCCESS,
  E_JOIN_SUCCESS
} SplitResult;

// provide function header documentation using Doxygen tags to explain to
// your client how they must use this function to either split big file into
// smaller files or join [previously split] smaller files into big file ...

/**
 * @brief Split or join files based on the provided command line arguments.
 *
 * This function takes the command line arguments passed to it and processes them
 * to either split a big file into smaller files or join previously split smaller
 * files into a big file.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * @return The result of the split or join operation (SplitResult).
 */
SplitResult split_join(int argc, char *argv[]);

#ifdef __cplusplus
}
#endif

#endif // end of #ifndef SPLITTER_H
