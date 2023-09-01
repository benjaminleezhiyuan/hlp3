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


typedef enum {
  E_BAD_SOURCE = 1,
  E_BAD_DESTINATION,
  E_NO_MEMORY,
  E_SMALL_SIZE,
  E_NO_ACTION,
  E_SPLIT_SUCCESS,
  E_JOIN_SUCCESS
} SplitResult;

/**
 * @brief Splits or joins files based on the provided arguments.
 *
 * This function takes command-line arguments (`argc` and `argv`) to determine
 * the operation to perform (splitting or joining) and the necessary parameters.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return SplitResult indicating the success or failure of the operation.
 */
#ifdef __cplusplus
extern "C" 
#endif
SplitResult split_join(int argc, char *argv[]);

#endif // end of #ifndef SPLITTER_H
