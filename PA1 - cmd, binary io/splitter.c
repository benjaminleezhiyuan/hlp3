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
#include <stdlib.h>
#include <string.h>
#include <stddef.h> // size_t definition

// this is the maximum size of buffer for reading data from input file
// and to write data to output file ...
// if a file contains 10000 bytes, this means that you have to repeatedly
// [thrice] read the file for 4096 bytes, followed by the next 4096 bytes,
// followed by the final 1808 bytes.
// Not following this recipe by increasing the buffer to a higher value
// will mean that your submission is not following the specified requirements
// and will receive a zero grade!!!
#define FOUR_K 4096 // Don't modify this!!!
#define MAX_FILENAME_LENGTH 128

/**
 * @brief Splits a source file into smaller chunks and writes them to separate destination files.
 *
 * This function takes command-line arguments, reads a source file, splits it into chunks, and
 * writes each chunk to a separate destination file.
 *
 * @param argv Command-line arguments passed to the program.
 * @return SplitResult indicating the success or failure of the operation.
 */
SplitResult split(char *argv[])
{
  int chunkSize = atoi(argv[2]);
  int maxRead = chunkSize;
  if (chunkSize > FOUR_K)
  {
    maxRead = FOUR_K; // Limit the read size to FOUR_K if it's larger
  }

  const char *outputPath = argv[4];
  const char *inputPath = argv[6];

  FILE *sourceFile = fopen(inputPath, "rb");
  if (!sourceFile)
  {
    return E_BAD_SOURCE;
  }

  fseek(sourceFile, 0, SEEK_END);
  long fileSize = ftell(sourceFile);
  rewind(sourceFile);

  int numChunks = (fileSize + chunkSize - 1) / chunkSize;
  char *buffer = (char *)malloc(chunkSize);
  if (!buffer)
  {
    fclose(sourceFile);
    return E_NO_MEMORY;
  }

  for (int chunkIndex = 0; chunkIndex < numChunks; ++chunkIndex)
  {
    char chunkFilename[MAX_FILENAME_LENGTH];
    snprintf(chunkFilename, MAX_FILENAME_LENGTH, "%s%04d", outputPath, chunkIndex + 1);
    FILE *chunkFile = fopen(chunkFilename, "ab");
    if (!chunkFile)
    {
      free(buffer);
      fclose(sourceFile);
      return E_BAD_DESTINATION;
    }
    int bytesForChunk = chunkSize;
    while (bytesForChunk > 0)
    {
      int bytesToRead = bytesForChunk < maxRead ? bytesForChunk : maxRead;
      int bytesRead = fread(buffer, 1, bytesToRead, sourceFile);
      if (bytesRead == 0)
      {
        break;
      }
      fwrite(buffer, 1, bytesRead, chunkFile);
      bytesForChunk -= bytesRead;
    }
    fclose(chunkFile);
  }

  free(buffer);
  fclose(sourceFile);

  return E_SPLIT_SUCCESS;
}

/**
 * @brief Joins multiple chunk files into a single output file.
 *
 * This function takes command-line arguments, opens an output file for writing, and then
 * sequentially reads and appends the content of each chunk file to the output file to
 * join them together.
 *
 * @param argc The number of command-line arguments.
 * @param argv Command-line arguments passed to the program, including the chunk file paths.
 * @return SplitResult indicating the success or failure of the join operation.
 */
SplitResult join(int argc, char *argv[])
{
  const char *outputPath = argv[3];

  // Open the output file for writing
  FILE *outputFile = fopen(outputPath, "wb");
  if (!outputFile)
  {
    return E_BAD_DESTINATION; // Failed to open output file
  }

  // Process each chunk file
  for (int i = 5; i < argc; i++)
  {
    const char *chunkPath = argv[i];

    // Open the chunk file for reading
    FILE *chunkFile = fopen(chunkPath, "rb");
    if (!chunkFile)
    {
      fclose(outputFile);
      return E_BAD_SOURCE; // Failed to open chunk file
    }

    // Read and write the content of the chunk file
    char buffer[FOUR_K];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), chunkFile)) > 0)
    {
      fwrite(buffer, 1, bytesRead, outputFile);
    }

    fclose(chunkFile);
  }

  fclose(outputFile);

  return E_JOIN_SUCCESS; // Joining successful
}

/**
 * @brief Splits or joins files based on the specified operation.
 *
 * This function takes command-line arguments and performs either a splitting or joining
 * operation on files based on the operation argument provided.
 *
 * @param argc The number of command-line arguments.
 * @param argv Command-line arguments passed to the program, including the operation flag.
 * @return SplitResult indicating the success or failure of the split or join operation.
 */
SplitResult split_join(int argc, char *argv[])
{
  SplitResult rs = E_NO_ACTION;

  if (argc < 4)
  {
    // Handle insufficient command-line arguments
    return rs;
  }

  char *operation = argv[1]; // check if its split or join operation

  if (strcmp(operation, "-s") == 0)
  {
    // Handle splitting operation
    // Read the input file and split it into smaller pieces
    // Write the smaller pieces to the output directory
    // Set rs based on the success or failure of the operation
    rs = split(argv);
  }
  else if (strcmp(operation, "-j") == 0)
  {
    // Handle joining operation
    // Read the smaller pieces and join them into the original file
    // Write the joined data to the output file
    // Set rs based on the success or failure of the operation
    rs = join(argc, argv);
  }

  return rs;
}
