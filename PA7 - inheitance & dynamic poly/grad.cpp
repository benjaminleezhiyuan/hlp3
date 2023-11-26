/*!******************************************************************
 * \file      grad.cpp
 * \author    Benjamin Lee
 * \par       DP email: benjaminzhiyuan.lee\@digipen.edu.sg
 * \par       Course: CSD2126
 * \par       Section: B
 * \par      
 * \date      26-11-2023
 * 
 * \brief     Definitions for class Graduate member functions
 *********************************************************************/

#include "grad.hpp" 
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

int Graduate::gcount = 0;

/**
 * @brief Constructs a Graduate object from a comma-separated string.
 *
 * @param line A string containing comma-separated values with information about the graduate student.
 */
Graduate::Graduate(std::string& line) : Student(line) 
{
    std::istringstream iss(line);
    std::string token;
     // Skip the common information already parsed by the Student constructor
    for (int i = 0; i < 4; ++i) {
        std::getline(iss, token, ',');
    }

    std::getline(iss >> std::ws, gresearch, ',');
    
    std::getline(iss >> std::ws, gadvisor, ',');
    
    gcount++;
}

/**
 * @brief Gets the research area of the graduate student.
 *
 * @return A string representing the research area of the graduate student.
 */
std::string Graduate::research() const
{
    return gresearch;
}

/**
 * @brief Gets the advisor of the graduate student.
 *
 * @return A string representing the advisor of the graduate student.
 */
std::string Graduate::advisor() const
{
    return gadvisor;
}

/**
 * @brief Gets the total count of created Graduate objects.
 *
 * @return An integer representing the total count of Graduate objects.
 */
int Graduate::count()
{
    return Graduate::gcount;
}

/**
 * @brief Prints details of the graduate student, including common details from the base class (Student),
 *        type, research area, and advisor.
 */
void Graduate::print_details() const
  {
    Student::print_details();
    std::cout << "Type = Graduate Student" << std::endl;
    std::cout << "Research Area = " << gresearch << std::endl;
    std::cout << "Advisor = " << gadvisor << std::endl;
  }

/**
 * @brief Calculates the total score for the graduate student based on homework mean and project score.
 *
 * @return A double representing the total score of the graduate student.
 */
double Graduate::total_score() const
{
    return hw_mean()*0.5 + project_score()*0.5;
}

/**
 * @brief Calculates the course grade for the graduate student based on the total score.
 *
 * @return A string representing the course grade of the graduate student.
 */
std::string Graduate::course_grade() const
{   
    if (total_score() < 80.0)
    {
        return "N";
    }
    else
    {
        return "CR";
    }
}