/*!******************************************************************
 * \file      splitter.cpp
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
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

// this is the maximum size of buffer for reading data from input file
// and to write data to output file ...
// if a file contains 10000 bytes, this means that you have to repeatedly
// [thrice] read the file for 4096 bytes, followed by the next 4096 bytes,
// followed by the final 1808 bytes.
// Not following this recipe by increasing the buffer to a higher value
// will mean that your submission is not following the specified requirements
// and will receive a zero grade!!!
constexpr int FOUR_K{4096}; // Don't modify this!!!
constexpr int MAX_FILENAME_LENGTH{128};

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
    int chunkSize = std::stoi(argv[2]);

    const std::string outputPath = argv[4];
    const std::string inputPath = argv[6];

    std::ifstream sourceFile(inputPath, std::ios::binary);
    if (!sourceFile)
    {
        return E_BAD_SOURCE;
    }

    sourceFile.seekg(0, std::ios::end);
    long fileSize = sourceFile.tellg();
    sourceFile.seekg(0, std::ios::beg);

    int numChunks = (fileSize + chunkSize - 1) / chunkSize;
    char *buffer = new char[chunkSize]; // Using 'new' for memory allocation

    for (int chunkIndex = 0; chunkIndex < numChunks; ++chunkIndex)
    {
        int bytesRead = sourceFile.readsome(buffer, chunkSize);

        // Create the chunk filename with padded zeros
        std::ostringstream chunkFilenameStream;
        chunkFilenameStream << outputPath << std::setw(4) << std::setfill('0') << chunkIndex + 1;
        std::string chunkFilename = chunkFilenameStream.str();

        std::ofstream chunkFile(chunkFilename, std::ios::binary | std::ios::app);
        if (!chunkFile)
        {
            delete[] buffer; // Release allocated memory before returning
            return E_BAD_DESTINATION;
        }

        chunkFile.write(buffer, bytesRead);
    }

    delete[] buffer; // Release allocated memory
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
    const std::string outputPath = argv[3];

    // Open the output file for writing
    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile.is_open())
    {
        return E_BAD_DESTINATION; // Failed to open output file
    }

    // Process each chunk file
    for (int i = 5; i < argc; i++)
    {
        const std::string chunkPath = argv[i];

        // Open the chunk file for reading
        std::ifstream chunkFile(chunkPath, std::ios::binary);
        if (!chunkFile.is_open())
        {
            outputFile.close();
            return E_BAD_SOURCE; // Failed to open chunk file
        }

        // Read and write the content of the chunk file
        chunkFile.seekg(0, std::ios::end);
        long fileSize = chunkFile.tellg();
        chunkFile.seekg(0, std::ios::beg);
        char *buffer = new char[fileSize];
        size_t bytesRead;
        while ((bytesRead = chunkFile.read(buffer, fileSize).gcount()) > 0)
        {
            outputFile.write(buffer, bytesRead);
        }

        // Close the chunk file and deallocate buffer
        chunkFile.close();
        delete[] buffer;
    }

    outputFile.close();
    return E_JOIN_SUCCESS; // Joining successful
}

/**
 * @brief Performs either a splitting or joining operation based on the specified command.
 *
 * This function takes command-line arguments and performs either a splitting or joining
 * operation on files based on the command specified.
 *
 * @param argc The number of command-line arguments.
 * @param argv Command-line arguments passed to the program, including the operation flag.
 * @return SplitResult indicating the success or failure of the split or join operation.
 */
SplitResult split_join(int argc, char *argv[])
{
    SplitResult rs = SplitResult::E_NO_ACTION;

    if (argc < 4)
    {
        // Handle insufficient command-line arguments
        return rs;
    }

    std::string operation = argv[1];

    if (operation == "-s")
    {
        rs = split(argv);
    }
    else if (operation == "-j")
    {
        rs = join(argc, argv);
    }

    return rs;
}

