/*!******************************************************************
 * \file      lines.cpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par      
 * \date      30-08-2023
 * 
 * \brief     Function definition for line counter
 *********************************************************************/


#include "lines.hpp"

/**
 * \brief Count the number of lines in a file.
 *
 * This function opens the specified file and counts the number of lines present in it.
 *
 * \param filename The name of the file to be opened and counted.
 * \return The number of lines in the file. Returns 0 if the file cannot be opened.
 */
int lines_in_file(const char *filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 0;
    }

    int line_count = 0;
    std::string line;
    while (std::getline(file, line))
    {
        line_count++;
    }
    return line_count;
}

/**
 * \brief Count the total number of lines in multiple files.
 *
 * This function takes an array of file names and counts the total number of lines
 * across all the files.
 *
 * \param filename An array of C-style strings (const char*) containing the names of files.
 *                 The last element of the array must be a nullptr to indicate the end.
 *
 * \return The total number of lines in all the files. Returns 0 if any file cannot be opened.
 */
int HLP3::lines(const char *filename[])
{
    int total = 0;
    int index = 0;

    while (filename[index] != nullptr)
    {
        int file_lines = lines_in_file(filename[index]);
        if (file_lines >= 0)
        {
            total += file_lines;
        }
        index++;
    }
    return total;
}
