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
#include <cstring>
#include <cstddef>

// this is the maximum size of buffer for reading data from input file
// and to write data to output file ...
// if a file contains 10000 bytes, this means that you have to repeatedly
// [thrice] read the file for 4096 bytes, followed by the next 4096 bytes,
// followed by the final 1808 bytes.
// Not following this recipe by increasing the buffer to a higher value
// will mean that your submission is not following the specified requirements
// and will receive a zero grade!!!
constexpr int FOUR_K {4096}; // Don't modify this!!!
constexpr int MAX_FILENAME_LENGTH {128};

SplitResult split(char *argv[]) {
    int chunkSize = std::atoi(argv[2]);
    if (chunkSize > FOUR_K) {
        chunkSize = FOUR_K;
    }

    const char *outputPath = argv[4];
    const char *inputPath = argv[6];

    std::ifstream sourceFile(inputPath, std::ios::binary);
    if (!sourceFile.is_open()) {
        return E_BAD_SOURCE;
    }

    sourceFile.seekg(0, std::ios::end);
    long fileSize = sourceFile.tellg();
    sourceFile.seekg(0, std::ios::beg);

    int numChunks = (fileSize + chunkSize - 1) / chunkSize;
    char *buffer = new char[chunkSize];
    if (!buffer) {
        sourceFile.close();
        return E_NO_MEMORY;
    }

    for (int chunkIndex = 0; chunkIndex < numChunks; ++chunkIndex) {
        int bytesRead = 0;

        while (bytesRead + chunkSize <= fileSize) {
            sourceFile.read(buffer, chunkSize);
            bytesRead += sourceFile.gcount();

            char chunkFilename[MAX_FILENAME_LENGTH];
            snprintf(chunkFilename, MAX_FILENAME_LENGTH, "%s%04d", outputPath, chunkIndex + 1);
            std::ofstream chunkFile(chunkFilename, std::ios::binary | std::ios::app);
            if (!chunkFile.is_open()) {
                delete[] buffer;
                sourceFile.close();
                return E_BAD_DESTINATION;
            }
            chunkFile.write(buffer, bytesRead);
        }

        int remainingBytes = fileSize - bytesRead;
        if (remainingBytes > 0) {
            sourceFile.read(buffer, remainingBytes);
            bytesRead += sourceFile.gcount();

            char chunkFilename[MAX_FILENAME_LENGTH];
            snprintf(chunkFilename, MAX_FILENAME_LENGTH, "%s%04d", outputPath, chunkIndex + 1);
            std::ofstream chunkFile(chunkFilename, std::ios::binary | std::ios::app);
            if (!chunkFile.is_open()) {
                delete[] buffer;
                sourceFile.close();
                return E_BAD_DESTINATION;
            }
            chunkFile.write(buffer, bytesRead);
        }
    }

    delete[] buffer;
    sourceFile.close();

    return E_SPLIT_SUCCESS;
}

SplitResult join(int argc, char *argv[]) {
    const char *outputPath = argv[3];

    std::ofstream outputFile(outputPath, std::ios::binary);
    if (!outputFile.is_open()) {
        return E_BAD_DESTINATION;
    }

    for (int i = 5; i < argc; i++) {
        const char *chunkPath = argv[i];

        std::ifstream chunkFile(chunkPath, std::ios::binary);
        if (!chunkFile.is_open()) {
            outputFile.close();
            return E_BAD_SOURCE;
        }

        char buffer[FOUR_K];
        size_t bytesRead;
        while ((bytesRead = chunkFile.readsome(buffer, sizeof(buffer))) > 0) {
            outputFile.write(buffer, bytesRead);
        }

        chunkFile.close();
    }

    outputFile.close();

    return E_JOIN_SUCCESS;
}

SplitResult split_join(int argc, char *argv[]) {
    SplitResult rs = E_NO_ACTION;

    if (argc < 4) {
        // Handle insufficient command-line arguments
        return rs;
    }

    char *operation = argv[1]; // check if it's a split or join operation

    if (std::strcmp(operation, "-s") == 0) {
        rs = split(argv);
    } else if (std::strcmp(operation, "-j") == 0) {
        rs = join(argc, argv);
    }

    return rs;
}
