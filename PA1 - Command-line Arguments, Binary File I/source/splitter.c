/*!******************************************************************
 * \file      splitter.c
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      30-08-2023
 *
 * \brief
 *********************************************************************/

#include "splitter.h"
#include <stdio.h>
#include <string.h>

// this is the maximum size of buffer for reading data from input file
// and to write data to output file ...
// if a file contains 10000 bytes, this means that you have to repeatedly
// [thrice] read the file for 4096 bytes, followed by the next 4096 bytes,
// followed by the final 1808 bytes.
// Not following this recipe by increasing the buffer to a higher value
// will mean that your submission is not following the specified requirements
// and will receive a zero grade!!!
#define FOUR_K 4096 // Don't modify this!!!

SplitResult split(size_t pieceSize, const char *outputDir, const char *inputFile)
{

}

SplitResult join(const char *outputFile, const char *inputDir)

{

}

SplitResult split_join(int argc, char *argv[])
{
  SplitResult rs = E_NO_ACTION;

  if (argc < 4)
  {
    // Handle insufficient command-line arguments
    return rs;
  }

  char *operation = argv[1];

  if (strcmp(operation, "-s") == 0)
  {
    // Handle splitting operation
    // Read the input file and split it into smaller pieces
    // Write the smaller pieces to the output directory
    // Set rs based on the success or failure of the operation
    split(atoi(argv[2]),argv[4],argv[6]);
  }
  else if (strcmp(operation, "-j") == 0)
  {
    // Handle joining operation
    // Read the smaller pieces and join them into the original file
    // Write the joined data to the output file
    // Set rs based on the success or failure of the operation
    join(argv[3],argv[5]);
  }

  return rs;
}
