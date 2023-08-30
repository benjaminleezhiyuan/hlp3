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

// add other headers from C standard library ...
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "splitter.h"

// this is the maximum size of buffer for reading data from input file
// and to write data to output file ...
// if a file contains 10000 bytes, this means that you have to repeatedly
// [thrice] read the file for 4096 bytes, followed by the next 4096 bytes,
// followed by the final 1808 bytes.
// Not following this recipe by increasing the buffer to a higher value
// will mean that your submission is not following the specified requirements
// and will receive a zero grade!!!
#define FOUR_K 4096 // Don't modify this!!!

SplitResult split_file(const char *inputFile, const char *outputPrefix, size_t pieceSize)
{
  FILE *input = fopen(inputFile, "rb");
  if (!input)
  {
    return E_BAD_SOURCE;
  }

  unsigned char *buffer = (unsigned char *)malloc(pieceSize);
  if (!buffer)
  {
    fclose(input);
    return E_NO_MEMORY;
  }

  size_t pieceCount = 0;
  while (!feof(input))
  {
    size_t bytesRead = fread(buffer, 1, pieceSize, input);

    if (bytesRead > 0)
    {
      char outputFilename[100];
      snprintf(outputFilename, sizeof(outputFilename), "%s%zu", outputPrefix, pieceCount + 1);
      FILE *output = fopen(outputFilename, "wb");
      if (!output)
      {
        free(buffer);
        fclose(input);
        return E_BAD_DESTINATION;
      }

      fwrite(buffer, 1, bytesRead, output);
      fclose(output);

      pieceCount++;
    }
  }

  free(buffer);
  fclose(input);
  return E_SPLIT_SUCCESS;
}

SplitResult join_files(const char *outputFile, const char **inputFiles, size_t numInputFiles)
{
  FILE *output = fopen(outputFile, "wb");
    if (!output) {
        return E_BAD_DESTINATION;
    }

    unsigned char *buffer = (unsigned char *)malloc(FOUR_K);
    if (!buffer) {
        fclose(output);
        return E_NO_MEMORY;
    }

    for (size_t i = 0; i < numInputFiles; i++) {
        FILE *input = fopen(inputFiles[i], "rb");
        if (!input) {
            fclose(output);
            free(buffer);
            return E_BAD_SOURCE;
        }

        size_t bytesRead;

        while ((bytesRead = fread(buffer, 1, FOUR_K, input)) > 0) {
            fwrite(buffer, 1, bytesRead, output);
        }

        fclose(input);
    }

    fclose(output);
    free(buffer);
    return E_JOIN_SUCCESS;
}

SplitResult split_join(int argc, char *argv[])
{
  SplitResult rs = E_NO_ACTION;

  // parse command-line arguments to determine whether to split a file
  // into smaller files	or to join smaller files into original file ...
  if (argc != 6 || strcmp(argv[1], "-s") != 0)
  {
    printf("Usage: %s -s <piece_size> -o <output_prefix> -i <input_file>\n", argv[0]);
    return rs;
  }

  size_t pieceSize = (size_t)atoi(argv[2]) < (size_t)FOUR_K ? (size_t)atoi(argv[2]) : (size_t)FOUR_K;
  char *outputPrefix = argv[4];
  char *inputFile = argv[6];

  return split_file(inputFile, outputPrefix, pieceSize);

  if (argc < 5 || strcmp(argv[1], "-j") != 0)
  {
    printf("Usage: %s -j -o <output_file> -i <input_files>\n", argv[0]);
    return rs;
  }

  char *outputFile = argv[3];
  char **inputFiles = &argv[5]; // Skip the -i flag
  size_t numInputFiles = argc - 5;

  return join_files(outputFile, (const char **)inputFiles, numInputFiles);
}
