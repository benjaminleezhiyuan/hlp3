/*!******************************************************************
 * \file      ug.cpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par
 * \date      26-11-2023
 *
 * \brief     Definitions for class Undergraduate member functions
 *********************************************************************/

#include "ug.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

// Initialize static data member ucount
int Undergraduate::ucount = 0;

Undergraduate::Undergraduate(std::string &line) : Student(line)
{
    std::stringstream iss(line);
    std::string token;

    // Skip the first 4 tokens
    for (int i = 0; i < 4; ++i)
    {
        std::getline(iss, token, ','); // Read and discard the token
    }

    std::getline(iss >> std::ws, udorm, ',');
    std::getline(iss >> std::ws, uyear, ',');

    ucount++;
}

/**
 * @brief Gets the dormitory information of the undergraduate student.
 *
 * @return A string representing the dormitory of the undergraduate student.
 */
std::string Undergraduate::dormitory() const
{
    return udorm;
}

/**
 * @brief Gets the graduation year of the undergraduate student.
 *
 * @return A string representing the graduation year of the undergraduate student.
 */
std::string Undergraduate::year() const
{
    return uyear;
}

/**
 * @brief Gets the total count of created Undergraduate objects.
 *
 * @return An integer representing the total count of Undergraduate objects.
 */
int Undergraduate::count()
{
    return Undergraduate::ucount;
}

/**
 * @brief Prints details of the undergraduate student, including common
 *        details from the base class (Student),
 *        type, residence hall, and year in college.
 */
void Undergraduate::print_details() const
{
    Student::print_details();
    std::cout << "Type = Undergraduate Student" << std::endl;
    std::cout << "Residence Hall = " << udorm << std::endl;
    std::cout << "Year in College = " << uyear << std::endl;
}

/**
 * @brief Calculates the total score for the undergraduate student
 *        based on homework mean and project score.
 *
 * @return A double representing the total score of the undergraduate student.
 */
double Undergraduate::total_score() const
{

    return hw_mean() * 0.7 + project_score() * 0.3;
}

/**
 * @brief Calculates the course grade for the undergraduate student based on the total score.
 *
 * @return A string representing the course grade of the undergraduate student.
 */
std::string Undergraduate::course_grade() const
{
    if (total_score() < 70.0)
    {
        return "N";
    }
    else
    {
        return "CR";
    }
}